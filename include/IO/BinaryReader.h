#pragma once

#include <fstream>
#include <vector>
#include <cstring>
#include <stdexcept>

class BinaryReader
{
public:
    enum class SourceType
    {
        File,
        Memory
    };

    enum class SeekOrigin
    {
        Begin,
        Current,
        End
    };

    BinaryReader(const std::string& filePath, bool loadIntoMemory = false);
    BinaryReader(const void* data, const size_t size);
    ~BinaryReader();

    const uint8_t* GetBufferPointer(size_t offset);

    template<typename T>
    T Read()
    {
        T value;

        ReadBytes(&value, sizeof(T));

        return value;
    }

    void ReadBytes(void* outBuffer, const size_t size);
    std::string ReadString(const size_t length);

    void Seek(size_t offset, const SeekOrigin seekOrigin = SeekOrigin::Begin);
    size_t GetPosition();
    size_t GetSize();

private:
    SourceType sourceType;
    std::ifstream fileStream;

    std::vector<uint8_t> fileBuffer;
    const uint8_t* memoryBuffer = nullptr;
    size_t bufferSize = 0;
    size_t bufferPosition = 0;
};
