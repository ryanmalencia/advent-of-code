#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int GetPriority(const std::string& first, const std::string& second)
{
    for(const auto item : first)
    {
        if(second.find(item) == std::string::npos)
            continue;
        if(item >= 97)
            return item - 96;
        else
            return item - 38;
    }
    return 0;
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
        int length = line.length();
        std::string first(line.begin(), line.begin() + length / 2);
        std::string second(line.begin() + (length / 2), line.end());
        priority += GetPriority(first, second);
    }
    std::cout << priority << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}