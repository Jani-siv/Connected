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

bool IsEmptyLine(const std::string& testable)
{
    return (testable.length() == 0);
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
    std::vector<std::pair<std::string,std::string>> container;
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
    while(not file.eof()) {
        std::getline(file, dataFromJson);
        if (not IsEmptyLine(dataFromJson)) {
            EXPECT_EQ("{ empty : empty }", dataFromJson);
        }
    }
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
            EXPECT_EQ("{ empty : empty }",dataFromJson);
            count++;
        }
        else
            if (not IsEmptyLine(dataFromJson)){
            EXPECT_EQ("{ second : second }",dataFromJson);}
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
            EXPECT_EQ("{ empty : empty }",dataFromJson);
            count++;
        }
        else
        {
        if (not IsEmptyLine(dataFromJson)){
            EXPECT_EQ("{ second : second }",dataFromJson);
            count++;}
        }
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
            EXPECT_EQ("{ empty : empty }",dataFromJson);
            count++;
        }
        else {
            if (not IsEmptyLine(dataFromJson)){
                EXPECT_EQ("{ second : second }", dataFromJson);
            count++;}
        }
    }
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, AddNewObjectToExitingJsonFile)
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
            EXPECT_EQ("{ empty : empty }",dataFromJson);
            count++;
        }
        else {
            if(not IsEmptyLine(dataFromJson)){
                EXPECT_EQ("{ second : second }", dataFromJson);
            count++;}
        }
    }
    file.close();
    remove(filename_.c_str());
};

TEST_F(JsonTests, AddMemberToObject)
{
    std::vector<std::pair<std::string,std::string>> container = GenerateData("JsonClass","empty");
    container.push_back(GeneratePairData("second","second"));
    json::json::AddObjectsToJsonFile(filename_, container);

    std::string dataFromJson;
    std::vector<std::pair<type,args>> member;
    std::pair<type,args>memberData("dependency","dateClass");
    member.push_back(memberData);
    json::AppObjectMembersToJsonFile(filename_, "JsonClass", member);
    std::fstream file(filename_.c_str(), std::ios_base::in);
    std::string testable;
    int foundDep = 0;
    int foundMember = 0;
    while(not file.eof())
    {
        std::getline(file,testable);
        if (testable.find("\"dependency\":[") != std::string::npos)
        {
            foundDep++;
        }
        if (testable.find("{\"JsonClass\":\"dateClass\"}") != std::string::npos)
        {
            foundMember++;
        }
    }
    EXPECT_EQ(foundMember,1);
    EXPECT_EQ(foundDep,1);
    file.close();
    member.push_back(memberData);
    json::AppObjectMembersToJsonFile(filename_, "second", member);
    file.open(filename_.c_str(), std::ios_base::in);
    testable.clear();
    foundDep = 0;
    foundMember = 0;
    while(not file.eof())
    {
        std::getline(file,testable);
        if (testable.find("\"dependency\":[") != std::string::npos)
        {
            foundDep++;
        }
        if (testable.find("\"second\":\"dateClass\"") != std::string::npos)
        {
            foundMember++;
        }
    }
    EXPECT_EQ(foundMember,2);
    EXPECT_EQ(foundDep,2);
    file.close();
    remove(filename_.c_str());
};

} // namespace json::test