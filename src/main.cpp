#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "sementic_graph_graph.hpp"

int
main (int argc, char** argv)
{
  int img_width = 512;
  int img_height = 512;
  std::string file_name = "../seg.out";

  std::vector<std::array<uint16_t, 2>> list_adjacency;
  bool** mat_adjacency;

  std::vector<std::array<uint16_t, 2>> list_search_current_node;
  std::vector<std::array<uint16_t, 2>> list_search_future_nodes;


  std::ifstream f(file_name);
  int** mat_semantic_img = new int* [img_height];
  for(int i = 0; i<img_height; i++)
      mat_semantic_img[i] = new int[img_width];

  for (int i = 0; i < img_height; i++)
    for (int j = 0; j < img_width; j++)
      f >> mat_semantic_img[i][j];

  
  SemanticGraph::Graph sgg(mat_semantic_img,img_height,img_width);

  return (0);
}