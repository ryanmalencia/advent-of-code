#include <fstream>
#include <iostream>
#include <string>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::ifstream file("input.txt");
    std::string line;
    int current = 0, next = 0, count = 0;
    bool bFirst = true;
    while(std::getline(file, line))
    {
        next = std::stoi(line);
        if(bFirst)
        {
            bFirst = false;
            current = next;
            continue;
        }
        if(next > current)
            ++count;
        current = next;
    }
    std::cout << count << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}