#include "gtest/gtest.h"

#include "../header/executable.h"
#include "../header/connector.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/semicolon.h"

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
    mkdirCmd.push_back("mkdir");
    mkdirCmd.push_back("TestDir");

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
    mkdirTest.push_back("mkdir");
    mkdirTest.push_back("TestDir2");
    
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

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
