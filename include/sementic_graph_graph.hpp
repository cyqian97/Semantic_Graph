#include <map>
#include <array>
#include <vector>
#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "sementic_graph_vertex.hpp"


namespace SemanticGraph{


class Graph
{
private:
// height=> row_num, width=> col_num, mat[row][col], pixel={row_num,col_num}
    const int image_height;
    const int image_width;
    int** mat_image_semantic;

    std::vector<Vertex*> vec_ptr_vertex;
    bool** mat_adjacency;
    std::map<int, std::vector<Vertex*>>map_label_to_vertices;

    int num_pixels;

    int** mat_id_vertex;

    bool** mat_scanned;

    std::vector<int*> queue_current;
    std::vector<int*> queue_next;

    int id_vertex_current = 0;
    Vertex* ptr_vertex_current;

    void flood_fill(); // Flood fill loops to extract vertex and adjacency
    void build_graph(); // Fill the adjacency matrix

public:

    Graph(int** const img_semantic, const int image_height, const int image_width);
    ~Graph();

};



Graph::Graph(int** const _mat_image_semantic, const int _image_height, const int _image_width):
    mat_image_semantic(_mat_image_semantic), image_height(_image_height), image_width(_image_width)
{
    std::cout << "Start building adjacency graph..." << std::endl;

    // Timer
    auto start = std::chrono::high_resolution_clock::now();
    
    num_pixels = image_height*image_width;

    mat_id_vertex = new int* [image_height];
    for(int i = 0; i<image_height; i++)
    {
        mat_id_vertex[i] = new int[image_width];
        std::fill_n(mat_id_vertex[i],image_width,-1);
    }
    
    mat_scanned = new bool* [image_height];
    for(int i = 0; i<image_height; i++)
        mat_scanned[i] = new bool[image_width]();

    int pixel_init[2] = {0,0};
    queue_current.push_back(pixel_init);
    mat_scanned[0][0] = true;
    ptr_vertex_current = new Vertex(id_vertex_current++,mat_image_semantic[0][0]);
    vec_ptr_vertex.push_back(ptr_vertex_current);
    ptr_vertex_current->add_pixel_inside(0,0);
    mat_id_vertex[0][0] = 0;

    // update map_label_to_vertices
    auto iter_map = map_label_to_vertices.find(mat_image_semantic[0][0]);
    if (iter_map != map_label_to_vertices.end())
    {
        iter_map->second.push_back(ptr_vertex_current);
    }
    else
    {
        std::vector<Vertex*> _temp_vec_ptr_vertex{ptr_vertex_current};
        map_label_to_vertices.insert(std::make_pair(mat_image_semantic[0][0], _temp_vec_ptr_vertex)); 
    }

    flood_fill();

    auto pixel_next_ptr = queue_next.begin();
    while(!queue_next.empty())
    {   
        auto q_ = *pixel_next_ptr;
        if(!mat_scanned[q_[0]][q_[1]])
        {
            queue_current.push_back(q_);
            mat_scanned[q_[0]][q_[1]] = true;
            ptr_vertex_current = new Vertex(id_vertex_current++,mat_image_semantic[q_[0]][q_[1]]);
            vec_ptr_vertex.push_back(ptr_vertex_current);
            ptr_vertex_current->add_pixel_inside(q_[0], q_[1]);
            mat_id_vertex[q_[0]][q_[1]] = ptr_vertex_current->get_id_node();


            // update map_label_to_vertices
            iter_map = map_label_to_vertices.find(mat_image_semantic[q_[0]][q_[1]]);
            if (iter_map != map_label_to_vertices.end())
            {
                iter_map->second.push_back(ptr_vertex_current);
            }
            else
            {
                std::vector<Vertex*> _temp_vec_ptr_vertex{ptr_vertex_current};
                map_label_to_vertices.insert(std::make_pair(mat_image_semantic[q_[0]][q_[1]], _temp_vec_ptr_vertex)); 
            }

            flood_fill();
        }
        pixel_next_ptr = queue_next.begin();
        queue_next.erase(pixel_next_ptr); 
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;

    // std::ofstream myfile ("mat_id_vertex.txt");
    // if (myfile.is_open())
    // {
    //     for(int i = 0; i<image_height; i++)
    //     {
    //         for(int j = 0; j<image_width; j++)
    //             myfile << mat_id_vertex[i][j] << "\t";
    //         myfile << "\n";
    //     }
    // }
    // myfile.close();

    // Print label to vertices map
    // std::map<int, std::vector<Vertex*>>::iterator it;

    // for (it = map_label_to_vertices.begin(); it != map_label_to_vertices.end(); it++)
    // {
    //     std::cout << "Vertice with label " << it->first << std::endl;
    //     for (auto & ptr_vertex : it->second)
    //     {
    //         std::cout << '\t' << ptr_vertex->get_id_node();
    //     }
    //     std::cout << '\n' << std::endl;
    // }


    for (auto & ptr_vertex : vec_ptr_vertex)
        ptr_vertex->calc_center();

    // Obtain the adjacency matrix can be done in the process of building the vertices.
    start = std::chrono::high_resolution_clock::now();
    build_graph(); 
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;


    std::cout << "Finish building adjacency graph..." << std::endl;


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
            if(mat_image_semantic[p_[0]][p_[1]] == ptr_vertex_current->get_label_semantic())
            {
                ptr_vertex_current->add_pixel_inside(p_[0],p_[1]);
                mat_scanned[p_[0]][p_[1]] = true;
                mat_id_vertex[p_[0]][p_[1]] = ptr_vertex_current->get_id_node();
                queue_current.push_back(p_); //push_back changes .begin()
            // std::cout << "Checkpoint 2" << std::endl;
            }
            else
            {
                queue_next.push_back(p_);
                ptr_vertex_current->add_pixel_adjacent(p_[0],p_[1]);

                // std::vector<int*> v = ptr_vertex_current->get_pixels_adjacent();

                // std::cout << "adjacency size: " << (ptr_vertex_current->get_pixels_adjacent()).size() << std::endl;
                // for(const auto &p_a:ptr_vertex_current->get_pixels_adjacent())
                //     std::cout << "{" << p_a[0] << ", " << p_a[1] << "}, " ;
                // std::cout << std::endl;
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

void Graph::build_graph()
{

    mat_adjacency = new bool* [vec_ptr_vertex.size()];
    for(int i = 0; i<vec_ptr_vertex.size(); i++)
        mat_adjacency[i] = new bool[vec_ptr_vertex.size()]();

    for(int i=0; i<vec_ptr_vertex.size(); i++)
    {
        // std::cout << "vertex_id: " << vec_ptr_vertex[i]->get_id_node() << std::endl;
        std::vector<int*> v = (vec_ptr_vertex[i])->get_pixels_adjacent();
        for(const auto &p_:v)
        {
            // std::cout << "p = {" << p_[0] << ", " << p_[1] << "}" << std::endl;
            for(int j=0; j<vec_ptr_vertex.size(); j++) 
            {   
                if(vec_ptr_vertex[j]->is_pixel_inside(p_[0],p_[1]))
                {
                    mat_adjacency[i][j] = true;
                    // std::cout << "adj\n";
                }
            }
        }
    }    

    // std::ofstream myfile ("mat_adjacency.txt");
    // if (myfile.is_open())
    // {
    //     for(int i = 0; i<vec_ptr_vertex.size(); i++)
    //     {
    //         for(int j = 0; j<vec_ptr_vertex.size(); j++)
    //             myfile << mat_adjacency[i][j] << "\t";
    //         myfile << "\n";
    //     }
    // }
    // myfile.close();

    // myfile.open("labels.txt");
    // if (myfile.is_open())
    // {
    //     for(int i = 0; i<vec_ptr_vertex.size(); i++)
    //     {
    //         myfile << (vec_ptr_vertex[i])->get_label_semantic() << "\t";
    //     }
    // }
    // myfile.close();
}

} // namespace SemanticGraph