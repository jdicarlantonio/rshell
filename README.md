# rshell
A very basic BASH shell implementation. Written in C++ using the composite design pattern.

## Overview
In this shell, you can enter any commands that are in your path. I.E. `ls -la`, `mkdir tempdir`, etc, and it contains the `test` command as a built in. It runs in your terminal emulator and can be exited by typing in the `exit` command (see bugs). Now functional with `|`, `<`, `>`, and `>>` (see bugs).

## Installation
```
git clone --recursive https://github.com/jdicarlantonio/rshell
cd rshell
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
* Using output redirection sequentially on files, IE, `cat file_1 > file_2 > ... > file_n` will get the contents of the first file into the second instead of the last
* Using pipes and redirection with `&&`, `||`, and `;` uses left to right precedence instead of executing pipe and redirection first 
* Entering semicolons with a space before will not work, I.E. `ls -la ; mkdir temp` will not execute properly
* Connectors expect a left hand command and a right hand command. If you try to put a command such as `ls -l &&` it will execute the first command and show an error.
* Beginning a command with '&&' does not return an error as it should, but the commands after work as if it was never there
