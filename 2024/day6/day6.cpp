#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <regex>

typedef std::chrono::high_resolution_clock Clock;

void RotateDirection(int vX, int vY, int& vXnew, int& vYnew)
{
    if(vX == 1 || vX == -1) vXnew = 0;
    else if(vX == 0 && vY == -1) vXnew = 1;
    else vXnew = -1;

    if(vY == 1 || vY == -1) vYnew = 0;
    else if(vY == 0 && vX == 1) vYnew = 1;
    else vYnew = -1;
}

bool bInfinite(const std::vector<std::string>& vecObstruct, int currentX, int currentY, int vX, int vY, int maxVal, int& count)
{
    std::set<std::pair<int, int>> visited;
    visited.insert({currentX, currentY});
    bool bInfiniteLoop = true;
    int loopStartX = 0;
    int loopStartY = 0;
    bool bStartLoop = false;
    while(true)
    {
        currentX += vY;
        currentY += vX;
        if(currentX < 0 || currentX >= maxVal)
            break;
        if(currentY < 0 || currentY >= maxVal)
            break;

        if(vecObstruct[currentX][currentY] == '.')
        {
            if(visited.insert({currentX, currentY}).second == false)
            {
                bStartLoop = true;
            }
            if(loopStartX == currentX && loopStartY == currentY)
            {
                return true;
            }

            if(bStartLoop)
            {
                loopStartX = currentX;
                loopStartY = currentY;
            }
            ++count;
            continue;
        }

        currentX -= vY;
        currentY -= vX;

        int newVx = 0, newVy = 0;
        RotateDirection(vX, vY, newVx, newVy);
        vX = newVx;
        vY = newVy;
    }
    return bInfiniteLoop;
}

int PartOne()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 1;
    }

    auto timer = Clock::now();

    std::vector<std::string> vecObstruct;

    std::string strLine;
    int startRow = 0;
    int startCol = 0;
    int row = 0;
    bool bFoundStart = false;
    while (std::getline(ifs, strLine))
    {
        vecObstruct.push_back(strLine);
        if(!bFoundStart)
        {
            size_t pos = strLine.find('^');
            if(pos != std::string::npos)
            {
                bFoundStart = true;
                startRow = row;
                startCol = pos;
                vecObstruct[row][pos] = 'X';
            }
        }
        ++row;
    }

    int vY = -1;
    int vX = 0;

    int count = 1;
    int currentX = startRow;
    int currentY = startCol;
    while(true)
    {
        currentX += vY;
        currentY += vX;
        if(currentX < 0 || currentX >= row)
            break;
        if(currentY < 0 || currentY >= row)
            break;

        if(vecObstruct[currentX][currentY] == '.')
        {
            ++count; 
            vecObstruct[currentX][currentY] = 'X';
            continue;
        }
        else if(vecObstruct[currentX][currentY] == 'X')
        {
            continue;
        }

        currentX -= vY;
        currentY -= vX;

        int newVx = 0, newVy = 0;
        RotateDirection(vX, vY, newVx, newVy);
        vX = newVx;
        vY = newVy;
    }
    
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 1: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return count;
}

int PartTwo()
{
    std::ifstream ifs;
    ifs.open("input.txt");

    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 1;
    }

    auto timer = Clock::now();

    std::vector<std::string> vecObstruct;

    std::string strLine;
    int startRow = 0;
    int startCol = 0;
    int row = 0;
    bool bFoundStart = false;
    std::set<int> rowObstacles, colObstacles;
    while (std::getline(ifs, strLine))
    {
        vecObstruct.push_back(strLine);
        if(!bFoundStart)
        {
            size_t pos = strLine.find('^');
            if(pos != std::string::npos)
            {
                bFoundStart = true;
                startRow = row;
                startCol = pos;
                vecObstruct[row][pos] = 'X';
            }
        }

        bool bFirst = true;
        size_t pos = strLine.find('#');
        while(pos != std::string::npos)
        {
            std::cout << pos << std::endl;
            if(bFirst)
            {
                rowObstacles.insert(row);
                bFirst = false;
            }
            colObstacles.insert(pos);
            pos = strLine.find('#', pos + 1);
        }
        ++row;
    }

    int count = 1;
    /*int vY = -1;
    int vX = 0;

    
    int currentX = startRow;
    int currentY = startCol;
    while(true)
    {
        currentX += vY;
        currentY += vX;
        if(currentX < 0 || currentX >= row)
            break;
        if(currentY < 0 || currentY >= row)
            break;

        if(vecObstruct[currentX][currentY] == '.')
        {
            ++count; 
            vecObstruct[currentX][currentY] = 'X';
            continue;
        }
        else if(vecObstruct[currentX][currentY] == 'X')
        {
            continue;
        }

        currentX -= vY;
        currentY -= vX;

        int newVx = 0, newVy = 0;
        RotateDirection(vX, vY, newVx, newVy);
        vX = newVx;
        vY = newVy;
    }*/
    
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 1: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return count;
}

int main()
{
    //std::cout << "Part 1: " << PartOne() << std::endl;
    std::cout << "Part 2: " << PartTwo() << std::endl;
    return 0;
}
