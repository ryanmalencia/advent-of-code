#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::ifstream file("input.txt");
    std::string line;
    int current = 0, max = 0;
    std::vector<int> all;
    while(std::getline(file, line))
    {
        if(line.length() == 0)
        {
            if(current > max)
                max = current;
            all.push_back(current);
            current = 0;
        }
        else
            current += std::stoi(line);
    }
    std::sort(all.begin(), all.end(), std::greater<int>());
    int total = all[0] + all[1] + all[2];
    std::cout << total << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}