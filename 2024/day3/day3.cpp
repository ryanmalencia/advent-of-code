#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include <regex>
#include <cstddef>

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

    int result = 0;
    std::string strLine;
    std::regex regex("mul\\(\\d+,\\d+\\)");
    while (std::getline(ifs, strLine))
    {
        std::sregex_iterator itr(strLine.begin(), strLine.end(), regex);
        std::sregex_iterator end;
        while (itr != end)
        {
            for (size_t idx = 0; idx < itr->size(); ++idx)
            {
                char *str = strdup((*itr)[idx].str().c_str());
                char *tok = strtok(str, "(");
                tok = strtok(nullptr, "(");
                char *tok2 = strtok(tok, ",");
                char *tok3 = strtok(nullptr, ",");
                tok = strtok(tok3, ")");
                result += atoi(tok2) * atoi(tok);
                free(str);
            }
            ++itr;
        }
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 1: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return result;
}

bool isValid(std::map<int, int> &mapValToValid, int val)
{
    bool bValid = true;

    auto ins = mapValToValid.insert({val, 1});

    if (ins.first == mapValToValid.begin())
    {
        return bValid;
    }

    auto prev = std::prev(ins.first);
    mapValToValid[val] = prev->second;

    return prev->second > 0;
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

    int result = 0;
    std::string wholeFile;
    std::string strLine;

    while (std::getline(ifs, strLine))
    {
        wholeFile.append(strLine);
    }

    std::regex regex("mul\\(\\d+,\\d+\\)");
    std::regex doex("do\\(\\)");
    std::regex dontex("don't\\(\\)");

    std::sregex_iterator end;

    std::sregex_iterator itrdo(wholeFile.begin(), wholeFile.end(), doex);

    std::map<int, int> posToValid;
    while (itrdo != end)
    {
        for (size_t idx = 0; idx < itrdo->size(); ++idx)
        {
            posToValid.insert({itrdo->position(), 1});
        }
        ++itrdo;
    }

    std::sregex_iterator itrdont(wholeFile.begin(), wholeFile.end(), dontex);
    std::vector<int> dontPositions;
    while (itrdont != end)
    {
        for (size_t idx = 0; idx < itrdont->size(); ++idx)
        {
            posToValid.insert({itrdont->position(), -1});
        }
        ++itrdont;
    }

    std::sregex_iterator itr(wholeFile.begin(), wholeFile.end(), regex);

    while (itr != end)
    {
        for (size_t idx = 0; idx < itr->size(); ++idx)
        {
            int pos = itr->position();
            if (!isValid(posToValid, pos))
            {
                continue;
            }
            char *str = strdup((*itr)[idx].str().c_str());
            char *tok = strtok(str, "(");
            tok = strtok(nullptr, "(");
            char *tok2 = strtok(tok, ",");
            char *tok3 = strtok(nullptr, ",");
            tok = strtok(tok3, ")");
            result += atoi(tok2) * atoi(tok);
            free(str);
        }
        ++itr;
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 2: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return result;
}

int main()
{
    std::cout << "Part 1: " << PartOne() << std::endl;
    std::cout << "Part 2: " << PartTwo() << std::endl;
    return 0;
}
