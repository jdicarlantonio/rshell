#include "gtest/gtest.h"

#include "../header/executable.h"

TEST(ExecutableTest, lsTest)
{
    std::vector<char*> commandOneArg;
    commandOneArg.push_back("ls");
    commandOneArg.push_back("-l");
    commandOneArg.push_back(NULL);
    
    std::vector<char*> commandMultipleArgs;
    commandMultipleArgs.push_back("ls");
    commandMultipleArgs.push_back("-la");
    commandMultipleArgs.push_back(NULL);
    
    Executable* multipleArgs = new Executable(commandMultipleArgs); 
    Executable* oneArg = new Executable(commandOneArg); 

    EXPECT_EQ(true, multipleArgs->execute());
    EXPECT_EQ(true, oneArg->execute());

    delete multipleArgs;
    delete oneArg;
}

TEST(ExecutableTest, FileManip)
{
    std::vector<char*> mkdirCommand;
    mkdirCommand.push_back("mkdir");
    mkdirCommand.push_back("TestDir");
    mkdirCommand.push_back(NULL);
    
    std::vector<char*> rmRecursive;
    rmRecursive.push_back("rm");
    rmRecursive.push_back("-rf");
    rmRecursive.push_back("TestDir");
    rmRecursive.push_back(NULL);

    Executable* mkdirExec = new Executable(mkdirCommand);
    Executable* rmExec = new Executable(rmRecursive);

    EXPECT_EQ(true, mkdirExec->execute());
    EXPECT_EQ(true, rmExec->execute());

    delete mkdirExec;
    delete rmExec;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
