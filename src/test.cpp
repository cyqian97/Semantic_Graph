#include <array>
#include <iostream>

int main()
{
    int** A;
    A = new int* [5];

    for(int i = 0; i<5; i++)
        A[i] = new int[5];
    
    for(int i = 0; i<5; i++)
        for(int j = 0; j<5; j++)
            A[i][j] = j+5*i;

    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j<5; j++)
            std::cout << A[i][j] << "\t";
        std::cout << "\n";
    }

    return(0);
}