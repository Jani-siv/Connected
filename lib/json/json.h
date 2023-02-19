#pragma once

#include <vector>
#include <string>

namespace json{
using containerDataType = std::vector<std::pair<std::string,std::string>>;
using args = std::string;
using type = std::string;

class json {
public:
    static void AddObjectsToJsonFile(const std::string& filename, containerDataType& data);
    [[maybe_unused]] static void AppObjectMembersToJsonFile(const std::string& filename, const std::string& objName,
                                           const std::vector<std::pair<type,args>>& data);
private:
    static std::vector<std::string> SplitFileFromPosition(const std::string& filename, size_t position);
    static std::string GenerateMemberString(const std::vector<std::pair<type, args>> &data,const std::string& objName, std::string substr);
    static bool IsContainerDataValid(const containerDataType& data);
    static std::string GenerateObjectToFile(const std::string& filename, containerDataType& data);
    static size_t FindObjectPositionFromFile(const std::string &filename, const std::string &objectname);
};

} //namespace json