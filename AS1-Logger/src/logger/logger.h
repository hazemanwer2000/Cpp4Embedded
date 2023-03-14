
#include <iostream>
#include <vector>

#include "std_types.h"

namespace Logger {
    enum class LogLevel : uint8_t {
        Disabled = 0,
        Error,
        Warning,
        Info,
        Debug
    };

    enum class LogMode : uint8_t {
        File,
        Console
    };

    struct Application {
        std::string appID;
        LogLevel logLevel;
        LogMode logMode;
    
        Application(std::string appID, LogLevel logLevel=LogLevel::Debug, LogMode logMode=LogMode::Console) :
            appID(appID), logLevel(logLevel), logMode(logMode) {}
    };

    void log(const Application &app, LogLevel logLevel, std::string msg);

    void setOutputFile(std::string str);
}