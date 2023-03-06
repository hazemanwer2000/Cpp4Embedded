
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

namespace Utils {
    std::string getDateTime() {
        std::stringstream s;

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        s << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
        
        return s.str();
    }
}
