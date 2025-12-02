#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

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

    int safe = 0;
    std::string strLine;
    while (std::getline(ifs, strLine))
    {
        char *dup = strdup(strLine.c_str());
        
        int num = 0;
        int count = 0;
        int prev = 0;
        bool bIncreasing = false;
        bool bSafe = true;
        char* cNum = strtok(dup, " ");
        do
        {
            num = atoi(cNum);
            if (count == 0)
            {
                prev = num;
                ++count;
                continue;
            }

            if (prev == num || abs(prev - num) > 3)
            {
                bSafe = false;
                break;
            }

            if (count == 1 && prev < num)
            {
                bIncreasing = true;

            }
            if (bIncreasing && num < prev)
            {

                bSafe = false;
                break;

            }
            else if (!bIncreasing && num > prev)
            {

                bSafe = false;
                break;
                
            }
            prev = num;
            ++count;
        }while((cNum = strtok(nullptr, " ")) != nullptr);
        if (bSafe)
        {
            safe++;
        }
        free(dup);
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 1: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return safe;
}

bool SafeAfterClean(int* data, size_t len, size_t idxToSkip)
{
    int num = 0;
    int count = 0;
    int prev = 0;
    bool bIncreasing = false;
    bool bSafe = true;
    for(size_t idx = 0; idx < len; ++idx)
    {
        if(idx == idxToSkip) continue;
        num = data[idx];
        if (count == 0)
        {
            prev = num;
            ++count;
            continue;
        }

        if (prev == num || abs(prev - num) > 3)
        {
            bSafe = false;
            break;
        }

        if (count == 1 && prev < num)
        {
            bIncreasing = true;

        }
        if (bIncreasing && num < prev)
        {

            bSafe = false;
            break;

        }
        else if (!bIncreasing && num > prev)
        {

            bSafe = false;
            break;
            
        }
        prev = num;
        ++count;
    }
    return bSafe;
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

    int safe = 0;
    std::string strLine;
    while (std::getline(ifs, strLine))
    {
        char *dup = strdup(strLine.c_str());
               
        char* cNum = strtok(dup, " ");
        std::vector<int> vals;
        do
        {
            vals.push_back(atoi(cNum));
        }
        while((cNum = strtok(nullptr, " ")) != nullptr);
        
        int* data = vals.data();
        size_t len = vals.size();
        if(SafeAfterClean(data, len, len))
        {
            safe++;
        }
        else
        {
            for(size_t idxToSkip = 0; idxToSkip < len; ++idxToSkip)
            {
                if(SafeAfterClean(data, len, idxToSkip))
                {
                    safe++;
                    break;
                }
            }
        }
        free(dup);
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 2: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return safe;
}

int main()
{
    std::cout << "Part 1: " << PartOne() << std::endl;
    std::cout << "Part 2: " << PartTwo() << std::endl;
    return 0;
}
 