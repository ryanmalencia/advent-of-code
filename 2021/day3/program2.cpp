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
    
    int total = 0, length = 0;
    int* piVals;
    while(std::getline(in, line))
    {
        if (total == 0)
        {
            piVals = new int[line.length()];
            length = line.length();
            memset(piVals, 0, length*sizeof(piVals));
        }
        for (size_t idx = 0; idx < line.length(); ++idx)
        {
            int val = line[idx];
            if (line[idx] == 49)
                piVals[idx]++;
        }
        total++;
    }

    int threshold = total / 2;
    unsigned int gamma = 0, epsilon = 0;
    for (int idx = 0; idx < length; ++idx)
    {
        gamma <<= 1;
        epsilon <<= 1;
        if (piVals[idx] > threshold)
            gamma |= 1;
        else
            epsilon |= 1;
    }

    std::cout << gamma * epsilon << std::endl;
    delete[] piVals;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}