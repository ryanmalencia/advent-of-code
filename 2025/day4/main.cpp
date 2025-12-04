#include <array>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../include/ctoi.h"
#include "../../include/logging.h"
#include "../../include/string_utils.h"
#include "../../include/timing.h"

size_t PartOne()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }

    START_TIMER(PartOne);

    std::vector<std::vector<bool>> grid;
    std::string line;
    size_t roll_count = 0;
    size_t line_count = 0;
    while (std::getline(ifs, line))
    {
        std::vector<bool> layer;
        layer.reserve(line.size());
        for (char c : line)
        {
            layer.push_back(c == '@');
        }
        grid.emplace_back(layer);
        ++line_count;
    }   

    size_t row_num = 0;
    for(const auto& row : grid)
    {
        for (size_t col_num = 0; col_num < row.size(); ++col_num)
        {
            const auto& cell = row[col_num];
            if(!cell) continue;

            size_t adjancent_count = 0;
            const int x_start = col_num == 0 ? 0 : -1;
            const int y_start = row_num == 0 ? 0 : -1;
            const int x_max = col_num == (row.size() - 1) ? 0 : 1;
            const int y_max = row_num == (line_count - 1) ? 0 : 1;
            
            bool bValid = true;
            for(int x = x_start; x <= x_max; ++x)
            {
                for(int y = y_start; y <= y_max; ++y)
                {
                    if(x == 0 && y == 0) continue;
                    if(grid[row_num + y][col_num + x])
                    {
                        ++adjancent_count;
                        if(adjancent_count > 3)
                        {
                            bValid = false;
                            break;
                        }
                    }
                }
                if(!bValid) break;
            }
            
            if(bValid)
            {
                ++roll_count;
            }
        }
        ++row_num;
    }

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return roll_count;
}

size_t PartTwo()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }

    START_TIMER(PartTwo);

    std::vector<bool*> grid;
    std::string line;
    size_t roll_count = 0;
    size_t line_count = 0;
    size_t line_size = 0;

    while (std::getline(ifs, line))
    {
        if(line_size == 0)
        {
            line_size = line.size();
        }

        bool* layer = new bool[line_size];
        for (size_t i = 0; i < line_size; ++i)
        {
            layer[i] = (line[i] == '@');
        }
        grid.emplace_back(layer);
        ++line_count;
    }   

    
    size_t num_removed = 0;
    do
    {
        size_t row_num = 0;
        num_removed = 0;
        for(const auto row : grid)
        {
            for (size_t col_num = 0; col_num < line_size; ++col_num)
            {
                if(!row[col_num]) continue;

                size_t adjancent_count = 0;
                const int x_start = col_num == 0 ? 0 : -1;
                const int y_start = row_num == 0 ? 0 : -1;
                const int x_max = col_num == (line_size - 1) ? 0 : 1;
                const int y_max = row_num == (line_count - 1) ? 0 : 1;
                
                bool bValid = true;
                for(int x = x_start; x <= x_max; ++x)
                {
                    for(int y = y_start; y <= y_max; ++y)
                    {
                        if(x == 0 && y == 0) continue;

                        if(grid[row_num + y][col_num + x])
                        {
                            ++adjancent_count;
                            if(adjancent_count > 3)
                            {
                                bValid = false;
                                break;
                            }
                        }
                    }
                    if(!bValid) break;
                }
                
                if(bValid)
                {
                    ++roll_count;
                    grid[row_num][col_num] = false;
                    ++num_removed;
                }
            }
            
            ++row_num;
        }
    } while (num_removed > 0);

    for(auto row : grid)
    {
        delete[] row;
    }
    grid.clear();
    
    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return roll_count;
}

int main()
{
    auto partOne = PartOne();
    auto partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
