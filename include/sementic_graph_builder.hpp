#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "sementic_graph_vertex.hpp"
#include "sementic_graph_graph.hpp"

namespace SemanticGraph{
class Builder
{
private:
    int num_pixels;

    bool** mat_adjacency;
    int** mat_id_vertex;

    bool** mat_scanned;
    int num_scanned;

    std::vector<int*> queue_current;
    std::vector<int*> queue_next;

    int id_vertex_current;
    Vertex* vertex_current_ptr;

    Graph* semantic_graph;


public:
    Builder();
    ~Builder();

};

Builder::Builder()
{
}


Builder::~Builder()
{
}

} // namespace SemanticGraph