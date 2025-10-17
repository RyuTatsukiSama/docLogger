#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include "../rLogger/rLogger.h"
#undef DOC_LOG_THRESHOLD
#define DOC_LOG_THRESHOLD rLoggerSeverity::Info
#include <thread>
#include <string>

class TaskManager
{
private:
    /* data */
public:
    TaskManager(/* args */);
    ~TaskManager();
};

#endif // !TASKMANAGER_H