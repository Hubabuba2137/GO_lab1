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
    bool line_segment_intersection(Line line, Segment seg);
    bool is_on_right_of_line(Node node, Line line);

    Node flip_node_around_line(Node node, Line line);
    Node flip_node_around_segment(Node node, Segment seg);
    float angle(const Segment &seg1, const Segment &seg2);
    bool is_node_inside(Vertex vert, Node node);
    bool is_node_inside_trian(Vertex vert, Node node);
}