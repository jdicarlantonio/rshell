# rshell
A very basic command shell implementation. Written in C++ using the composite design pattern.

## Overview
In this shell implementation, you can enter any commands that are in your path. I.E. `ls -la`, `mkdir tempdir`, etc, and it contains the `test` command as a built in. It runs in your terminal emulator and can be exited by typing in the `exit` command (see bugs). Now functional with `|`, `<`, `>`, and `>>`.

## Installation
```
git clone --recursive https://github.com/cs100/assignment-1-lost.git
cd assignment-1-lost
cmake3 .
make
./rshell
```
**NOTE:** `cmake3` is needed for the hammer server.

To get googletest, run the following before building
```
git submodule init
git submodule update
```

## Known Bugs
* When using precedence, there are some cases where, when all commands aren't wrapped in parentheses, the commands not in parentheses will not execute properly
* Entering semicolons with a space before will not work, I.E. "ls -la ; mkdir temp", will not execute properly
* Connectors expect a left hand command and a right hand command. If you try to put a command such as `ls -l &&` it will execute the first command and show an error.
* Beginning a command with '&&' does not return an error as it should, but the commands after work as if it was never there
