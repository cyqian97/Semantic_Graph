#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class SementicGraphVertex
{
private:
    std::vector<int*> pixels_inside;
    std::vector<int*> pixels_adjacent;

public:
    const int id_node = -1;
    const int label_semantic = -1;

    SementicGraphVertex();
    SementicGraphVertex(int _id_node, int _label_semantic);
    ~SementicGraphVertex();

    void add_pixel_inside(int x, int y);
    void add_pixel_adjacent(int x, int y);

    bool is_pixel_inside(int x, int y);
    bool is_pixel_adjacent(int x, int y);

    int get_id_node(){return id_node;}
    int get_label_semantic(){return label_semantic;}
    std::vector<int*> get_pixels_inside(){return pixels_inside;}
    std::vector<int*> get_pixels_adjacent(){return pixels_adjacent;}
};

SementicGraphVertex::SementicGraphVertex()
{
}

SementicGraphVertex::SementicGraphVertex(int _id_node, int _label_semantic):
    id_node(_id_node), label_semantic(_label_semantic)
{
}

SementicGraphVertex::~SementicGraphVertex()
{
}

void SementicGraphVertex::add_pixel_inside(int x, int y)
{
    int temp[2] = {x,y};
    pixels_inside.push_back(temp);
}

void SementicGraphVertex::add_pixel_adjacent(int x, int y)
{
    int temp[2] = {x,y};
    pixels_adjacent.push_back(temp);
}

bool SementicGraphVertex::is_pixel_inside(int x, int y)
{
    int temp[2] = {x,y};
    auto iter_pixel = std::find(
        pixels_inside.begin(),pixels_inside.end(),temp);

    if(iter_pixel == pixels_inside.end())
        return false;
    
    return true;   
}

bool SementicGraphVertex::is_pixel_adjacent(int x, int y)
{
    int temp[2] = {x,y};
    auto iter_pixel = std::find(
        pixels_adjacent.begin(),pixels_adjacent.end(),temp);

    if(iter_pixel == pixels_adjacent.end())
        return false;
    
    return true;   
}