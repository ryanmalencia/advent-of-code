#include <algorithm>
#include <array>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    size_t fresh_ingredients = 0;

    std::string line;
    std::vector<std::pair<size_t, size_t>> fresh_ranges;
    bool filling_fresh_ranges = true;
    while (std::getline(ifs, line))
    {
        if(line.length() == 0)
        {
            filling_fresh_ranges = false;
            continue;
        }

        if(filling_fresh_ranges)
        {
            const auto range = string_utils::split_string(line, "-");
            if(range.size() != 2)
            {
                std::cout << "Invalid range: " << line << std::endl;
                continue;
            }

            size_t start = std::stoull(range[0]);
            size_t end = std::stoull(range[1]);
            fresh_ranges.push_back({start, end});
        }
        else
        {
            size_t ingredient = std::stoull(line);
            for(const auto& range: fresh_ranges)
            {
                if(ingredient >= range.first && ingredient <= range.second)
                {
                    fresh_ingredients++;
                    break;
                }
            }
        }
    }   

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return fresh_ingredients;
}

size_t PartTwo()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }

    START_TIMER(PartTwo);
    
    std::string line;
    std::vector<std::pair<size_t, size_t>> fresh_ranges;
    while (std::getline(ifs, line))
    {
        if(line.length() == 0)
        {
            break;
        }

        const auto range = string_utils::split_string(line, "-");
        size_t start = std::stoull(range[0]);
        size_t end = std::stoull(range[1]);

        fresh_ranges.push_back({start, end});

    }

    std::sort(fresh_ranges.begin(), fresh_ranges.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    size_t curr_idx = 0;
    std::pair<size_t, size_t> current_range = fresh_ranges[curr_idx];
    for(size_t i = 0; i < fresh_ranges.size() - 1; ++i)
    {
        std::pair<size_t, size_t>& next_range = fresh_ranges[i + 1];
        if(current_range.second >= (next_range.first-1))
        {
            fresh_ranges[curr_idx].second = std::max(current_range.second, next_range.second);
            next_range.first = 0;
            next_range.second = 0;
            current_range = fresh_ranges[curr_idx];
        }
        else
        {
            curr_idx = i + 1;
            current_range = fresh_ranges[curr_idx];
        }
    }

    size_t fresh_ingredients = 0;
    for(const auto& range: fresh_ranges)
    {
        if(range.first == 0 && range.second == 0)
        {
            continue;
        }
        
        size_t count = (range.second - range.first + 1);
        fresh_ingredients += count;
    }

    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return fresh_ingredients;
}

int main()
{
    auto partOne = PartOne();
    auto partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
