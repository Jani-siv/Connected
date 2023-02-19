#pragma once
#include <string>
#include <vector>

#include "CmakeParser.hpp"
#include "EntityCreator.hpp"

namespace graph{

class DependencyGraph {
public:
    DependencyGraph()=default;
    ~DependencyGraph()=default;
    void CreateGraph(const std::string& cmakeFile);
private:
    std::vector<std::string> filepaths_;
    CmakeParser parser_;
    EntityCreator creator_;
};

}
