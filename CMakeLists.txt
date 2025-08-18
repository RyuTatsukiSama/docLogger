cmake_minimum_required(VERSION 3.15)
project(rLog_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common Library
add_library(LoggerLib
    "./src/rLogger/rLogger.cpp"
    "./src/rLogger/rLogger.h"
    "./src/rLogger/rLoggerOptions.h"
    "./src/TaskManager/taskManager.cpp"
    "./src/TaskManager/taskManager.h")

# Task Manager Executable
add_executable(TaskManagerApp "./src/TaskManager/taskManager.cpp")
target_link_libraries(TaskManagerApp PRIVATE LoggerLib)

# Unit Test Executable
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

add_executable(UnitTests "UnitTest/unitTest.cpp" "UnitTest/logSeverityTest.cpp" "UnitTest/formatLogTest.cpp")
target_link_libraries(UnitTests PRIVATE LoggerLib gtest_main)