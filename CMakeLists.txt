cmake_minimum_required(VERSION 3.15)
project(rLog_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fichiers sources
set(SOURCES
    "main.cpp"
)

add_executable(rLog_cpp ${SOURCES})