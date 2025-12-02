#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>

int main()
{
    std::ifstream in("input.txt");
    std::string line;
    int iValidPasswordCount = 0;
    while(std::getline(in, line))
    {
        char *limits = strtok (&line[0] , " ");
        char *character = strtok(NULL, " ");
        char *password = strtok(NULL, " ");
        char *strposone = strtok(limits, "-");
        char *strpostwo = strtok(NULL, "-");
        char *characterToMatch = strtok(character, ":");
        
        int posone = atoi(strposone);
        int postwo = atoi(strpostwo);

        size_t passlen = strlen(password);
        
        char cposone = password[posone - 1];
        char cpostwo = password[postwo - 1];


        char match = characterToMatch[0];
        if(cposone == match && cpostwo == match) continue;
        if(cposone != match && cpostwo != match) continue;
        iValidPasswordCount++;
    }
    
    std::cout << "Valid password count: " << iValidPasswordCount << std::endl;
    return 0;
}
