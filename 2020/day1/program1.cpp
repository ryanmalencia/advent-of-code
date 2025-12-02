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

    int s, l, a;
    const size_t len = vecInput.size();
    for(int i =0; i < len; ++i)
    {
        l = vecInput[len - i - 1];
        s = vecInput[0];
        int count = 0;
        while((s + l) < 2020)
        {
            s = vecInput[++count];
        }
        if((s + l) == 2020)
        {
            a = s * l;
            break;
        }
    }
    std::cout << "Answer: " << a << std::endl;
    return 0;
}
