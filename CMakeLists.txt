set (CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(tests/googletest)

ADD_EXECUTABLE(rshell
    src/executable.cpp
    src/semicolon.cpp
    src/connector.cpp
    src/and.cpp
    src/or.cpp
    src/shell.cpp
    src/input.cpp
    src/main.cpp
)

ADD_EXECUTABLE(test
    tests/test.cpp
    src/executable.cpp
    src/semicolon.cpp
    src/connector.cpp
    src/and.cpp
    src/or.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
