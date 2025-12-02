#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int GetPoints(char opponent, char mine)
{
    int result = 0;
    if(mine == 'X')
        result += 1;
    else if(mine == 'Y')
        result += 2;
    else
        result += 3;

    if(mine == (opponent + 23))
        result += 3;
    if((mine == 'X' && opponent == 'C') ||
       (mine == 'Y' && opponent == 'A') ||
       (mine == 'Z' && opponent == 'B'))
       result += 6;
    
    return result;
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

    int count = 0;
    while (std::getline(input_file, line)) {
        count += GetPoints(line[0], line[2]);
    }
    std::cout << count << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}