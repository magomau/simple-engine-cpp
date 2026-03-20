#pragma once

namespace simple_engine {

class Logger {
public:
    static void info(const char* message);
    static void error(const char* message);
};

} // namespace simple_engine
