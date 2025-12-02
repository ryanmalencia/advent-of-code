#include <fstream>
#include <iostream>
#include <string>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::ifstream file("input.txt");
    std::string line;
    int total = 0;
    char str[3];
    str[2] = '\0';
    bool bFirst = true;
    while(std::getline(file, line))
    {
        bFirst = true;
        for(const auto& c : line)
        {
            if(c > 47 && c < 58)
            {
                if(bFirst)
                {
                    str[0] = c;
                    str[1] = c;
                    bFirst = false;
                }
                else
                {
                    str[1] = c;
                }
            }
        }
        total += std::atoi(str);
    }
    std::cout << total << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}