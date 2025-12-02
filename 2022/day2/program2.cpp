#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int GetPoints(char opponent, char mine)
{
    int result = 0;
    switch(mine)
    {
    case 'Y':
    {
        result += 3;
        switch (opponent)
        {
        case 'A':
            result += 1;
            break;
        case 'B':
            result += 2;
            break;
        case 'C':
            result += 3;
            break;
        }
        break;
    }
    case 'X':
    {
        switch (opponent)
        {
        case 'A':
            result += 3;
            break;
        case 'B':
            result += 1;
            break;
        case 'C':
            result += 2;
            break;
        }
        break;
    }
    case 'Z':
    {
        result += 6;
        switch (opponent)
        {
        case 'A':
            result += 2;
            break;
        case 'B':
            result += 3;
            break;
        case 'C':
            result += 1;
            break;
        }
        break;
    }
    }
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