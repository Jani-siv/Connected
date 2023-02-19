#include "../CmakeParser.hpp"
#include <gtest/gtest.h>
#include <filesystem>

namespace graph::tests{

class CmakeParserTests : public testing::Test
{
public:
    void SetUp() override {};
    void TearDown() override {};
};

TEST_F(CmakeParserTests, RunWithoutFile)
{
    CmakeParser parser;
    std::vector<std::string> test = parser.ParseCmakeFile("test");
    EXPECT_EQ(true,test.empty());
};

TEST_F(CmakeParserTests, RunWithFile)
{
    CmakeParser parser;
    std::string testablePath = "/tmp/testable";
    std::fstream file(testablePath.c_str(), std::ios_base::out);
    std::vector<std::string> test = parser.ParseCmakeFile(testablePath);
    EXPECT_EQ(false,test.empty());
    remove(testablePath.c_str());
};

} //namespace graph::tests
