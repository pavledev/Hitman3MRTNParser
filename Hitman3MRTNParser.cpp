#include <iostream>
#include <sstream>
#include <filesystem>

#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

#include <IO/BinaryReader.h>
#include <Glacier/Morpheme.h>

void GetMRTNReferences(const std::string& jsonPath)
{
    std::ifstream ifs(jsonPath);

    if (!ifs.is_open())
    {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    std::stringstream buffer;

    buffer << ifs.rdbuf();

    std::string jsonStr = buffer.str();

    rapidjson::Document doc;
    rapidjson::ParseResult ok = doc.Parse(jsonStr.c_str());

    if (!ok)
    {
        std::cerr << "JSON parse error: "
            << rapidjson::GetParseError_En(ok.Code())
            << " (at offset " << ok.Offset() << ")" << std::endl;

        return;
    }

    if (doc.HasMember("hash_reference_data") && doc["hash_reference_data"].IsArray())
    {
        const auto& refs = doc["hash_reference_data"];

        mrtnReferences.reserve(refs.Size());

        for (rapidjson::SizeType i = 0; i < refs.Size(); i++)
        {
            const auto& ref = refs[i];
            std::string refHash = ref["hash"].GetString();

            mrtnReferences.push_back(refHash);
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: " << argv[0] << " <MRTN file> <meta.JSON file>" << std::endl;

        return 1;
    }

    std::string mrtnPath = argv[1];
    std::string jsonPath = argv[2];

    GetMRTNReferences(jsonPath);

    BinaryReader binaryReader(mrtnPath);
    std::vector<uint8_t> data(binaryReader.GetSize());

    binaryReader.ReadBytes(data.data(), data.size());

    MR::NetworkDef* networkDef = reinterpret_cast<MR::NetworkDef*>(data.data());

    networkDef->Locate();

    std::filesystem::path outPath = std::filesystem::path(mrtnPath).replace_extension(".json");

    std::ofstream of(outPath);

    if (!of.is_open())
    {
        std::cerr << "Failed to create output file: " << outPath << std::endl;
        return 1;
    }

    of << networkDef->SerializeToJson();
    of.close();

    std::cout << "MRTN data serialized to " << outPath << std::endl;

    return 0;
}
