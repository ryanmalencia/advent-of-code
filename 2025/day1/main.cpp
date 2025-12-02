#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>

#include "../../include/timing.h"

int PartOne()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }

    START_TIMER(PartOne);
    std::string strLine;
    int current_pos = 50;
    int zero_counter = 0;
    while (std::getline(ifs, strLine))
    {
        const char* line = strLine.c_str();
        char dir = line[0];
        int distance = atoi(line + 1);

        if(dir == 'L')
        {
            current_pos -= distance;
        }
        else
        {
            current_pos += distance;
        }

        if(current_pos % 100 == 0)
        {
            zero_counter += 1;
        }
    }

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return zero_counter;
}

int PartTwo()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }

    START_TIMER(PartTwo);
    
    int current_pos = 50;
    int last_pos = 50;
    int zero_counter = 0;
    std::string strLine;
    while (std::getline(ifs, strLine))
    {
        last_pos = current_pos;
        const char* line = strLine.c_str();
        char dir = line[0];
        int distance = atoi(line + 1);

        int full_turns = distance / 100;
        int partial_turns = distance % 100;
        
        int zeros = 0;
        zeros += full_turns;

        if(dir == 'L')
        {
            current_pos -= partial_turns;
        }
        else
        {
            current_pos += partial_turns;
        }

        if(current_pos < 0)
        {
            if(last_pos != 0) ++zeros;
            current_pos = current_pos + 100;
        }
        else if(current_pos > 99)
        {
            ++zeros;
            current_pos = current_pos - 100;
        }
        else if(current_pos == 0 && last_pos != 0)
        {
            ++zeros;
        }

        zero_counter += zeros;
    }

    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return zero_counter;
}

int main()
{
    int partOne = PartOne();
    int partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
