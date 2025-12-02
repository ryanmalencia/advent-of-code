#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "../../include/timing.h"

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

    int columncount = 9;
    std::vector<std::vector<char>> columns(columncount);
    for(int linecount = 0; linecount < 8; ++linecount)
    {
        int idx = 1;
        std::getline(input_file, line);
        for(int column = 0; column < columncount; ++column)
        {
            if(line[idx] == ' ') 
            {
                idx += 4;
                continue;
            }
            columns[column].insert(columns[column].begin(), line[idx]);
            idx += 4;
        }
    }
    
    std::getline(input_file, line);
    std::getline(input_file, line);
    while(std::getline(input_file, line))
    {
        std::string operation = line.substr(0, line.find(' '));
        line.erase(0, line.find(' ') + 1);
        int count = atoi(line.substr(0, line.find(' ')).c_str());
        line.erase(0, line.find(' ') + 1);
        std::string from = line.substr(0, line.find(' '));
        line.erase(0, line.find(' ') + 1);
        int source = atoi(line.substr(0, line.find(',')).c_str());
        line.erase(0, line.find(' ') + 1);
        std::string to = line.substr(0, line.find(' '));
        line.erase(0, line.find(' ') + 1);
        int destination = atoi(line.substr(0, line.find(',')).c_str());

        auto& sourceVec = columns[source - 1];
        auto& destinationVec = columns[destination - 1];

        destinationVec.insert(destinationVec.end(), sourceVec.end() - count, sourceVec.end());
        sourceVec.erase(sourceVec.end() - count, sourceVec.end());   
    }
    
    for(int column = 0; column < columncount; ++column)
    {
        std::cout << columns[column].back();
    }
    std::cout << std::endl;

    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}