#include "rLoggerOptions.h"

namespace doc
{
    const LoggerOptions *gOpts = nullptr;

    LoggerOptions::LoggerOptions(const bool _outputConsole,
                                   const bool _outputFile,
                                   const std::string _fileName,
                                   std::function<std::chrono::system_clock::time_point()> _timeProvider) : m_outputConsole(_outputConsole),
                                                                                                           m_outputFile(_outputFile),
                                                                                                           m_fileName(_fileName),
                                                                                                           m_timeProvider(_timeProvider),
                                                                                                           m_fileStream(nullptr)
    {
        if (_outputFile) // Check if the user want his log to be display into a file
        {
            if (_fileName == "") // if the file name is not set, give him the time from the timeProvider
            {
                std::chrono::time_point now = std::chrono::floor<std::chrono::seconds>(_timeProvider());
                m_fileName = std::format("{:%Y-%m-%d_%H-%M-%S}", now);
            }

            if (!std::filesystem::exists("rLogs")) // If the directory "rLogs" don't exist create it
            {
                std::filesystem::create_directory("rLogs");
            }

            std::string pathFile = std::format("rLogs/{}.log", m_fileName);

            if (std::filesystem::exists(pathFile)) // if a file with this name already exist, add "-previous" at the end of the old one
            {
                std::filesystem::rename(pathFile, std::format("rLogs/{}-previous.log", m_fileName));
            }

            m_fileStream = new std::ofstream(pathFile); // open a stream to the file
        }
    }

    LoggerOptions::~LoggerOptions()
    {
        if (m_fileStream)
        {
            delete m_fileStream;
            m_fileStream = nullptr;
        }
    }
}