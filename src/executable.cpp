#include "../header/executable.h"

#include <iostream>

#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

Executable::Executable(StringVec args)
    : Command()
    , argList(args)
    , executeSuccess(true)
{
    
}

Executable::~Executable()
{}

// syscalls are going to go here
// argList should contain the executable name (e.g. ls, cd, ...) first, followed
// by the arguments and filename, why i decided to call is argList, i don't know.
bool Executable::execute(int fdin, int fdout)
{
    bool successful = true;
    // keep track of child
    pid_t childPid;
    
    if(argList[0] == "exit")
    {
        exit(0);
    }

    // create child process 
    childPid = fork();
    int errnoSave = errno;
    // status of child (for waitpid())
    int status;
    if(childPid == 0) // zero means success
    {
        // convert strings to char*
        std::vector<char*> args;
        for(auto const& token : argList)
        {
            args.push_back(const_cast<char*>(token.c_str()));
        }
        args.push_back(NULL);
        
        // need to call dup2 here for each file descriptor
        if(dup2(fdin, 0) == -1)
        {
            perror("dup error");
            return false;
        }
        if(dup2(fdout, 1) == -1)
        {
            perror("dup error");
            return false;
        }

        // we can run execvp
        if(execvp(args[0], args.data()) == -1)
        {
            errnoSave = errno;
            successful = false;
            perror("execvp error");

            exit(69); 
        }
    }
    else if(childPid < 0)
    {
        perror("fork error");
        successful = false;
    }
    else
    {
        // wait for child 
        if(waitpid(childPid, &status, 0) < 0)
        {
            perror("wait error");
            successful = false;
        }
    }

    int exitStatus = WEXITSTATUS(status);
    if(exitStatus > 0)
    {
        successful = false;
    }

    return successful;
}

bool Executable::getFilePath(std::string& filepath)
{
    if(argList.size() > 1)
    {
        return false;
    }
    
    filepath = argList[0];
    return true;
}
