#pragma once

class cLogger
{
public:
    enum class LogLevel
    {
        Error = 0,
        Warning,
        Info
    };
    explicit cLogger(LogLevel logLevel = LogLevel::Error);
    void log(LogLevel logLevel, const char* message) const;
private:
    LogLevel m_logLevel = LogLevel::Error;
};
