set (CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(tests/googletest)

ADD_EXECUTABLE(test
    tests/test.cpp
    src/executable.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
