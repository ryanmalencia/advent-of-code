#pragma once

#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;

// Macros must be used in this order
#define START_TIMER(timer_name) auto timer_name = Clock::now();
#define END_TIMER(timer_name) auto timer_name ## _end = Clock::now();
#define PRINT_TIMER_NS(timer_name) std::cout << "Time for " #timer_name ": "  << std::chrono::duration_cast<std::chrono::nanoseconds>(timer_name ## _end - timer_name).count() << "ns" << std::endl;
#define PRINT_TIMER_US(timer_name) std::cout << "Time for " #timer_name ": "  << std::chrono::duration_cast<std::chrono::microseconds>(timer_name ## _end - timer_name).count() << "us" << std::endl;
#define PRINT_TIMER_MS(timer_name) std::cout << "Time for " #timer_name ": "  << std::chrono::duration_cast<std::chrono::milliseconds>(timer_name ## _end - timer_name).count() << "ms" << std::endl;
#define PRINT_TIMER_S(timer_name) std::cout << "Time for " #timer_name ": "  << std::chrono::duration_cast<std::chrono::seconds>(timer_name ## _end - timer_name).count() << "s" << std::endl;
#define PRINT_TIMER_M(timer_name) std::cout << "Time for " #timer_name ": "  << std::chrono::duration_cast<std::chrono::minutes>(timer_name ## _end - timer_name).count() << "mins" << std::endl;