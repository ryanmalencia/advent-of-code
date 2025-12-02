#include <fstream>
#include <iostream>
#include <string>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::ifstream file("input.txt");
    std::string line;
    int current = 0, max = 0;
    while(std::getline(file, line))
    {
        if(line.length() == 0)
        {
            if(current > max)
                max = current;
            current = 0;
        }
        else
            current += std::stoi(line);
    }
    std::cout << max << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}