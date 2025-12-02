#include <algorithm>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
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
    std::string strLine;
    std::vector<int> leftSide, rightSide;
    while (std::getline(ifs, strLine))
    {
        const char* line = strLine.c_str();
        leftSide.push_back(atoi(line));
        rightSide.push_back(atoi(line + 8));
    }
    std::sort(leftSide.begin(), leftSide.end());
    std::sort(rightSide.begin(), rightSide.end());

    int distance = 0;
    const int* rd = rightSide.data();
    const int* ld = leftSide.data();
    for (size_t idx = 0; idx < leftSide.size(); ++idx)
    {
        int r = rd[idx];
        int l = ld[idx];
        if (r == l)
            continue;

        if (l < r)
        {
            distance += (r - l);
            continue;
        }
        distance += (l - r);
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate distance: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return distance;
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
    std::string strLine;
    std::unordered_map<int, int> leftSide, rightSide;
    while (std::getline(ifs, strLine))
    {
        char *dup = strdup(strLine.c_str());
        int left = atoi(strtok(dup, " "));
        int right = atoi(strtok(nullptr, " "));
        free(dup);

        auto match1 = leftSide.find(left);
        if (match1 != leftSide.end())
        {
            match1->second = match1->second + 1;
        }
        else
        {
            leftSide.insert({ left , 1 });
        }
        auto match2 = rightSide.find(right);
        if (match2 != rightSide.end())
        {
            match2->second = match2->second + 1;
        }
        else
        {
            rightSide.insert({ right , 1 });
        }
    }

    int similarity = 0;
    for (const auto& val : leftSide)
    {
        auto match = rightSide.find(val.first);
        if (match == rightSide.end()) continue;

        similarity += val.first * match->second;
    }
    auto timer_end = Clock::now();
    std::cout << "Time to calculate similarity for Part 2: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return similarity;
}

int main()
{
    std::cout << "Part 1: " << PartOne() << std::endl;
    std::cout << "Part 2: " << PartTwo() << std::endl;
    return 0;
}
