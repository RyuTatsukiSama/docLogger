#ifndef RLOGGEROPTIONS_H
#define RLOGGEROPTIONS_H

#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <fstream>
#include "DLL_API.h"

namespace doc
{
    /// @brief This class is used to give some parameter to the logger for a more quick configuration of it.
    /// Work with the OptionsBuilder class. For more explanation https://github.com/RyuTatsukiSama/docLogger/blob/main/Documentation.md
    class DLL_API LoggerOptions
    {
    private:
        LoggerOptions(const bool _outputConsole,
                      const bool _outputFile,
                      const std::string _fileName,
                      std::function<std::chrono::system_clock::time_point()> _timeProvider);

        bool m_outputConsole;
        bool m_outputFile;
        std::string m_fileName;
        std::ofstream *m_fileStream;
        std::function<std::chrono::system_clock::time_point()> m_timeProvider;

    public:
        LoggerOptions() = default;
        ~LoggerOptions();

        LoggerOptions(const LoggerOptions &other);            // copy constructor
        LoggerOptions &operator=(const LoggerOptions &other); // copy assignment

        LoggerOptions(LoggerOptions &&other) noexcept;            // move constructor
        LoggerOptions &operator=(LoggerOptions &&other) noexcept; // move assignment

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

        /// @brief This class is use to have default member for the option.
        /// For more explanation https://github.com/RyuTatsukiSama/docLogger/blob/main/Documentation.md
        class OptionsBuilder
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

            /// @brief Set if you want your log to be display automaticaly in the console
            /// If you want the default parameter ( true ), no need to call this method
            /// @return Instance of the builder, with that you can call the set methods and th build methods on the same line
            OptionsBuilder &setOutputConsole(bool _oc)
            {
                outputConsole = _oc;
                return *this;
            }

            /// @brief Set if you want your log to be display automaticaly in the file
            /// If you want the default parameter ( true ), no need to call this method
            /// @return Instance of the builder, with that you can call the set methods and th build methods on the same line
            OptionsBuilder &setOutputFile(bool _of)
            {
                outputFile = _of;
                return *this;
            }

            /// @brief Set if you want a specific name for your log file
            /// If you want the default parameter ( YYYY-mm-dd_HH-MM-SS ), from the timeProvider, no need to call this method
            /// @return Instance of the builder, with that you can call the set methods and th build methods on the same line
            OptionsBuilder &setFileName(std::string _name)
            {
                fileName = _name;
                return *this;
            }

            /// @brief Set if you want your log to have a specific timeProvider ( use mainly for test )
            /// If you want the default parameter ( now of your time zone ), no need to call this method
            /// @param _tp A function or lambda that return a std::chrono::system_clock::time_point()
            /// @return Instance of the builder, with that you can call the set methods and th build methods on the same line
            OptionsBuilder &setTimeProvider(std::function<std::chrono::system_clock::time_point()> _tp)
            {
                timeProvider = std::move(_tp);
                return *this;
            }

#pragma endregion

            /// @brief Create a instance of LoggerOptions with the members in the instance of OptionsBuilder
            /// @return The created instance of LoggerOptions
            LoggerOptions build()
            {
                return LoggerOptions(outputConsole, outputFile, fileName, timeProvider);
            }
        };
    };

    /// @brief It is the value by default of the LoggerOptions used by the Logger if no LoggerOptions is given, instantiate it before using the Logger. It is like the default configuration you want for your logger instances
    extern const LoggerOptions *gOpts;

    DLL_API void setGlobalLoggerOptions(const LoggerOptions &_options);
}
#endif // !RLOGGEROPTIONS_H