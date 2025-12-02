#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);

    //std::vec<std::string, char> numstrings = {{"one", 49}, {"two", 50}, {"three", 51}, {"four", 52}, {"five", 53}, {"six",54}, {"seven",55}, {"eight", 56}, {"nine",57}};
    

    const char* one = "one";
    const char* two = "two";
    const char* three = "three";
    const char* four = "four";
    const char* five = "five";
    const char* six = "six";
    const char* seven = "seven";
    const char* eight = "eight";
    const char* nine = "nine";

    const char* stringvals[9]={ one, two, three, four, five, six, seven, eight, nine};


    std::ifstream file("input.txt");
    std::string line;
    int total = 0;
    char str[3];
    str[2] = '\0';
    bool bFirst = true;
    while(std::getline(file, line))
    {
        size_t linelength = line.length();
        bFirst = true;
        unsigned int firstIndex = 0, lastIndex = 0;
        int idx = 0;
        for(const auto& c : line)
        {
            if(c > 47 && c < 58)
            {
                if(bFirst)
                {
                    str[0] = c;
                    str[1] = c;
                    firstIndex = idx;
                    lastIndex = idx;
                    bFirst = false;
                }
                else
                {
                    str[1] = c;
                    lastIndex = idx;
                }
            }
            ++idx;
        }

        if(firstIndex > 0 || lastIndex < (linelength - 1))
        {
            for(unsigned int idx = 0; idx < 9; ++idx)
            {
                const char* val = stringvals[idx];
                if(firstIndex > 0)
                {
                    auto idxfound = line.find(val);
                    if(idxfound == std::string::npos) continue;
                    if(idxfound < firstIndex)
                    {
                        str[0] = idx + 49;
                        firstIndex = idxfound;
                        if(firstIndex == 0) break;
                    }
                }
                if(lastIndex < (linelength - 1))
                {
                    auto idxfound = line.rfind(val);
                    if(idxfound == std::string::npos) continue;
                    if(idxfound > lastIndex)
                    {
                        str[1] = idx + 49;
                        lastIndex = idxfound;
                    }
                }
            }
        }
        total += std::atoi(str);
    }
    std::cout << total << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}