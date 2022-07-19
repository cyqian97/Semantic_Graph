#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "sementic_graph_vertex.hpp"


namespace SemanticGraph{


class Graph
{
private:
// height=> row_num, width=> col_num, mat[row][col], pixel={row_num,col_num}
    const int image_height;
    const int image_width;
    int** mat_image_semantic;

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



Graph::Graph(int** const _mat_image_semantic, const int _image_height, const int _image_width):
    mat_image_semantic(_mat_image_semantic), image_height(_image_height), image_width(_image_width)
{
    std::cout << "Start initialization..." << std::endl;
    num_pixels = image_height*image_width;

    mat_id_vertex = new int* [image_height];
    for(int i = 0; i<image_height; i++)
    {
        mat_id_vertex[i] = new int[image_width];
        std::fill_n(mat_id_vertex[i],image_width,-1);
    }
    // for(int i = 0; i<image_height; i++)
    //     for(int j = 0; j<image_width; j++)
    //         mat_id_vertex[i][j] = -1;
    
    mat_scanned = new bool* [image_height];
    for(int i = 0; i<image_height; i++)
        mat_scanned[i] = new bool[image_width]();
    // for(int i = 0; i<image_height; i++)
    //     for(int j = 0; j<image_width; j++)
    //         mat_scanned[i][j] = false;

    int pixel_init[2] = {0,0};
    queue_current.push_back(pixel_init);
    mat_scanned[0][0] = true;
    vertex_current_ptr = new Vertex(id_vertex_current++,mat_image_semantic[0][0]);
    vertex_current_ptr->add_pixel_inside(0,0);
    mat_id_vertex[0][0] = 0;
    std::cout << "Complete initialization..." << std::endl;

    std::cout << "Start first flood fill..." << std::endl;
    flood_fill();
    std::cout << "Complete first flood fill..." << std::endl;

    auto pixel_next_ptr = queue_next.begin();
    while(!queue_next.empty())
    {   
        auto q_ = *pixel_next_ptr;
        if(!mat_scanned[q_[0]][q_[1]])
        {
            queue_current.push_back(q_);
            mat_scanned[q_[0]][q_[1]] = true;
            vertex_current_ptr = new Vertex(id_vertex_current++,mat_image_semantic[q_[0]][q_[1]]);
            vertex_current_ptr->add_pixel_inside(q_[0], q_[1]);
            mat_id_vertex[q_[0]][q_[1]] = vertex_current_ptr->get_id_node();
            std::cout << "Start a flood fill..." << std::endl;
            flood_fill();
            std::cout << "Complete a flood fill..." << std::endl;
        }
        pixel_next_ptr = queue_next.begin();
        queue_next.erase(pixel_next_ptr); 
        std::cout << "queue next size:" << queue_next.size() << std::endl;
    }
    std::cout << "Complete building the graph..." << std::endl;

    std::ofstream myfile ("example.txt");
    if (myfile.is_open())
    {
        for(int i = 0; i<image_height; i++)
        {
            for(int j = 0; j<image_width; j++)
                myfile << mat_id_vertex[i][j] << "\t";
            myfile << "\n";
        }
    }
    myfile.close();


}


Graph::~Graph()
{
}

void Graph::flood_fill()
{
    auto pixel_now_ptr = queue_current.begin();
    while(!queue_current.empty())
    {
        // std::cout << "Enter while loop" << std::endl;
        int* neighbors[4];
        neighbors[0] = new int[2]{(*pixel_now_ptr)[0]-1, (*pixel_now_ptr)[1]};
        neighbors[1] = new int[2]{(*pixel_now_ptr)[0], (*pixel_now_ptr)[1]+1};
        neighbors[2] = new int[2]{(*pixel_now_ptr)[0]+1, (*pixel_now_ptr)[1]};
        neighbors[3] = new int[2]{(*pixel_now_ptr)[0], (*pixel_now_ptr)[1]-1};
        // for(int i = 0; i<4; i++)
        // {
        //     std::cout << "neighbors["<< i << "] = {" << neighbors[i][0] << ", " << neighbors[i][1] << "}" << std::endl;
        // }

        int* p_;
        for(int i = 0; i<4; i++)
        {
            // std::cout << "Checkpoint 0" << std::endl;
            p_ = neighbors[i];
            if( p_[0] < 0 || p_[0] > image_height-1 ||
                p_[1] < 0 || p_[1] > image_width-1 ||
                mat_scanned[p_[0]][p_[1]])
                continue;
            // std::cout << "Checkpoint 1" << std::endl;
            if(mat_image_semantic[p_[0]][p_[1]] == vertex_current_ptr->get_label_semantic())
            {
                vertex_current_ptr->add_pixel_inside(p_[0],p_[1]);
                mat_scanned[p_[0]][p_[1]] = true;
                mat_id_vertex[p_[0]][p_[1]] = vertex_current_ptr->get_id_node();
                queue_current.push_back(p_); //push_back changes .begin()
            // std::cout << "Checkpoint 2" << std::endl;
            }
            else
            {
                queue_next.push_back(p_);
                vertex_current_ptr->add_pixel_adjacent(p_[0],p_[1]);
            // std::cout << "Checkpoint 3" << std::endl;
            }
        }
        if(!queue_current.empty())
        {
            pixel_now_ptr = queue_current.begin(); 
            queue_current.erase(pixel_now_ptr); //erase automatically move .begin() to the next
        }
        // std::cout << "Checkpoint 4" << std::endl;
    }
}



} // namespace SemanticGraph