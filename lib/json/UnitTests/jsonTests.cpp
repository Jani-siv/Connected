#include "../json.h"
#include <gtest/gtest.h>
#include <fstream>

namespace json::test {

std::vector<std::pair<std::string,std::string>> GenerateData(std::string data, std::string arg)
{
    std::pair<std::string,std::string>emptyPair(data,arg);
    std::vector<std::pair<std::string,std::string>>container;
    container.push_back(emptyPair);
    return container;
}

std::pair<std::string,std::string> GeneratePairData(std::string data, std::string arg)
{
    std::pair<std::string,std::string>emptyPair(data,arg);
    return emptyPair;
}

class JsonTests : public testing::Test
{
public:
    void SetUp() override {

    };
    void TearDown() override {};
    const std::string filename_ ="objectData.json";
};

TEST_F(JsonTests, EmptyContainer)
{
    std::string empty;
    std::vector<std::pair<std::string,std::string>> container;// = GenerateData(empty,empty);
    json::json::AddObjectsToJsonFile(filename_, container);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    EXPECT_FALSE(file.is_open());
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, FirstDataFieldEmpty)
{
    std::string empty;
    std::vector<std::pair<std::string,std::string>> container = GenerateData(empty,"empty");
    json::json::AddObjectsToJsonFile(filename_, container);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    EXPECT_FALSE(file.is_open());
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, ValidOneObjectData)
{
    std::vector<std::pair<std::string,std::string>> container = GenerateData("empty","empty");
    json::json::AddObjectsToJsonFile(filename_, container);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    EXPECT_TRUE(file.is_open());
    std::string dataFromJson;
    while(not file.eof())
    {
        std::getline(file,dataFromJson);
    }
    EXPECT_EQ("{ empty : empty }",dataFromJson);
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, ValidTwoObjectData)
{
    std::vector<std::pair<std::string,std::string>> container = GenerateData("empty","empty");
    container.push_back(GeneratePairData("second","second"));
    json::json::AddObjectsToJsonFile(filename_, container);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    EXPECT_TRUE(file.is_open());
    std::string dataFromJson;
    int count = 1;
    while(not file.eof())
    {
        std::getline(file,dataFromJson);
        if (count == 1)
        {
            EXPECT_EQ("{ empty : empty },",dataFromJson);
            count++;
        }
        else
            EXPECT_EQ("{ second : second }",dataFromJson);
    }
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, TwoObjectHaveSameNameNotAddedToFile)
{
    std::vector<std::pair<std::string,std::string>> container = GenerateData("empty","empty");
    container.push_back(GeneratePairData("second","second"));
    container.push_back(GeneratePairData("second","third"));
    json::json::AddObjectsToJsonFile(filename_, container);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    EXPECT_TRUE(file.is_open());
    std::string dataFromJson;
    int count = 1;
    while(not file.eof())
    {
        std::getline(file,dataFromJson);
        if (count == 1)
        {
            EXPECT_EQ("{ empty : empty },",dataFromJson);
            count++;
        }
        else
            EXPECT_EQ("{ second : second }",dataFromJson);
            count++;
    }
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, AddTwoTimesSameObject)
{
    std::vector<std::pair<std::string,std::string>> container = GenerateData("empty","empty");
    container.push_back(GeneratePairData("second","second"));
    json::json::AddObjectsToJsonFile(filename_, container);
    json::json::AddObjectsToJsonFile(filename_, container);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    EXPECT_TRUE(file.is_open());
    std::string dataFromJson;
    int count = 1;
    while(not file.eof())
    {
        std::getline(file,dataFromJson);
        if (count == 1)
        {
            EXPECT_EQ("{ empty : empty },",dataFromJson);
            count++;
        }
        else
            EXPECT_EQ("{ second : second }",dataFromJson);
        count++;
    }
    file.close();
    remove(filename_.c_str());
};

} // namespace json::test