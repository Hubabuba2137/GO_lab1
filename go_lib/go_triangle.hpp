#pragma once
#include <raylib.h>
#include <vector>

#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    struct Triangle{
        Node points[3];
        Segment edges[3];

        Triangle(Node a, Node b, Node c);
        Triangle();

        void draw();
    };
}//namespace go