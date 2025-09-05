#include "IO/BinaryReader.h"

BinaryReader::BinaryReader(const std::string& filePath, bool loadIntoMemory)
{
    if (loadIntoMemory)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);

        if (!file)
        {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::streamsize size = file.tellg();

        file.seekg(0, std::ios::beg);

        fileBuffer.resize(size);

        if (!file.read(reinterpret_cast<char*>(fileBuffer.data()), size))
        {
            throw std::runtime_error("Failed to read file into memory");
        }

        sourceType = SourceType::Memory;
        memoryBuffer = fileBuffer.data();
        bufferSize = fileBuffer.size();
        bufferPosition = 0;
    }
    else
    {
        fileStream.open(filePath, std::ios::binary | std::ios::in);

        if (!fileStream)
        {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        sourceType = SourceType::File;
    }
}

BinaryReader::BinaryReader(const void* data, const size_t size)
    : sourceType(SourceType::Memory),
    memoryBuffer(static_cast<const uint8_t*>(data)),
    bufferSize(size),
    bufferPosition(0)
{
    if (!data || size == 0)
    {
        throw std::runtime_error("Invalid memory buffer.");
    }
}

BinaryReader::~BinaryReader()
{
    if (fileStream.is_open())
    {
        fileStream.close();
    }
}

const uint8_t* BinaryReader::GetBufferPointer(size_t offset)
{
    if (sourceType == SourceType::Memory)
    {
        if (bufferPosition + offset > bufferSize)
        {
            throw std::out_of_range("GetBufferPointer: offset out of bounds");
        }

        return memoryBuffer + bufferPosition + offset;
    }

    throw std::runtime_error("GetBufferPointer is only valid for memory sources");
}

void BinaryReader::ReadBytes(void* outBuffer, const size_t size)
{
    if (sourceType == SourceType::File)
    {
        fileStream.read(static_cast<char*>(outBuffer), size);

        if (fileStream.gcount() != static_cast<std::streamsize>(size))
        {
            throw std::runtime_error("Failed to read bytes from file.");
        }
    }
    else
    {
        if (bufferPosition + size > bufferSize)
        {
            throw std::runtime_error("Attempt to read past end of buffer.");
        }

        std::memcpy(outBuffer, memoryBuffer + bufferPosition, size);

        bufferPosition += size;
    }
}

std::string BinaryReader::ReadString(const size_t length)
{
    std::string result(length, '\0');

    ReadBytes(result.data(), length);

    return result;
}

void BinaryReader::Seek(size_t offset, const SeekOrigin seekOrigin)
{
    if (sourceType == SourceType::File)
    {
        std::ios_base::seekdir dir;

        switch (seekOrigin)
        {
        case SeekOrigin::Begin:
            dir = std::ios::beg;
            break;
        case SeekOrigin::Current:
            dir = std::ios::cur;
            break;
        case SeekOrigin::End:
            dir = std::ios::end;
            break;
        default:
            throw std::invalid_argument("Invalid SeekOrigin");
        }

        fileStream.seekg(static_cast<std::streamoff>(offset), dir);

        if (!fileStream)
        {
            throw std::runtime_error("Seek failed in file stream");
        }
    }
    else if (sourceType == SourceType::Memory)
    {
        size_t newPos = 0;

        switch (seekOrigin)
        {
        case SeekOrigin::Begin:
            newPos = offset;
            break;
        case SeekOrigin::Current:
            newPos = bufferPosition + offset;
            break;
        case SeekOrigin::End:
            newPos = bufferSize + offset;
            break;
        default:
            throw std::invalid_argument("Invalid SeekOrigin");
        }

        if (newPos > bufferSize)
        {
            throw std::out_of_range("Seek past end of memory buffer");
        }

        bufferPosition = newPos;
    }
}

size_t BinaryReader::GetPosition()
{
    if (sourceType == SourceType::File)
    {
        return static_cast<size_t>(fileStream.tellg());
    }
    else
    {
        return bufferPosition;
    }
}

size_t BinaryReader::GetSize()
{
    if (sourceType == SourceType::File)
    {
        auto current = fileStream.tellg();

        fileStream.seekg(0, std::ios::end);

        size_t size = static_cast<size_t>(fileStream.tellg());

        fileStream.seekg(current);

        return size;
    }
    else
    {
        return bufferSize;
    }
}
