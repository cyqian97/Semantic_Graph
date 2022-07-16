#include <array>
#include <iostream>

int main()
{
    bool** A;
    A = new bool* [5];

    bool temp = true;

    for(int i = 0; i<5; i++)
        A[i] = new bool[5];
    
    for(int i = 0; i<5; i++)
        for(int j = 0; j<5; j++)
        {
            A[i][j] = temp;
            temp = !temp;
        }

    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
            std::cout << A[i][j] << "\t";
        std::cout << "\n";
    }

    return(0);
}