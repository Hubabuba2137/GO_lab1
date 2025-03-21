#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include "go_lib.hpp"
#include "go_node.hpp"
#include "go_line.hpp"
#include "go_segment.hpp"
#include "go_vertex.hpp"

namespace go{
    bool is_on_segment(Node node, Segment seg){
    
        if(node.pos.x < std::min(seg.tab[0].pos.x, seg.tab[1].pos.x) || node.pos.x > std::max(seg.tab[0].pos.x, seg.tab[1].pos.x)){
            return false;
        }
    
        if(node.pos.y < std::min(seg.tab[0].pos.y, seg.tab[1].pos.y) || node.pos.y > std::max(seg.tab[0].pos.y, seg.tab[1].pos.y)){
            return false;
        }
    
        return true;
    }
    
    bool is_on_line(Node node, Line line){
        return line.solve_equation(node.pos.x, node.pos.y);
    }
    
    bool is_on_right_of_line(Node node, Line line) {
        float dx = line.end.x - line.start.x;
        float dy = line.end.y - line.start.y;
        float rx = node.pos.x - line.start.x;
        float ry = node.pos.y - line.start.y;
        
        float cross = dx * ry - dy * rx;
        
        return cross < 0;
    }
    
    Node flip_node_around_line(Node node, Line line){
        float x_s, y_s;
    
        if(line.start.x == line.end.x){
            x_s = line.start.x;
            y_s = node.pos.y;
        }
    
        else if(fabs(line.a_coe) < 1e-6){  // a_coe ~ 0
            x_s = node.pos.x;
            y_s = line.b_coe;
        }
    
        else{
            float m = line.a_coe;
            float c = line.b_coe;
            x_s = (node.pos.x + m * (node.pos.y - c)) / (1 + m * m);
            y_s = (m * node.pos.x + m * m * node.pos.y + c) / (1 + m * m);
        }
    
        float x_prim = 2 * x_s - node.pos.x;
        float y_prim = 2 * y_s - node.pos.y;
    
        return Node(x_prim, y_prim);
    }
    
    Node flip_node_around_segment(Node node, Segment seg){
        Line temp(seg.tab[0], seg.tab[1]);
    
        return flip_node_around_line(node, temp);
    }
}