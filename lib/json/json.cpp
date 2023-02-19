#include <fstream>
#include <sstream>
#include <cstring>
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

void json::AppObjectMembersToJsonFile(const std::string &filename, const std::string &objName,
                                      const std::vector<std::pair<type,args>>& data)
{
    size_t position = FindObjectPositionFromFile(filename, objName);
    if (position != 0)
       {
            std::vector<std::string> fromPosition = SplitFileFromPosition(filename, position);
            std::string substr = fromPosition.at(0).substr(0,fromPosition.at(0).find_last_of('}')-1);
           substr += ",";
           substr += '\n';
           //supported only an array type of members
           substr = GenerateMemberString(data,objName,substr);
           fromPosition.at(0) = substr.substr(0, substr.find_last_of(','));
           fromPosition.at(0) += "\n]}";
           (fromPosition.at(1).length() > 1) ? fromPosition.at(0) += ",\n" : fromPosition.at(0) += "\n";
           fromPosition.at(0) += fromPosition.at(1);
           std::fstream outFile(filename.c_str(), std::ios_base::out);
           outFile.write(fromPosition.at(0).c_str(),static_cast<long>(fromPosition.at(0).length()));
           outFile.close();
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
std::vector<std::string> json::SplitFileFromPosition(const std::string& filename, size_t position)
{
    std::ifstream file(filename.c_str(),std::ios_base::in);
    char c[1]{};
    std::string beginOfFile, endOfFile;
    while (file.get(c[0])) {
        auto pos = file.tellg();
        if (pos <= position)
        {
            beginOfFile.push_back(c[0]);
        }
        else
        {
            endOfFile.push_back(c[0]);
        }
    }
    file.close();
    std::vector<std::string> data;
    data.push_back(beginOfFile);
    data.push_back(endOfFile);
    return data;
}
std::string json::GenerateMemberString(const std::vector<std::pair<type, args>> &data,const std::string& objName, std::string substr)
{
    bool setNameOnce = false;
    for (const auto& member : data)
    {
        std::string arrayName = member.first;
        if (not setNameOnce)
        {
            substr += "\"" + arrayName + "\"" + ":[" + "\n" + "{\"" + objName + "\":\"" + member.second + "\"},\n";
            setNameOnce = true;
        }
        else {
            substr += "{\"" + objName + "\":\"" + member.second + "\"},\n";
        }
    }
    return substr;
}


} //namespace json
