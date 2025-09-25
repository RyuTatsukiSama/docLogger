#ifndef RLOGGEROPTIONS_H
#define RLOGGEROPTIONS_H

#include <string>
#include <functional>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>

class rLoggerOptions
{
private:
    rLoggerOptions(const bool _outputConsole,
                   const bool _outputFile,
                   const std::string _fileName,
                   std::function<std::chrono::system_clock::time_point()> _timeProvider);

    bool m_outputConsole;
    bool m_outputFile;
    std::string m_fileName;
    std::ofstream *m_fileStream;
    std::function<std::chrono::system_clock::time_point()> m_timeProvider;

public:
    ~rLoggerOptions(); // TODO : rule of five (https://en.cppreference.com/w/cpp/language/rule_of_three.html)

#pragma region Get methods

    bool isOutputConsole(void) const
    {
        return m_outputConsole;
    }

    bool isOutputFile(void) const
    {
        return m_outputFile;
    }

    std::string getFileName(void) const
    {
        return m_fileName;
    }

    std::ofstream *getFileStream() const
    {
        return m_fileStream;
    }

    std::function<std::chrono::system_clock::time_point()> getTimeProvider(void) const
    {
        return m_timeProvider;
    }

#pragma endregion

    class Builder
    {
    private:
        bool outputConsole = true;
        bool outputFile = true;
        std::string fileName = "";
        std::function<std::chrono::system_clock::time_point()> timeProvider = []()
        {
            return std::chrono::zoned_time{
                std::chrono::current_zone(),
                std::chrono::system_clock::now()};
        };

    public:
#pragma region Set methods

        Builder &setOutputConsole(bool _oc)
        {
            outputConsole = _oc;
            return *this;
        }
        Builder &setOutputFile(bool _of)
        {
            outputFile = _of;
            return *this;
        }
        Builder &setFileName(std::string _name)
        {
            fileName = _name;
            return *this;
        }
        Builder &setTimeProvider(std::function<std::chrono::system_clock::time_point()> _tp)
        {
            timeProvider = std::move(_tp);
            return *this;
        }

#pragma endregion

        rLoggerOptions build()
        {
            return rLoggerOptions(outputConsole, outputFile, fileName, timeProvider);
        }
    };
};

extern const rLoggerOptions *gOpts;

#endif // !RLOGGEROPTIONS_H