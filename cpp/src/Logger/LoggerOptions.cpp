#include "doc/LoggerOptions.h"
#include <format>
#include <filesystem>

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

            if (!std::filesystem::exists("docLogs")) // If the directory "docLogs" don't exist create it
            {
                std::filesystem::create_directory("docLogs");
            }

            std::string pathFile = std::format("docLogs/{}.log", m_fileName);

            if (std::filesystem::exists(pathFile)) // if a file with this name already exist, add "-previous" at the end of the old one
            {
                std::filesystem::rename(pathFile, std::format("docLogs/{}-previous.log", m_fileName));
            }

            m_fileStream = new std::ofstream(pathFile); // open a stream to the file
        }
    }

    LoggerOptions::~LoggerOptions()
    {
        if (this == gOpts && m_fileStream)
        {
            delete m_fileStream;
            m_fileStream = nullptr;
        }
    }

    LoggerOptions::LoggerOptions(const LoggerOptions &other) : m_outputConsole(other.m_outputConsole),
                                                               m_outputFile(other.m_outputFile),
                                                               m_fileName(other.m_fileName),
                                                               m_timeProvider(other.m_timeProvider),
                                                               m_fileStream(other.m_fileStream)
    {
    }

    LoggerOptions &LoggerOptions::operator=(const LoggerOptions &other)
    {
        return *this = LoggerOptions(other);
    }

    // TODO : Undestand this
    LoggerOptions::LoggerOptions(LoggerOptions &&other) noexcept : m_outputConsole(std::exchange(other.m_outputConsole, false)),
                                                                   m_outputFile(std::exchange(other.m_outputFile, false)),
                                                                   m_fileName(std::move(other.m_fileName)),
                                                                   m_timeProvider(std::move(other.m_timeProvider)),
                                                                   m_fileStream(std::exchange(other.m_fileStream, nullptr))
    {
    }

    // TODO : Undestand this
    LoggerOptions &LoggerOptions::operator=(LoggerOptions &&other) noexcept
    {
        std::swap(m_outputConsole, other.m_outputConsole);
        std::swap(m_outputFile, other.m_outputFile);
        std::swap(m_fileName, other.m_fileName);
        std::swap(m_timeProvider, other.m_timeProvider);
        std::swap(m_fileStream, other.m_fileStream);
        return *this;
    }

    void setGlobalLoggerOptions(const LoggerOptions &_options)
    {
        if (!gOpts)
            gOpts = new LoggerOptions(_options);
        else
        {
            std::cerr << "gOpts is already set" << std::endl;
        }
    }
}