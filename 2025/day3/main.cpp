#include <array>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../../include/ctoi.h"
#include "../../include/logging.h"
#include "../../include/string_utils.h"
#include "../../include/timing.h"

size_t PartOne()
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
    if(!std::getline(ifs, strLine))
    {
        std::cout << "Input file is empty" << std::endl;
        return 0;
    }

    const size_t lineLength = strLine.length();
    size_t total_joltage = 0;
    do
    {
        int second = 0;
        int first = 0;
        const char* str = strLine.c_str();
        for(size_t i = 0; i < lineLength; ++i)
        {
            int val = ctoi(str[i]);
            if(val > first && i == (lineLength - 1))
            {
                second = val;
            }
            else if(val > first)
            {
                first = val;
                second = 0;
            }
            else if(val > second)
            {
                second = val;
            }
        }

        size_t joltage = first * 10 + second;
        total_joltage += joltage;

    } while (std::getline(ifs, strLine));

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return total_joltage;
}

long long PartTwo()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }

    START_TIMER(PartTwo);
    
    std::string strLine;
    if(!std::getline(ifs, strLine))
    {
        std::cout << "Input file is empty" << std::endl;
        return 0;
    }

    const size_t lineLength = strLine.length();
    long long total_joltage = 0;
    
    do
    {
        const char* str = strLine.c_str();
        const size_t count = 12;
        std::array<int, count> values = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for(size_t i = 0; i < lineLength; ++i)
        {
            int val = ctoi(str[i]);
            size_t j = i < (lineLength - count) ? 0 : count - (lineLength - i);
            for(; j < count; ++j)
            {
                if(val > values[j])
                {
                    values[j] = val;
                    memset(values.data() + j + 1, 0, (values.size() - j - 1) * sizeof(int));
                    break;
                }
            }

            if(i >= (lineLength - count))
            {
                values[count - (lineLength - i)] = std::max(values[count - (lineLength - i)], val);
            }
        }

        long long joltage = 0;
        for(int i = 0; i < count; ++i)
        {
            joltage *= 10;
            joltage += values[i];
        }
        total_joltage += joltage;

    } while (std::getline(ifs, strLine));

    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return total_joltage;
}

int main()
{
    auto partOne = PartOne();
    auto partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
