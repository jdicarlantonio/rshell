set (CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(rshell
    src/executable.cpp
    src/semicolon.cpp
    src/connector.cpp
    src/and.cpp
    src/or.cpp
    src/shell.cpp
    src/input.cpp
    src/builtin.cpp
    src/pipe.cpp
    src/inputredir.cpp
    src/outputredir.cpp
    src/outputappend.cpp
    src/main.cpp
)

ADD_EXECUTABLE(test
    tests/test.cpp
    src/executable.cpp
    src/semicolon.cpp
    src/connector.cpp
    src/input.cpp
    src/and.cpp
    src/or.cpp
    src/builtin.cpp
    src/inputredir.cpp
    src/outputredir.cpp
    src/outputappend.cpp
    src/pipe.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
