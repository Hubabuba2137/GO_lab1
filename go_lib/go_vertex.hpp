#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    struct Vertex{
        std::vector<Node> vertices;
        std::vector<Segment> edges;
    
        Vertex(std::vector<Node> nodes);
        Vertex();
        void create_edges();
        void draw();
        void add_vertex(Node node);
        
        float area();
    };
}