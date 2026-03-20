#include "Logger.h"

#include <iostream>

namespace simple_engine {

void Logger::info(const char* message) {
    std::cout << "[Info] " << message << std::endl;
}

void Logger::error(const char* message) {
    std::cerr << "[Error] " << message << std::endl;
}

} // namespace simple_engine
