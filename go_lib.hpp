#pragma once
#include <raylib.h>
#include <vector>

#include "go_lib/go_node.hpp"
#include "go_lib/go_line.hpp"
#include "go_lib/go_segment.hpp"
#include "go_lib/go_vertex.hpp"

#include "go_lib/circle_aproxiamtion.hpp"

namespace go{
    bool is_on_segment(Node node, Segment seg);
    bool is_on_line(Node node, Line line);
    bool is_on_right_of_line(Node node, Line line);

    Node flip_node_around_line(Node node, Line line);
    Node flip_node_around_segment(Node node, Segment seg);
}