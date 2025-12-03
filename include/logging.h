#pragma once

#ifdef LOGGING
#include <iostream>
namespace logging {
    inline bool can_log() { return true; };
    inline void log_message(const char* msg) { std::cout << msg << std::endl; };
}
#else
namespace logging {
    inline bool can_log() { return false; };
    inline void log_message(const char*) { };
}
#endif