#pragma once

#include <iostream>
#include <cmath>

namespace num_utils {
    unsigned int num_digits(unsigned int num)
    {
        if (num == 0)
        {
            return 1;
        }

        return static_cast<unsigned int>(std::floor(std::log10(num))) + 1;
    }
}
