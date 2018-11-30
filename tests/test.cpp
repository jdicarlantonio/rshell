#include "gtest/gtest.h"

#include "../header/executable.h"
#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"
#include "../header/input.h"
#include "../header/builtin.h"

#include <vector>
#include <string>

TEST(ParserTest, SingleCommand)
{
    Input input;
    std::vector<std::string> cmd = {
        "ls",
        "-la"
    };

    input.tokenize("ls -la");

    EXPECT_EQ(cmd, input.getTokens());
}

TEST(ParserTest, SemiColon)
{
    Input input;
    std::vector<std::string> cmd = {
        "ls",
        "-la",
        ";",
        "pwd"
    };

    input.tokenize("ls -la; pwd");

    EXPECT_EQ(cmd, input.getTokens());
}

TEST(ParserTest, And)
{
    Input input;
    std::vector<std::string> cmd = {
        "ls",
        "-la",
        "&&",
        "pwd"
    };

    input.tokenize("ls -la && pwd");

    EXPECT_EQ(cmd, input.getTokens());
}

TEST(ParserTest, Or)
{
    Input input;
    std::vector<std::string> cmd = {
        "ls",
        "-la",
        "||",
        "pwd"
    };

    input.tokenize("ls -la || pwd");

    EXPECT_EQ(cmd, input.getTokens());
}

TEST(ParserTest, MultipleConnectors)
{
    Input input;
    std::vector<std::string> cmd = {
        "ls",
        "-la",
        "||",
        "pwd",
        ";",
        "ls",
        "&&",
        "pwd"
    };

    input.tokenize("ls -la || pwd; ls && pwd");

    EXPECT_EQ(cmd, input.getTokens());
}

TEST(ExecutableTest, lsTest)
{
    std::vector<std::string> commandOneArg;
    commandOneArg.push_back("ls");
    commandOneArg.push_back("-l");
    
    std::vector<std::string> commandMultipleArgs;
    commandMultipleArgs.push_back("ls");
    commandMultipleArgs.push_back("-la");
 
    Executable* multipleArgs = new Executable(commandMultipleArgs); 
    Executable* oneArg = new Executable(commandOneArg); 

    EXPECT_EQ(true, multipleArgs->execute());
    EXPECT_EQ(true, oneArg->execute());

    delete multipleArgs;
    delete oneArg;
}

TEST(ExecutableTest, FileManip)
{
    std::vector<std::string> mkdirCommand;
    mkdirCommand.push_back("mkdir");
    mkdirCommand.push_back("TestDir");

    
    std::vector<std::string> rmRecursive;
    rmRecursive.push_back("rm");
    rmRecursive.push_back("-rf");
    rmRecursive.push_back("TestDir");


    Executable* mkdirExec = new Executable(mkdirCommand);
    Executable* rmExec = new Executable(rmRecursive);

    EXPECT_EQ(true, mkdirExec->execute());
    EXPECT_EQ(true, rmExec->execute());

    delete mkdirExec;
    delete rmExec;
}

TEST(ConnectorTest, OneConnector)
{
    std::vector<std::string> lsCmd;
    lsCmd.push_back("ls");
    lsCmd.push_back("-la");

    std::vector<std::string> mkdirCmd;
    mkdirCmd.push_back("pwd");

    Executable* lsExec = new Executable(lsCmd);
    Executable* mkdirExec = new Executable(mkdirCmd);

    Connector* semicolon = new SemiColon(lsExec, mkdirExec);

    EXPECT_EQ(true, semicolon->execute());

    delete lsExec;
    delete mkdirExec;
    delete semicolon;
}

TEST(RecursiveTest, MultipleConnectors)
{
    std::vector<std::string> lsCmd;
    lsCmd.push_back("ls");
    lsCmd.push_back("-a");
    
    std::vector<std::string> echoHello;
    echoHello.push_back("echo");
    echoHello.push_back("hello");
    
    Executable* lsExec = new Executable(lsCmd);
    Executable* echoHelloExec = new Executable(echoHello);

    Connector* semicolon = new SemiColon(lsExec, echoHelloExec);

    std::vector<std::string> mkdirTest;
    mkdirTest.push_back("pwd");
    
    Executable* mkdirTestExec = new Executable(mkdirTest);

    Connector* andCon = new And(semicolon, mkdirTestExec);
    
    std::vector<std::string> echoWorld;
    echoHello.push_back("echo");
    echoHello.push_back("world");
    
    Executable* echoWorldExec = new Executable(echoWorld);
    
    Connector* orCon = new Or(andCon, echoWorldExec);

    EXPECT_EQ(true, orCon->execute());

    delete lsExec;
    delete semicolon;
    delete mkdirTestExec;
    delete echoHelloExec;
    delete andCon;
    delete echoWorldExec;
    delete orCon;
}

TEST(BuiltInTest, TestCommandTrue)
{
    std::vector<std::string> testCmd;
    testCmd.push_back("test");
    testCmd.push_back("-e");
    testCmd.push_back("dummyfile");

    Executable* testTest = new test(testCmd);

    EXPECT_EQ(false, testTest->execute());

    delete testTest;
}

TEST(BuiltInTest, TestCommandFalse)
{
    std::vector<std::string> testCmd;
    testCmd.push_back("test");
    testCmd.push_back("-e");
    testCmd.push_back("test");

    Executable* testTest = new test(testCmd);

    EXPECT_EQ(true, testTest->execute());

    delete testTest;
}

TEST(BuiltInTest, TestCommandArguments)
{
    std::vector<std::string> testCmd;
    testCmd.push_back("test");
    testCmd.push_back("-e");
    testCmd.push_back("test");
    Executable* eTest = new test(testCmd);

    std::vector<std::string> testCmd2;
    testCmd2.push_back("test");
    testCmd2.push_back("-e");
    testCmd2.push_back("bin");
    Executable* dTest = new test(testCmd2);

    std::vector<std::string> testCmd3;
    testCmd2.push_back("test");
    testCmd2.push_back("-f");
    testCmd2.push_back("Makefile");
    Executable* fTest = new test(testCmd3);

    EXPECT_EQ(true, eTest->execute());
    EXPECT_EQ(true, dTest->execute());
    EXPECT_EQ(false, fTest->execute());
}

TEST(BuiltInTest, SymbolicTestCommand)
{
    std::vector<std::string> symTest;
    symTest.push_back("[");
    symTest.push_back("-e");
    symTest.push_back("]");

    Executable* tester = new test(symTest);
   
    EXPECT_EQ(false, tester->execute());
}

TEST(BuiltInTest, SymbolicTestCommandOnFile)
{
    std::vector<std::string> symTest;
    symTest.push_back("[");
    symTest.push_back("-e");
    symTest.push_back("test");
    symTest.push_back("]");

    Executable* tester = new test(symTest);
   
    EXPECT_EQ(true, tester->execute());
}

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
