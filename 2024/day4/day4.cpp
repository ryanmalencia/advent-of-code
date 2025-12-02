#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

typedef std::chrono::high_resolution_clock Clock;

int countMatches(const std::vector<std::string>& vec, int rowOffset, int colOffset, int patternlen, const char* str, int rowsToCount, int colsToCount)
{
    int matches = 0;
    for(int i = 0; i < patternlen && i < rowsToCount; ++i)
    {
        bool bMatch = true;
        for(int j = 0; j < patternlen; ++j)
        {
            if(vec[i + rowOffset][j + colOffset] != str[j])
            {
                bMatch = false;
                break;
            }
        }
        if(bMatch) ++matches;
    }

    for(int j = 0; j < patternlen && j < colsToCount; ++j)
    {
        bool bMatch = true;
        for(int i = 0; i < patternlen; ++i)
        {
            if(vec[i + rowOffset][j + colOffset] != str[i])
            {
                bMatch = false;
                break;
            }
        }
        if(bMatch) ++matches;
    }

    bool bMatchDiag = true;
    for(int j = 0; j < patternlen; ++j)
    {
        if(vec[j + rowOffset][j + colOffset] != str[j])
        {
            bMatchDiag = false;
            break;
        }
    }
    if(bMatchDiag) ++matches;

    bMatchDiag = true;
    for(int j = 0; j < patternlen; ++j)
    {
        if(vec[j + rowOffset][(patternlen - 1) - j + colOffset] != str[j])
        {
            bMatchDiag = false;
            break;
        }
    }
    if(bMatchDiag) ++matches;
    return matches;
}

int PartOne(const std::string& pattern)
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
    int rowCount = 0;
    std::vector<std::string> lines;
    while (std::getline(ifs, strLine))
    {
        lines.push_back(strLine);
        ++rowCount;
    }

    std::string revpattern = pattern;
    std::reverse(revpattern.begin(), revpattern.end());
    const char* cPattern = pattern.c_str();
    const char* cRevPattern = revpattern.c_str();
    int count = 0;

    int patternLen = pattern.length();
    for (int i = 0; i < (rowCount - patternLen + 1); ++i)
    {
        int rowsToCount = 1;
        if(i == (rowCount - patternLen)) rowsToCount = patternLen;
        for (int j = 0; j < (rowCount - patternLen + 1); ++j)
        {
            char arr[4][4];
            int colsToCount = 1;
            if(j == (rowCount - patternLen)) colsToCount = patternLen;
            
            int xmasMatches = countMatches(lines, i, j, patternLen, cPattern, rowsToCount, colsToCount);
            int samxMatches = countMatches(lines, i, j, patternLen, cRevPattern, rowsToCount, colsToCount);
            count += xmasMatches;
            count += samxMatches;
        }
    }

    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 1: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return count;
}

bool bMatch(char arr[3][3])
{
    if (arr[1][1] != 'A')
        return false;

    if (arr[0][0] == 'M' && arr[2][2] == 'S')
    {
        if (arr[2][0] == 'M' && arr[0][2] == 'S')
            return true;
        if (arr[0][2] == 'M' && arr[2][0] == 'S')
            return true;
        return false;
    }
    if (arr[2][2] == 'M' && arr[0][0] == 'S')
    {
        if (arr[2][0] == 'M' && arr[0][2] == 'S')
            return true;
        if (arr[0][2] == 'M' && arr[2][0] == 'S')
            return true;
        return false;
    }
    return false;
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
    int idx = 0;
    char *cLines[140];
    while (std::getline(ifs, strLine))
    {
        cLines[idx++] = strdup(strLine.c_str());
    }

    int count = 0;
    for (int i = 0; i < 140 - 2; ++i)
    {
        for (int j = 0; j < 140 - 2; ++j)
        {
            char arr[3][3];
            arr[0][0] = cLines[i][j];
            arr[0][2] = cLines[i][j + 2];
            arr[2][0] = cLines[i + 2][j];
            arr[2][2] = cLines[i + 2][j + 2];
            arr[1][1] = cLines[i + 1][j + 1];
            if (bMatch(arr))
            {
                count++;
            }
        }
    }

    auto timer_end = Clock::now();
    std::cout << "Time to calculate part 2: " << std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer).count() << "us" << std::endl;
    return count;
}

int main()
{
    std::string pattern = "XMAS";
    std::cout << "Part 1: " << PartOne(pattern) << std::endl;
    std::cout << "Part 2: " << PartTwo() << std::endl;
    return 0;
}
