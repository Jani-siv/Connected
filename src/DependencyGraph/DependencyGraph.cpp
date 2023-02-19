#include "DependencyGraph.hpp"
#include "lib/json/json.h"

namespace graph{

void DependencyGraph::CreateGraph(const std::string& cmakeFile)
{
    std::string var = "test", arg = "1", filename = "object.json";
    std::pair<std::string,std::string> dataField(var,arg);
    std::vector<std::pair<std::string, std::string>> container;
    container.push_back(dataField);
    json::json::AddObjectsToJsonFile(filename, container);
}

}
