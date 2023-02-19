#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace graph {

class CmakeParser {
public:
    CmakeParser()=default;
    ~CmakeParser()=default;
    std::vector<std::string> ParseCmakeFile(const std::string& cmakeFile);
private:
    std::vector<std::string> dependencyFiles_;
};

} //namespace graph
