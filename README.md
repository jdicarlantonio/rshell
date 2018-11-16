# rshell
A very basic implementation of BASH. Written in C++ using the composite design pattern.

## Overview
In this shell implementation, you can enter any commands that are in your path. I.E. `ls -la`, `mkdir tempdir`, etc. It runs in your terminal emulator and can be exited by typing in the `exit` command (see bugs).

## Installation
```
git clone --recursive https://github.com/cs100/assignment-1-lost.git
cd assignment-1-lost
cmake3 .
make
./rshell
```
**NOTE:** `cmake3` is needed for the hammer server.

## Known Bugs
* If entering a command with an executable that fails, you will need to enter `exit` multiple times to exit the shell. This seems to be a problem with zombie processes, since the number of times you need to press exit depends on how many commands failed. If all commands are successful, exit works perfectly.
* Connectors expect a left hand command and a right hand command. If you try to put a command such as `ls -l &&` it will execute the first command and show an error.
* Beginning a command with '&&' does not return an error as it should, but the commands after work as if it was never there
