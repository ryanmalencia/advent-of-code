#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

    size_t treesEncountered = 0;
    size_t position = 0;
    std::string strLine;
    size_t linelen = 0;
    while(std::getline(ifs, strLine))
    {
        if(linelen == 0)
        {
            position += 3;
            linelen = strLine.length();
            continue;
        }

        const char* str = strLine.c_str();
        const char sym = str[position];
        if(sym == '#')
        {
            ++treesEncountered;   
        }

        position += 3;
        if(position >= linelen)
        {
            position = (position % linelen);
        }
    }

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return treesEncountered;
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

    std::vector<std::string> trees;
    std::string strLine;
    while(std::getline(ifs, strLine))
    {
        trees.push_back(strLine);
    }

    const size_t slopes[5] = {1, 3, 5, 7, 1};
    const size_t grades[5] = {1, 1, 1, 1, 2};

    size_t multipliedTrees = 1;
    const size_t linelen = trees[0].length();

    for(size_t idx = 0; idx < 5; ++idx)    
    {
        size_t position = slopes[idx];
        const size_t slope = position;
        const size_t grade = grades[idx];

        size_t treesEncountered = 0;
        size_t counter = 0;
        for(const auto& line : trees)
        {
            if(counter < grade)
            {
                ++counter;
                continue;
            }
            counter = 1;
            const char* str = line.c_str();
            const char sym = str[position];
            if(sym == '#')
            {
                ++treesEncountered;   
            }
            position += slope;
            if(position >= linelen)
            {
                position = (position % linelen);
            }
        }
        multipliedTrees *= treesEncountered;
    }

    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return multipliedTrees;
}

int main()
{
    size_t partOne = PartOne();
    size_t partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
