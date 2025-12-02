#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string.h>
#include "../../include/timing.h"

#ifdef WINDOWS
#define strtok_r strtok_s
#endif

inline unsigned int gamecountstrtok(const std::string& input, std::map<std::string, int>& maxvals)
{
    char *save_ptr1, *save_ptr2, *save_ptr3;
    char* cline = strdup(input.c_str());
    char* gameinfo = strtok(cline, ":");
    unsigned int gamenum = std::atoi(gameinfo + 4);
    
    char* games = strtok(0, ":");

    char* gamesaveptr;
    char* game = strtok_r(games, ";", &gamesaveptr);

    while(game != nullptr)
    {
        char* dierollsetptr;
        char* dierollset = strtok_r(game, ",", &dierollsetptr);
        while(dierollset != nullptr)
        {
            dierollset += 1;
            char* dierollptr;
            char* dieroll = strtok_r(dierollset, " ", &dierollptr);
            int idx = 0;
            int dienum = 0;
            std::string diecolor;
            while(dieroll != nullptr)
            {
                if(idx == 0)
                {
                    dienum = std::atoi(dieroll);
                    if(dienum > 14) return 0;
                }
                else
                {
                    diecolor = dieroll;
                }
                dieroll = strtok_r(0, " ", &dierollptr);
                ++idx;
            }
            if(dienum > maxvals[diecolor]) return 0;
            dierollset = strtok_r(0, ",", &dierollsetptr);
        }
        game = strtok_r(0, ";", &gamesaveptr);
    }
    free(cline);
    return gamenum;
}

int main()
{
    START_TIMER(main_timer);
    std::ifstream file("input.txt");
    std::string line;
    unsigned int total = 0;

    std::map<std::string, int> mapvals = {{"red", 12}, {"green",13},{"blue",14}};

    while(std::getline(file, line))
    {
        total += gamecountstrtok(line, mapvals);
    }
    std::cout << total << std::endl;
    END_TIMER(main_timer);
    PRINT_TIMER_US(main_timer);
    return 0;
}
