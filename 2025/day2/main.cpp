#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../../include/logging.h"
#include "../../include/string_utils.h"
#include "../../include/timing.h"

long long PartOne()
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
        std::cout << "Failed to get line" << std::endl;
        return 0;
    }

    const auto id_ranges = string_utils::split_string(strLine, ",");
    long long addedInvalidIds = 0;
    for(const auto& id_range : id_ranges)
    {
        const auto min_max_vec = string_utils::split_string(id_range, "-");
        const auto str_min = min_max_vec[0];

        const auto str_max = min_max_vec[1];

        const long long min = std::stoll(str_min.c_str());
        const long long max = std::stoll(str_max.c_str());
        if(logging::can_log())
        {
            std::stringstream ss;
            ss << "Min: " << min << " Max: " << max;
            logging::log_message(ss.str().c_str());
        }

        if(str_min.length() == str_max.length() && str_min.length() % 2 == 1)
        {
            logging::log_message("Skipped");
            continue;
        }

        for(long long i = min; i <= max; ++i)
        {
            const std::string str = std::to_string(i);
            const auto len = str.length();
            if(len % 2 == 1) continue;
            const auto halflen = len / 2;

            const auto cstr = str.c_str();
            
            if(!strncmp(cstr, (cstr + halflen), halflen ))
            {
                addedInvalidIds += i;
                if(logging::can_log())
                {
                    std::stringstream ss;
                    ss << i << std::endl << addedInvalidIds;
                    logging::log_message(ss.str().c_str());
                }
            }
        }
    }

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return addedInvalidIds;
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
        std::cout << "Failed to get line" << std::endl;
        return 0;
    }

    long long addedInvalidIds = 0;
    const auto id_ranges = string_utils::split_string(strLine, ",");
    for(const auto& id_range : id_ranges)
    {
        const auto min_max_vec = string_utils::split_string(id_range, "-");
        const auto str_min = min_max_vec[0];
        const auto str_max = min_max_vec[1];
        const long long min = std::stoll(str_min.c_str());
        const long long max = std::stoll(str_max.c_str());
        if(logging::can_log())
        {
            std::stringstream ss;
            ss << "Min: " << min << " Max: " << max;
            logging::log_message(ss.str().c_str());
        }

        for(long long i = min; i <= max; ++i)
        {
            const std::string str = std::to_string(i);
            const size_t len = str.length();
            const size_t halflen = len / 2;
            const auto cstr = str.c_str();
            for(size_t test = halflen; test > 0; --test)
            {
                if(len % test == 1) continue;
                
                int start = 0;
                bool bInvalid = true;
                while((start + test) < len)
                {
                    if(strncmp(cstr + start, (cstr + start + test), test))
                    {
                        bInvalid = false;
                        break;
                    }
                    start += test;
                }
                if(bInvalid)
                {
                    addedInvalidIds += i;
                    if(logging::can_log())
                    {
                        std::stringstream ss;
                        ss << i << std::endl << addedInvalidIds;
                        logging::log_message(ss.str().c_str());
                    }
                    break;
                }
            }
        }
    }

    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return addedInvalidIds;
}

int main()
{
    long long partOne = PartOne();
    long long partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
