#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> temp = {0,1,2,3,4};
    auto t = temp.begin();
    while(!temp.empty())
    {
        std::cout << "t:" << *t << std::endl;
        if(*t < 2) temp.push_back(9);
        t = temp.begin();
        temp.erase(t);
    }

    int* t2;
    t2 = new int[2]{1,2};
    std::cout << "t2:" << t2[0] << "," << t2[1] << std::endl;

    bool** t3;
    t3 = new bool*[2];
    t3[0] = new bool[3]();
    std::cout << "t3:" << t3[0][0] << "," << t3[0][1]  << "," << t3[0][2] << std::endl;
    std::fill_n(t3[0],3,1);
    std::cout << "t3:" << t3[0][0] << "," << t3[0][1]  << "," << t3[0][2] << std::endl;

    return(0);
}