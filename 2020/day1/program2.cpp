#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::ifstream in("input.txt");
    std::vector<int> vecInput;
    int val;
    while(in >> val)
    {
        vecInput.push_back(val);
    }

    
    std::sort(vecInput.begin(), vecInput.end());

    int s, m, l, a;
    const size_t len = vecInput.size();
    for(int i =0; i < len; ++i)
    {
        l = vecInput[len - i - 1];
        m = vecInput[len - i - 2];
        s = vecInput[0];
        int count = 0, count2 = i;
        while((m + l) > 2020)
        {
            m = vecInput[len - ++count2 - 2];
        }
        while((s + m + l) < 2020)
        {
            s = vecInput[++count];
            if((s + m + l) > 2020)
            {
                m = vecInput[len - ++count2 - 2];
                count = -1;
            }
        }
        if((s + m + l) == 2020)
        {
            a = s * m * l;
            break;
        }
    }
    std::cout << "Answer: " << a << std::endl;
    return 0;
}
