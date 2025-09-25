#include "rLoggerOptions.h"

const rLoggerOptions *gOpts = nullptr;

rLoggerOptions::rLoggerOptions(const bool _outputConsole,
                               const bool _outputFile,
                               const std::string _fileName,
                               std::function<std::chrono::system_clock::time_point()> _timeProvider) : m_outputConsole(_outputConsole),
                                                                                                       m_outputFile(_outputFile),
                                                                                                       m_fileName(_fileName),
                                                                                                       m_timeProvider(_timeProvider)
{
    if (_outputFile)
    {
        if (_fileName == "")
        {
            std::chrono::time_point now = std::chrono::floor<std::chrono::seconds>(_timeProvider());
            m_fileName = std::format("{:%Y-%m-%d_%H-%M-%S}", now);
        }

        if (!std::filesystem::exists("rLogs"))
        {
            std::filesystem::create_directory("rLogs");
        }

        std::string pathFile = std::format("rLogs/{}.log", m_fileName);

        if (std::filesystem::exists(pathFile))
        {
            std::filesystem::rename(pathFile, std::format("rLogs/{}-previous.log", m_fileName));
        }

        m_fileStream = new std::ofstream(pathFile);
    }
}

rLoggerOptions::~rLoggerOptions()
{
    // TODO : The m_fileStream destroy multiple times
    // delete m_fileStream;
    // m_fileStream = nullptr;
}