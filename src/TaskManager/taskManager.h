#include <iostream>
#include "../Logger/rLogger.h"
#include <thread>
#include <string>

thread_local static std::string threadName = "";