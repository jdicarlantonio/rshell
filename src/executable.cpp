#include "../header/executable.h"

#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

Executable::Executable(StringVec args)
    : Command()
    , argList(args)
{
    
}

Executable::~Executable()
{}

// syscalls are going to go here
// argList should contain the executable name (e.g. ls, cd, ...) first, followed
// by the arguments and filename, why i decided to call is argList, i don't know.
bool Executable::execute()
{
    // keep track of child
    pid_t childPid;
    pid_t waitPid;
    // status of child (for waitpid())
    int status;
   
    // create child process 
    childPid = fork();
    if(childPid == 0) // zero means success
    {
        // we can run execvp
        execvp(argList[0], argList.data());

        // execvp returns => execvp failed 
        // thus we can print an error message and return false
        std::cout << "Unrecognized command\n";

        return false;
    }
    else
    {
        do
        {
            // wait for child to get its shit together
            waitPid = waitpid(childPid, &status, WUNTRACED); 
       
        // wait until process terminates normally or when user "signals" to stop
        // the process 
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return true;
}
