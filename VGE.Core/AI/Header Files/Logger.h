#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    virtual ~Logger() = default;

    virtual void Log(const std::string& message) = 0;
    virtual void LogError(const std::string& message) = 0;
    // ... (Add other logging levels or methods as needed)
};

#endif // LOGGER_H