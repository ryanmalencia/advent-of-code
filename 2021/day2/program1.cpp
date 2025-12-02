#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::ifstream in("input.txt");
    std::string line;
    int iHorizontalPos = 0, iDepth = 0;

    const char* forward = "forward";
    const char* down = "down";
    const char* up = "up";
    while(std::getline(in, line))
    {
        char *direction = strtok (&line[0] , " ");
        char *distance = strtok(NULL, " ");

        if(strcmp(direction, forward) == 0)
            iHorizontalPos += std::atoi(distance);
        else if(strcmp(direction, down) == 0)
            iDepth += std::atoi(distance);
        else if(strcmp(direction, up) == 0)
            iDepth -= std::atoi(distance);
    }
    std::cout << iHorizontalPos * iDepth << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}