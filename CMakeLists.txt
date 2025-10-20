cmake_minimum_required(VERSION 3.15)
project(rLogger_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# static library profiler
add_library(docProfiler
    "./src/Profiler/Profiler.cpp"
    "./src/Profiler/Profiler.h"
    "./src/Profiler/ProfilerTimer.cpp"
    "./src/Profiler/ProfillerTimer.h"
    "./src/Profiler/TraceEvent.h")

# static library logger
add_library(docLoggerLib
    "./src/Logger/LoggerSeverity.cpp"
    "./src/Logger/Include/LoggerSeverity.h"
    "./src/Logger/LoggerOptions.cpp"
    "./src/Logger/Include/LoggerOptions.h"
    "./src/Logger/Logger.cpp"
    "./src/Logger/Logger_severityMethods.cpp"
    "./src/Logger/Include/Logger.h"
    "./src/TaskManager/taskManager.cpp"
    "./src/TaskManager/taskManager.h")
    
target_link_libraries(docLoggerLib PRIVATE docProfiler)

# Task Manager Executable
add_executable(TaskManagerApp "./src/TaskManager/taskManager.cpp" "./src/TaskManager/main.cpp")
target_link_libraries(TaskManagerApp PRIVATE docLoggerLib)

# Unit Test Executable
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(UnitTests "UnitTest/unitTest.cpp" "UnitTest/logSeverityTest.cpp" "UnitTest/docLoggerTest.cpp" "UnitTest/optionsTest.cpp")
target_link_libraries(UnitTests PRIVATE docLoggerLib gtest gmock gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)

# rViewerLog Executable
add_executable(docViewerLog "./docViewerLog/docViewerLog.cpp" "./docViewerLog/icon.rc")