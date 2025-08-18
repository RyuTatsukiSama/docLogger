#include <string>

typedef struct rLoggerOptions
{
    std::string threadName = "Main";
    bool outputConsole = true;
    bool outputFile = true;
    std::string fileName = "";
} rLoggerOptions;