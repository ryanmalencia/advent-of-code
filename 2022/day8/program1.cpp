#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../../include/timing.h"

bool isVisible(int** grid, int row, int col, int totalrow, int totalcol)
{
    int height = grid[row][col];
    bool bContinue = false;
    if((totalrow - row) > row)
    {
        for(int r = 0; r < row; ++r)
            if(grid[r][col] >= height) bContinue = true;
        if(!bContinue) return true;
        bContinue = false;
        for(int r = row + 1; r < totalrow; ++r)
            if(grid[r][col] >= height) bContinue = true;
        if(!bContinue) return true;
    }
    else
    {
        for(int r = row + 1; r < totalrow; ++r)
            if(grid[r][col] >= height) bContinue = true;
        if(!bContinue) return true;
        bContinue = false;
        for(int r = 0; r < row; ++r)
            if(grid[r][col] >= height) bContinue = true;
        if(!bContinue) return true;
    }
    bContinue = false;
    if((totalcol - col) > col)
    {
        for(int c = 0; c < col; ++c)
            if(grid[row][c] >= height) bContinue = true;
        if(!bContinue) return true;
        bContinue = false;
        for(int c = col + 1; c < totalcol; ++c)
            if(grid[row][c] >= height) return false;
    }
    else
    {
        for(int c = col + 1; c < totalcol; ++c)
            if(grid[row][c] >= height) return false;
        if(!bContinue) return true;
        bContinue = false;
        for(int c = 0; c < col; ++c)
            if(grid[row][c] >= height) bContinue = true;
        if(!bContinue) return true;
    }
    return true;
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

    for(int r = 1; r < (row - 1); ++r)
    {
        for(int c = 1; c < (col - 1); ++c)
        {
            if(isVisible(grid, r, c, row, col))
                ++visible;
        }
    }

    std::cout << visible << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    input_file.close();
    return EXIT_SUCCESS;
}
