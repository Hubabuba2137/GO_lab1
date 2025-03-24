#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"

namespace go{
    struct Segment{
        Node tab[2];
    
        Segment(Node node_start, Node node_end);
        bool solve_seg(float x, float y);
        void draw();
    
        void move(Vector2);

        float len();
    };
}