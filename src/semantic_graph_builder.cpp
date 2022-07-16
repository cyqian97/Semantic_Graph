#include <array>
#include <vector>
#include <fstream>
#include <iostream>

int
main (int argc, char** argv)
{

  // int mat_adjacency[l][l] = {};
  std::vector<std::array<uint16_t, 2>> list_adjacency;

  std::ifstream f("test.out");

  int l = 3;
  int A[l][l] = {};
  for (int i = 0; i < l; i++)
    for (int j = 0; j < l; j++)
      f >> A[i][j];

  
  for (int i = 0; i < l; i++)
  {
    for (int j = 0; j < l; j++)
    {
      std::cout << A[i][j] << "\t";
    }
    std::cout << "\n";
  }


  return (0);
}