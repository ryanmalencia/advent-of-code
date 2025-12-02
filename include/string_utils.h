#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace string_utils {
    std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
    {
        std::vector<std::string> strings;

        size_t start = 0;
        size_t end = str.find(delimiter);
        while(end != std::string::npos)
        {
            strings.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }

        strings.push_back(str.substr(start));
        return strings;
    }
}
