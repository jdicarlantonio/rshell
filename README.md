# rshell
A very basic implementation of BASH. Written in C++ using the composite design pattern.

## Installation
```
git clone https://github.com/cs100/assignment-1-lost.git
cd assignment-1-lost
cmake .
make
```

Note: to get googletest use
```
git clone -recursive https://github.com/cs100/assignment-1-lost.git
```

## Known Bugs
* Right now, if entering a command that has an executable that fails, you will need to enter `exit` multiple times to exit the shell. This seems to be a problem with forking.
