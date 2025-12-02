#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include "../../include/timing.h"

int main()
{
    START_TIMER(main_timer);
    std::string filename("input.txt");
    FILE* fp = fopen(filename.c_str(), "r");
    if(!fp)
    {
        std::cout << "Unable to open file " << filename.c_str() << std::endl;
        return EXIT_FAILURE;
    }
    char line[4098];
    line[0] = '\0';
    fgets(line, 4098 - 1, fp);
    int length = strlen(line);
    int msgLength = 4;
    for(int i = 0; i < length - (msgLength - 1);)
    {
        bool bContinue = true;
        for(int j = 0; j < msgLength - 1; ++j)
        {
            bContinue = true;
            for(int k = j + 1; k < msgLength; ++k)
            {
                if(line[i + j] == line[i + k])
                {
                    bContinue = false;
                    i += (j + 1);
                }
                if(!bContinue)
                    break;
            }
            if(!bContinue)
                break;
        }
        if(!bContinue) continue;
        std::cout << (i + msgLength) << std::endl;
        break;
    }

    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    fclose(fp);
    return EXIT_SUCCESS;
}
