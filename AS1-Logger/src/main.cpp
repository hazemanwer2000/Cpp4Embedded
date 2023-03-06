
#include <iostream>
#include <fstream>

#include "logger.h"
#include "utils.h"
#include "std_types.h"

Logger::Application app1("App1", Logger::LogLevel::Error, Logger::LogMode::File);
Logger::Application app2("App2", Logger::LogLevel::Debug, Logger::LogMode::File);

void LoggingLikeJogging(Logger::Application &app) {
    Logger::log(app, Logger::LogLevel::Error, "This is an error message!");
    Logger::log(app, Logger::LogLevel::Warning, "This is a warning message!");
    Logger::log(app, Logger::LogLevel::Info, "This is an informative message!");
    Logger::log(app, Logger::LogLevel::Debug, "This is a debug-mode message!");
}

int main() {
    Logger::setOutputFile("log.txt");

    LoggingLikeJogging(app1);
    LoggingLikeJogging(app2);

    app1.logMode = Logger::LogMode::Console;
    app2.logMode = Logger::LogMode::Console;

    LoggingLikeJogging(app1);
    LoggingLikeJogging(app2);
}