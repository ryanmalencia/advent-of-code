#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int FullyContained(int* first, int* second)
{
    if(first[0] >= second[0] &&
       first[1] <= second[1])
       return 1;
    else if(second[0] >= first[0] &&
       second[1] <= first[1])
       return 1;
    return 0;
}

int Overlap(int* first, int* second)
{
    if(first[0] >= second[0])
    {
        if(second[1] >= first[0])
            return 1;
    }
    else if(first[1] <= second[1])
    {
        if(first[1] >= second[0])
           return 1;
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

    int fullyContained = 0;
    int first[2] = {0,0};
    int second[2] = {0,0};
    while (std::getline(input_file, line)) {
        
        std::string first_str = line.substr(0, line.find(','));
        line.erase(0, line.find(',') + 1);
        std::string second_str = line;

        first[0] = atoi(first_str.substr(0, first_str.find('-')).c_str());
        first_str.erase(0, first_str.find('-') + 1);
        first[1] = atoi(first_str.c_str());

        second[0] = atoi(second_str.substr(0, second_str.find('-')).c_str());
        second_str.erase(0, second_str.find('-') + 1);
        second[1] = atoi(second_str.c_str());
        int contained = FullyContained(first, second);
        if(contained == 0)
        {
            fullyContained += Overlap(first, second);
        }
        else
            fullyContained += contained;
    }
    std::cout << fullyContained << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}