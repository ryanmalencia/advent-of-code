#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../include/string_utils.h"
#include "../../include/timing.h"

bool ValidatePassport(const std::unordered_map<std::string, std::string>& passportEntries)
{
    static std::unordered_set<std::string> requiredEntries {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    static std::unordered_set<std::string> validEyeColors {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

    for(const auto& reqEntry : requiredEntries)
    {
        if (passportEntries.find(reqEntry) == passportEntries.end())
        {
            return false;
        }
    }

    for(const auto& entry : passportEntries)
    {
        if(entry.first == "byr")
        {
            int byr = std::atoi(entry.second.c_str());
            
            if(byr < 1920 || byr > 2002)
            {
                std::cout << "byr out of range" << std::endl;
                return false;
            }
        }
        else if(entry.first == "iyr")
        {
            int iyr = std::atoi(entry.second.c_str());
            if(iyr < 2010 || iyr > 2020)
            {
                std::cout << "iyr out of range" << std::endl;
                return false;
            }
        }
        else if(entry.first == "eyr")
        {
            int eyr = std::atoi(entry.second.c_str());
            if(eyr < 2020 || eyr > 2030)
            {
                std::cout << "eyr out of range" << std::endl;
                return false;
            }
        }
        else if(entry.first == "hgt")
        {
            std::string unit = entry.second.substr(entry.second.length() - 2);
            int height = std::atoi(entry.second.substr(0, entry.second.length() - 2).c_str());

            if(unit == "cm" && (height < 150 || height > 193))
            {
                std::cout << "hgt cm of range" << std::endl;
                return false;
            }
            else if(unit == "in" && (height < 59 || height > 76))
            {
                std::cout << "hgt in of range" << std::endl;
                return false;
            }
        }
        else if(entry.first == "hcl")
        {
            const char* str = entry.second.c_str();
            if(str[0] != '#' || entry.second.length() != 7)
            {
                std::cout << "hcl incorrect" << std::endl;
                return false;
            }

            std::regex alphanumeric_pattern("^#[0-9a-f]{6}$");
            if(!std::regex_match(entry.second, alphanumeric_pattern))
            {
                std::cout << "hcl regex incorrect" << std::endl;
                return false;
            }
        }
        else if(entry.first == "ecl")
        {
            if(validEyeColors.find(entry.second) == validEyeColors.end())
            {
                std::cout << "ecl invalid eye color" << std::endl;
                return false;
            }
        }
        else if(entry.first == "pid")
        {
            if(entry.second.length() != 9)
            {
                std::cout << "pid wrong length" << std::endl;
                return false;
            }

            std::regex alphanumeric_pattern("^[0-9]{9}$");
            if(!std::regex_match(entry.second, alphanumeric_pattern))
            {
                std::cout << "pid regex incorrect" << std::endl;
                return false;
            }
        }
    }
    return true;
}

size_t PartOne()
{
    std::ifstream ifs;
    ifs.open("input.txt");
    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }
    
    START_TIMER(PartOne);

    std::unordered_set<std::string> requiredEntries {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    std::string strLine;
    size_t numberValidPassports = 0;
    std::unordered_map<std::string, std::string> passportEntries;
    while (std::getline(ifs, strLine))
    {
        if(strLine.length() == 0)
        {
            bool bValid = true;
            for(const auto& reqEntry : requiredEntries)
            {
                if (passportEntries.find(reqEntry) == passportEntries.end())
                {
                    bValid = false;
                    break;
                }
            }

            if(bValid)
            {
                ++numberValidPassports;
            }
            passportEntries.clear();
            continue;
        }

        for(const auto& entries : string_utils::split_string(strLine, " "))
        {
            const auto& keyVal = string_utils::split_string(entries, ":");
            if(keyVal.size() != 2) continue;

            passportEntries.insert({keyVal[0], keyVal[1]});
        }
    }

    if(passportEntries.size() > 0)
    {
        bool bValid = true;
        for(const auto& reqEntry : requiredEntries)
        {
            if (passportEntries.find(reqEntry) == passportEntries.end())
            {
                bValid = false;
                break;
            }
        }
        if(bValid)
        {
            ++numberValidPassports;
        }
    }

    END_TIMER(PartOne);
    PRINT_TIMER_US(PartOne);
    return numberValidPassports;
}

size_t PartTwo()
{
    std::ifstream ifs;
    ifs.open("input.txt");
    if (!ifs.is_open())
    {
        std::cout << "Could not open input file" << std::endl;
        return 0;
    }
    
    START_TIMER(PartTwo);

    std::string strLine;
    size_t numberValidPassports = 0;
    std::unordered_map<std::string, std::string> passportEntries;
    while (std::getline(ifs, strLine))
    {
        if(strLine.length() == 0)
        {
            bool bValid = ValidatePassport(passportEntries);
            if(bValid)
            {
                ++numberValidPassports;
            }
            passportEntries.clear();
            continue;
        }

        for(const auto& entries : string_utils::split_string(strLine, " "))
        {
            const auto& keyVal = string_utils::split_string(entries, ":");
            if(keyVal.size() != 2) continue;

            passportEntries.insert({keyVal[0], keyVal[1]});
        }
    }

    if(passportEntries.size() > 0)
    {
        bool bValid = ValidatePassport(passportEntries);
        if(bValid)
        {
            ++numberValidPassports;
        }
    }

    END_TIMER(PartTwo);
    PRINT_TIMER_US(PartTwo);
    return numberValidPassports;
}

int main()
{
    size_t partOne = PartOne();
    size_t partTwo = PartTwo();
    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl;
    return 0;
}
