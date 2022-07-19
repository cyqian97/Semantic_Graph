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

    int get_id_node(){return id_node;}
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
    int temp[2] = {row,col};
    pixels_inside.push_back(temp);
}

void Vertex::add_pixel_adjacent(int row, int col)
{
    int temp[2] = {row,col};
    pixels_adjacent.push_back(temp);
}

bool Vertex::is_pixel_inside(int row, int col)
{
    int temp[2] = {row,col};
    auto iter_pixel = std::find(
        pixels_inside.begin(),pixels_inside.end(),temp);

    if(iter_pixel == pixels_inside.end())
        return false;
    
    return true;   
}

bool Vertex::is_pixel_adjacent(int row, int col)
{
    int temp[2] = {row, col};
    auto iter_pixel = std::find(
        pixels_adjacent.begin(),pixels_adjacent.end(),temp);

    if(iter_pixel == pixels_adjacent.end())
        return false;
    
    return true;   
}
} // namespace SemanticGraph