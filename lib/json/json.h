#pragma once

#include <vector>
#include <string>

namespace json{
using containerDataType = std::vector<std::pair<std::string,std::string>>;
class json {
public:
    static void AddObjectsToJsonFile(const std::string& filename, containerDataType& data);
    static void AppObjectToJsonFile(const std::string& filename, const std::string& objName,
                                    const std::string& data);
private:
    static bool IsContainerDataValid(const containerDataType& data);
    static std::string GenerateObjectToFile(const std::string& filename, containerDataType& data);
    static std::string &RemoveTrailingNlAndComma(std::string &tempData);
    static size_t FindObjectPositionFromFile(const std::string &filename, const std::string &objectname);
};

} //namespace json