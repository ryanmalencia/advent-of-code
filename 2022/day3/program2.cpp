#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int GetPriority(char c)
{
    if(c >= 97)
            return c - 96;
    else
        return c - 38;
}

std::string CommonCharacters(const std::string& first, const std::string& second)
{
    std::string common;
    for(const auto item : first)
    {
        if(second.find(item) == std::string::npos)
            continue;
        else if(common.find(item) == std::string::npos)
            common += item;
    }
    return common;
}

int main()
{
    START_TIMER(main_timer);
    std::string line;
    std::string filename("input.txt");
    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

    int priority = 0;
    while (std::getline(input_file, line)) {
        if(line.length() == 0) break;

        std::string line2, line3;
        std::getline(input_file, line2);
        std::getline(input_file, line3);

        std::string common = CommonCharacters(line, line2);
        common = CommonCharacters(common, line3);

        if(common.length() != 1)
        {
            std::cout << line << " " << line2 << " " << line3 << " " << common << std::endl;
            std::cerr << "Logic error: Common character length does not equal 1" << std::endl;
            return EXIT_FAILURE;
        }
        priority += GetPriority(common[0]);
    }
    std::cout << priority << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}