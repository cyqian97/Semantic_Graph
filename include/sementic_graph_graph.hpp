#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "sementic_graph_vertex.hpp"


namespace SemanticGraph{


class Graph
{
private:
    const int image_height;
    const int image_width;
    int** image_semantic;

    std::vector<Vertex> vertices;
    bool** mat_adjacency;

    int num_pixels;

    int** mat_id_vertex;

    bool** mat_scanned;
    int num_scanned = 0;

    std::vector<int*> queue_current;
    std::vector<int*> queue_next;

    int id_vertex_current = 0;
    Vertex* vertex_current_ptr;

public:

    Graph(int** const img_semantic, const int image_height, const int image_width);
    ~Graph();

    void flood_fill();
};



Graph::Graph(int** const _image_semantic, const int _image_height, const int _image_width):
    image_semantic(_image_semantic), image_height(_image_height), image_width(_image_width)
{
    num_pixels = image_height*image_width;

    mat_id_vertex = new int* [image_height];
    for(int i = 0; i<image_height; i++)
        mat_id_vertex[i] = new int[image_width];
    for(int i = 0; i<image_height; i++)
        for(int j = 0; j<image_width; j++)
            mat_id_vertex[i][j] = -1;
    
    mat_scanned = new bool* [image_height];
    for(int i = 0; i<image_height; i++)
        mat_scanned[i] = new bool[image_width];
    for(int i = 0; i<image_height; i++)
        for(int j = 0; j<image_width; j++)
            mat_scanned[i][j] = false;

    int temp[2] = {0,0};
    queue_current.push_back(temp);
    vertex_current_ptr = new Vertex(id_vertex_current++,image_semantic[0][0]);

}


Graph::~Graph()
{
}

void Graph::flood_fill()
{
    for(const auto &pixel: queue_current)
    {
        
    }
}



} // namespace SemanticGraph