# rLogger

## Description

This is a logger project made by RyuTatsukiSama ( and a lot of help from Epharos 🙏 ) made for C++ with CMake.

For now if you want to use it import the files of the " src/rLogger " folder in your project, or you can open the project with CMake to compile the files into a .lib file and add it to your project.

## Short explanation

In this project there is 3 .exe that are created with CMake :

1. The TaskManagerApp.exe : Actually use to make free test with the rLogger. But in the end it will be a little application to test the logger.

2. Unit_Test.exe : Run all the unit tests of the logger.

3. rViewerLog.exe : The rLogger use ANSI color system, this make the .log file that come out of it a little ugly. But with this no problem since it display the file content into a console window.

With all of this, you have also the clearLog.bat. It simply delete of the .log file in his folder and the subfolder, if you don't want to have an excess amount of .log file when you are running test in your code.

## Futures Update

- [ ] Finish Task Manager App
- [x] Writing all the unit test
- [ ] Documentations ( will be available [here](https://github.com/RyuTatsukiSama/rLogger/blob/main/Documentation.md) )
- [x] Commentary in the code in logger
- [ ] Commentary in the code in Task Manager App
- [ ] Commentary in the code in Unit Test
- [ ] Rename the project
- [ ] Put all the code in a namespace
- [ ] Make a realease to make it easy to download it
- [ ] Make it a .dll instead of a .lib
- [ ] Export the rLogger in other languages
- [ ] Multi os support
- [ ] Stacktrace when c++ 23 will be available
