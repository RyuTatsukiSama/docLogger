cmake_minimum_required(VERSION 3.15)
project(rLogger_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# dynamic libray logger
add_library(docLogger SHARED
    "./src/Logger/LoggerSeverity.cpp"
    "./src/Logger/include/LoggerSeverity.h"
    "./src/Logger/LoggerOptions.cpp"
    "./src/Logger/include/LoggerOptions.h"
    "./src/Logger/Logger.cpp"
    "./src/Logger/Logger_severityMethods.cpp"
    "./src/Logger/include/Logger.h"
    "./src/TaskManager/taskManager.cpp"
    "./src/TaskManager/taskManager.h"
    "./src/Logger/include/DLL_API.h"
)

target_include_directories(docLogger PUBLIC "./src/Logger/include")

target_compile_definitions(docLogger PRIVATE CMAKEDLL_EXPORTS)

add_executable(TaskManager "./src/TaskManager/taskManager.cpp" "./src/TaskManager/main.cpp")
target_link_libraries(TaskManager PRIVATE docLogger)

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
target_link_libraries(UnitTests PRIVATE docLogger gtest gmock gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)

# rViewerLog Executable
add_executable(docViewerLog "./docViewerLog/docViewerLog.cpp" "./docViewerLog/icon.rc")