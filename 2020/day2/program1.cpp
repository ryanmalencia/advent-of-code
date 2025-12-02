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
        char *strmin = strtok(limits, "-");
        char *strmax = strtok(NULL, "-");
        char *characterToMatch = strtok(character, ":");
        
        int min = atoi(strmin);
        int max = atoi(strmax);

        char match = characterToMatch[0];
        size_t len = strlen(password);
        int count = 0;
        for(size_t i = 0; i < len; ++i)
        {
            if(password[i] == match) count++;
        }

        if(count >= min && count <= max)
            iValidPasswordCount++;
    }
    
    std::cout << "Valid password count: " << iValidPasswordCount << std::endl;
    return 0;
}
