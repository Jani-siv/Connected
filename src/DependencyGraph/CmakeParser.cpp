#include "CmakeParser.hpp"

namespace graph {

std::vector<std::string> CmakeParser::ParseCmakeFile(const std::string& cmakeFile)
{
    std::fstream file(cmakeFile.c_str(),std::ios_base::in);
    if (file.is_open())
    {
        dependencyFiles_.push_back(cmakeFile);
        file.close();
    }
    return dependencyFiles_;
}

} //namespace graph
