#include <iostream>
#include <vector>
#include <cmath>

#include "go_lib.hpp"

namespace go{
    bool is_node_inside(Vertex vert, Node node) {
        if (vert.edges.size() == 3 && vert.vertices.size() == 3) {
            return is_node_inside_trian(vert, node);
        } else {
            int intersections = 0;
            for (const Segment &seg : vert.edges) {
                if (ray_intersects_segment(node, seg)) {
                    ++intersections;
                }
            }
            if(intersections%2 == 0){
                return false;
            }
            else{
                return true;
            }
        }
    }

    bool is_node_inside_trian(Vertex vert, Node node) {
        Node a = vert.vertices[0];
        Node b = vert.vertices[1];
        Node c = vert.vertices[2];
    
        Segment a_b(a, b);
        Segment b_c(b, c);
        Segment c_a(c, a);
    
        if (is_on_segment(node, a_b) || is_on_segment(node, b_c) || is_on_segment(node, c_a)) {
            return true;
        }
    
        Segment a_n(a, node);
        Segment b_n(b, node);
        Segment c_n(c, node);
    
        float alfa = angle(a_n, b_n);
        float beta = angle(b_n, c_n);
        float sigma = angle(c_n, a_n);
    
        float epsilon = 0.01f;
    
        if (fabs(alfa + beta + sigma - 2 * PI) < epsilon) {
            return true;
        } else {
            return false;
        }
    }
}