#include <array>
#include <vector>
#include <string>
#include <iostream>

class sementic_graph_vertex
{
private:
    int id_node = -1;
    int label_semantic = -1;
    std::vector<std::array<int,2>> pixels_inside;
    std::vector<std::array<int,2>> pixels_adjacent;

public:
    sementic_graph_vertex();
    sementic_graph_vertex(int _id_node, int _label_semantic);
    ~sementic_graph_vertex();

    int get_id_node(){return id_node;}

    int get_label_semantic(){return label_semantic;}
};

sementic_graph_vertex::sementic_graph_vertex()
{
}

sementic_graph_vertex::sementic_graph_vertex(int _id_node, int _label_semantic)
{
    id_node = _id_node;
    label_semantic = _label_semantic;
}

sementic_graph_vertex::~sementic_graph_vertex()
{
}
