# rshell
A very basic implementation of BASH. Written in C++ using the composite design pattern.

## Installation
```
git clone --recursive https://github.com/cs100/assignment-1-lost.git
cd assignment-1-lost
cmake .
make
```

## Known Bugs
* If entering a command with an executable that fails, you will need to enter `exit` multiple times to exit the shell. This seems to be a problem with forking, since the number of times you need to press exit depends on how many commands failed.
* Connectors expect a left hand command and a right hand command. If you try to put a command such as `ls -l &&` it will execute the first command and show an error.
