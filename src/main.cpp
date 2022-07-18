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

  for (int i = 0; i < 15; i++)
  {
    for (int j = 0; j < 15; j++)
      std::cout << mat_semantic_img[i][j] << "\t";
    std::cout << "\n";
  }

  

  SemanticGraph::Vertex sgv(0,5);
  sgv.add_pixel_inside(0,1);
  sgv.add_pixel_adjacent(2,3);

  std::cout << sgv.get_id_node() << std::endl;
  std::cout << sgv.get_label_semantic() << std::endl;

  auto temp =  sgv.get_pixels_inside();
  std::cout << temp[0][0] << ", " << temp[0][1] << std::endl;

  temp =  sgv.get_pixels_adjacent();
  std::cout << temp[0][0] << ", " << temp[0][1] << std::endl;


  std::cout << "size of mat_semantic_img: " << sizeof(mat_semantic_img) << std::endl;
  std::cout << "size of mat_semantic_img[0]: " << sizeof(mat_semantic_img[0]) << std::endl;
  std::cout << "size of mat_semantic_img[0][0]: " << sizeof(mat_semantic_img[0][0]) << std::endl;
  SemanticGraph::Graph sgg(mat_semantic_img,img_height,img_width);

  return (0);
}