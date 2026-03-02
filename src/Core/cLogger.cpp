#include "cLogger.h"

#include <iostream>

cLogger::cLogger(LogLevel logLevel): m_logLevel(logLevel)
{
}

void cLogger::log(LogLevel logLevel, const char* message) const
{
    auto levelToString = [](LogLevel logLevel)
    {
        switch (logLevel)
        {
        case LogLevel::Error: return "Error";
        case LogLevel::Warning: return "Warning";
        case LogLevel::Info: return "Info";
            default: return "Unknown";
        }  
    };
    if (logLevel > m_logLevel)
        return;
    std::clog << levelToString(logLevel) << ": " << message << "\n";
}
