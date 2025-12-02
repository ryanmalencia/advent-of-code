#include <fstream>
#include <iostream>
#include <string>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::ifstream file("input.txt");
    std::string line;
    int count = 0, counter = 0;
    int data[4] {0,0,0,0};
    int idx = 0;
    while(std::getline(file, line))
    {
        data[idx] = std::stoi(line);
        ++counter;
        if(counter < 4)
            continue;

        int current = data[(idx + 1) % 4] + data[(idx + 2) % 4] + data[(idx + 3) % 4];
        int next = data[(idx + 2) % 4] + data[(idx + 3) % 4] + data[(idx + 4) % 4];
        if(next > current)
            ++count;
        current = next;
        idx = (idx + 1) % 4;
    }
    std::cout << count << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}