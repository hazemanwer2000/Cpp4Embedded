
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include "logger.h"
#include "utils.h"

namespace Logger {
    static std::unique_ptr<std::ofstream> logFile(nullptr);

    static std::string LogLevelMapping[] = {
        "Disabled",
        "Error",
        "Warning",
        "Info",
        "Debug"
    };

    void setOutputFile(std::string str) {
        if (logFile) {
            logFile->close();
        }

        logFile.reset(new std::ofstream(str, std::ios::out | std::ios::app));
    }

    void log(const Application &app, LogLevel logLevel, std::string msg) {
        std::stringstream ss;
        auto append = [&ss] (std::string msg) {
            ss << " | " << msg;
        };

        if (logLevel <= app.logLevel) {
            append(Utils::getDateTime());
            append(app.appID);
            append(LogLevelMapping[static_cast<uint8_t>(logLevel)]);
            append(msg);
            ss << " | \n";

            switch (app.logMode) {
            case LogMode::Console:
                std::cout << ss.str();
                break;
            case LogMode::File:
                *logFile << ss.str();
                break;
            }
        }
    }
};