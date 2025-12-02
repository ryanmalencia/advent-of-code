#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

bool IsValidUpdate(const std::set<std::pair<int, int>> &invalidRules, const std::vector<int> &pages)
{
    bool bValidUpdate = true;
    for (size_t idx = 0; bValidUpdate && idx < pages.size() - 1; ++idx)
    {
        for (size_t otherIdx = idx + 1; bValidUpdate && otherIdx < pages.size(); ++otherIdx)
        {
            int other = pages[otherIdx];
            int before = pages[idx];
            auto invalidMatch = invalidRules.find({before, other});
            if (invalidMatch != invalidRules.end())
            {
                bValidUpdate = false;
                continue;
            }
        }
    }
    return bValidUpdate;
}

std::set<std::pair<int, int>> validRules;
struct less_than_key
{
    inline bool operator()(const int &struct1, const int &struct2)
    {
        return validRules.find({struct1, struct2}) != validRules.end();
    }
};

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

    std::map<int, int> pageToIndex;
    std::set<std::pair<int, int>> invalidRules;

    std::string strLine;
    bool bReadingRules = true;
    int totalMiddlePageNumbers = 0;
    while (std::getline(ifs, strLine))
    {
        if (strLine.length() == 0)
        {
            bReadingRules = false;
            break;
        }

        char *cLine = strdup(strLine.c_str());
        if (bReadingRules)
        {
            int before = atoi(strtok(cLine, "|"));
            int after = atoi(strtok(nullptr, "|"));
            invalidRules.insert({after, before});
            validRules.insert({before, after});
            free(cLine);
        }
    }

    while (std::getline(ifs, strLine))
    {
        char *cLine = strdup(strLine.c_str());
        std::vector<int> pages;
        char *tok = strtok(cLine, ",");
        while (tok != NULL)
        {
            pages.push_back(atoi(tok));
            tok = strtok(nullptr, ",");
        }
        free(cLine);
        if (!IsValidUpdate(invalidRules, pages))
        {
            std::sort(pages.begin(), pages.end(), less_than_key());
            int middleNum = pages[pages.size() / 2];
            totalMiddlePageNumbers += middleNum;
        }
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 2: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return totalMiddlePageNumbers;
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

    std::map<int, int> pageToIndex;
    std::set<std::pair<int, int>> invalidRules;

    std::string strLine;
    bool bReadingRules = true;
    int totalMiddlePageNumbers = 0;

    while (std::getline(ifs, strLine))
    {
        if (strLine.length() == 0)
        {
            bReadingRules = false;
            continue;
        }

        char *cLine = strdup(strLine.c_str());
        if (bReadingRules)
        {
            int before = atoi(strtok(cLine, "|"));
            int after = atoi(strtok(nullptr, "|"));
            invalidRules.insert({after, before});
            free(cLine);
        }
        else
        {
            std::vector<int> pages;
            char *tok = strtok(cLine, ",");
            while (tok != NULL)
            {
                pages.push_back(atoi(tok));
                tok = strtok(nullptr, ",");
            }
            free(cLine);
            if (IsValidUpdate(invalidRules, pages))
            {
                int middleNum = pages[pages.size() / 2];
                totalMiddlePageNumbers += middleNum;
            }
        }
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 1: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return totalMiddlePageNumbers;
}

int main()
{
    std::cout << "Part 1: " << PartOne() << std::endl;
    std::cout << "Part 2: " << PartTwo() << std::endl;
    return 0;
}
