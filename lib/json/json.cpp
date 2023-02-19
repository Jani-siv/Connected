#include <fstream>
#include "json.h"
namespace json{

void json::AddObjectsToJsonFile(const std::string &filename, containerDataType &data)
{
    if (IsContainerDataValid(data)) {
        std::string objectData = GenerateObjectToFile(filename, data);
        std::fstream file(filename.c_str(), std::ios_base::app);
        if (file.is_open())
        {
            file.write(objectData.c_str(),static_cast<long>(objectData.length()));
            file.close();
        }
    }
}

void json::AppObjectToJsonFile(const std::string &filename, const std::string &objName, const std::string &data)
{
    size_t position = FindObjectPositionFromFile(filename, objName);
    if (position != 0)
       {
           printf("HELLO: %zu\n",position);
       }
}

bool json::IsContainerDataValid(const containerDataType& data)
{
    if (not data.empty())
    {
        for (const auto& pairData : data)
        {
            if (pairData.first.empty())
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

size_t json::FindObjectPositionFromFile(const std::string &filename, const std::string &objectname)
{
    std::fstream file(filename.c_str(),std::ios_base::in);
    size_t position = 0;
    if (not file.is_open()) { return position;}
    if (file.is_open())
    {
        std::string line;
        while(not file.eof())
        {
            std::getline(file,line);
            if (line.find(objectname) != std::string::npos)
            {
                position = file.tellp();
                break;
            }
        }
        file.close();
    }
    return position;
}

std::string json::GenerateObjectToFile(const std::string& filename, containerDataType &data)
{
    std::string tempData{};
    for (const auto& pairData : data)
    {
        if ((FindObjectPositionFromFile(filename, pairData.first) == 0) &&
            (tempData.find(pairData.first) > tempData.length())){
            tempData += "{ " + pairData.first + " : " + pairData.second + " }\n";
        }
    }
    return tempData;
}


} //namespace json
