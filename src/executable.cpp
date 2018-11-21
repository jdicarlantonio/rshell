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
bool Executable::execute()
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
