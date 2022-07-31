#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

namespace SemanticGraph{
class Vertex
{
private:
    const int id_node = -1;
    const int label_semantic = -1;

    double center[2];

    std::vector<int*> pixels_inside;
    std::vector<int*> pixels_adjacent;

public:

    // Vertex();
    Vertex(int _id_node, int _label_semantic);
    ~Vertex();

    void add_pixel_inside(int row, int col);
    void add_pixel_adjacent(int row, int col);

    bool is_pixel_inside(int row, int col);
    bool is_pixel_adjacent(int row, int col);

    void calc_center();

    int get_id_node(){return id_node;}
    double* get_center_node(){return center;}
    int get_label_semantic(){return label_semantic;}
    std::vector<int*> get_pixels_inside(){return pixels_inside;}
    std::vector<int*> get_pixels_adjacent(){return pixels_adjacent;}
};

// Vertex::Vertex()
// {
// }

Vertex::Vertex(int _id_node, int _label_semantic):
    id_node(_id_node), label_semantic(_label_semantic)
{
}

Vertex::~Vertex()
{
}

void Vertex::add_pixel_inside(int row, int col)
{
    // int temp[2] = {row,col};
    // pixels_inside.push_back(temp);

    pixels_inside.push_back(new int[2]{row,col}); 
}

void Vertex::add_pixel_adjacent(int row, int col)
{
    // int temp[2] = {row,col};
    // std::cout << temp[0] << "," << temp[1] << std::endl;
    // pixels_adjacent.push_back(temp); {row,col}

    pixels_adjacent.push_back(new int[2]{row,col}); 

    // for(int i=0; i< pixels_adjacent.size(); i++)
    //     std::cout << "{" << pixels_adjacent[i][0] << ", " << pixels_adjacent[i][1] << "}, " ;
    // std::cout << std::endl;
}

bool Vertex::is_pixel_inside(int row, int col)
{
    // int temp[2] = {row,col};
    // auto iter_pixel = std::find(
    //     pixels_inside.begin(),pixels_inside.end(),temp);
    
    // if(iter_pixel == pixels_inside.end())
    //     return false;
    for(const auto &p:pixels_inside)
        if(p[0] == row && p[1] == col)
            return true;   
    return false;
}

bool Vertex::is_pixel_adjacent(int row, int col)
{
    // int temp[2] = {row, col};
    // auto iter_pixel = std::find(
    //     pixels_adjacent.begin(),pixels_adjacent.end(),temp);

    // if(iter_pixel == pixels_adjacent.end())
    //     return false;
    
    // return true;   

    for(const auto &p:pixels_adjacent)
        if(p[0] == row && p[1] == col)
            return true;   
    return false;
}

void Vertex::calc_center()
{
    center[0] = 0.;
    center[1] = 0.;

    for(auto& pixel: pixels_inside)
    {
        center[0] += pixel[0];
        center[1] += pixel[1];
    }
    center[0] /= pixels_inside.size();
    center[1] /= pixels_inside.size();
    // std::cout << "Vertex id=" << id_node << " center = " << center[0] << " , " << center[1] << std::endl;
}
} // namespace SemanticGraph