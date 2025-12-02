#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

int getScenic(int** grid, int row, int col, int totalrow, int totalcol)
{
    int height = grid[row][col];
    int left = col - 1, right = col + 1, top = row - 1, bottom = row + 1;
    for(; top >= 0;)
    {
        if(grid[top][col] >= height)
        {
            --top;
            break;
        }
        --top;
    }
    for(; bottom < totalrow;)
    {
        if(grid[bottom][col] >= height) 
        {
            ++bottom;
            break;
        }
        ++bottom;
    }
    for(; left >= 0;)
    {
        if(grid[row][left] >= height)
        {
            --left;
            break;
        }
        --left;
    }
    for(; right < totalcol;)
    {
        if(grid[row][right] >= height) 
        {
            ++right;
            break;
        }
        ++right;
    }
    return (col - (left + 1)) * (right - col - 1) * (row - (top + 1)) * ((bottom - 1) - row);
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

    int row = 99, col = 99;
    int** grid = new int*[row];
    for(int r = 0; r < row; ++r)
        grid[r] = new int[col];
    
    int visible = row + 2*(col-1) + (row-2);
    int current_row = 0;
    while(std::getline(input_file, line))
    {
        for(int c = 0; c < col; ++c)
            grid[current_row][c] = line[c] - 48;
        ++current_row;
    }

    int maxScenic = -1;
    for(int r = 1; r < (row - 1); ++r)
    {
        for(int c = 1; c < (col - 1); ++c)
        {
            int scenic = getScenic(grid, r, c, row, col);
            if(scenic > maxScenic)
                maxScenic = scenic;
        }
    }

    std::cout << maxScenic << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}
