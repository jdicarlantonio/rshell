#include "../header/executable.h"

#include <iostream>

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
//    pid_t waitPid;
    // status of child (for waitpid())
    int status;
   
    // create child process 
    childPid = fork();
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
            perror("Command not recognized");
            successful = false;
        }
    }
    else if(childPid == -1)
    {
        perror("fork error");
        successful = false;
    }
    else
    {
        // wait for child to get its shit together
        if(waitpid(childPid, &status, WUNTRACED) == -1)
        {
            perror("Command not found");
            successful = false;
        }
    }

    return successful;
}
