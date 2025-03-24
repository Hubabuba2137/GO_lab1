#include <raylib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include "go_lib.hpp"
#include "go_node.hpp"
#include "go_line.hpp"
#include "go_segment.hpp"
#include "go_vertex.hpp"
#include "intersect.hpp"

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

    bool line_segment_intersection(Line line, Segment seg){
        if(is_on_line(seg.tab[0], line) || is_on_line(seg.tab[1], line)){
            return true;
        }

        float d1, d2;
        if(line.start.x == line.end.x){
            d1 = seg.tab[0].pos.x - line.start.x;
            d2 = seg.tab[1].pos.x - line.start.x;
        }
        else{
            d1 = seg.tab[0].pos.y - (line.a_coe * seg.tab[0].pos.x + line.b_coe);
            d2 = seg.tab[1].pos.y - (line.a_coe * seg.tab[1].pos.x + line.b_coe);
        }

        // jeżeli < 0 to przecina linie, jeżeli > 0 to nie
        return (d1 * d2 < 0);
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
    float angle(const Segment &seg1, const Segment &seg2) {
        // Calculate direction vectors assuming `start` and `end` members in Segment.
        Vector2 v1 = { seg1.tab[1].pos.x - seg1.tab[0].pos.x, seg1.tab[1].pos.y - seg1.tab[0].pos.y };
        Vector2 v2 = { seg2.tab[1].pos.x - seg2.tab[0].pos.x, seg2.tab[1].pos.y - seg2.tab[0].pos.y };
    
        float dot = v1.x * v2.x + v1.y * v2.y;
        float len1 = sqrt(v1.x * v1.x + v1.y * v1.y);
        float len2 = sqrt(v2.x * v2.x + v2.y * v2.y);
        
        if(len1 == 0 || len2 == 0) {
            // Avoid division by zero. You can decide how to handle this case.
            return 0;
        }
    
        float angle = acos(dot / (len1 * len2));
        return angle;
    }

    bool ray_intersects_segment(Node point, Segment seg) {
        float x = point.pos.x, y = point.pos.y;
        float x1 = seg.tab[0].pos.x, y1 = seg.tab[0].pos.y;
        float x2 = seg.tab[1].pos.x, y2 = seg.tab[1].pos.y;
    
        // Check if the segment straddles the horizontal line at y
        if ((y1 > y) != (y2 > y)) {
            float intersectX = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
            return x < intersectX;
        }
        return false;
    }
    /*
    bool is_convex(Node a, Node b, Node c) {
        float v1x = b.pos.x - a.pos.x;
        float v1y = b.pos.y - a.pos.y;
        float v2x = c.pos.x - b.pos.x;
        float v2y = c.pos.y - b.pos.y;
    
        float cross = v1x * v2y - v1y * v2x;
        float epsilon = 1e-6;
        return cross > epsilon;
    }

    bool no_other_node_in_trian(Vertex trian, std::vector<Node>& vert) {
        for (Node& it : vert) {
            if (&it == &trian.vertices[0] || &it == &trian.vertices[1] || &it == &trian.vertices[2]) {
                continue;
            }
            if (is_node_inside_trian(trian, it)) {
                return false;
            }
        }
        return true;
    }

    std::vector<Vertex> ear_cut(Vertex shape) {
        std::vector<Vertex> triangles;
        std::vector<Node> vertices = shape.vertices;
    
        if (vertices.size() < 3) {
            std::cerr << "Polygon must have at least 3 vertices!" << std::endl;
            return triangles;
        }
    
        while (vertices.size() > 3) {
            bool earFound = false;
            for (int i = 0; i < vertices.size(); i++) {
                Node prev = vertices[(i - 1 + vertices.size()) % vertices.size()];
                Node curr = vertices[i];
                Node next = vertices[(i + 1) % vertices.size()];
    
                if (is_convex(prev, curr, next)) {
                    std::vector<Node> trian_nodes = {prev, curr, next};
                    Vertex trian(trian_nodes);
    
                    if (no_other_node_in_trian(trian, vertices)) {
                        triangles.push_back(trian);
                        vertices.erase(vertices.begin() + i);
                        earFound = true;
                        break;
                    }
                }
            }
            if (!earFound) {
                std::cerr << "Failed to find an ear. Check if the polygon is valid!" << std::endl;
                return triangles;
            }
        }
    
        std::vector<Node> last_trian = {vertices[0], vertices[1], vertices[2]};
        Vertex last(last_trian);
        triangles.push_back(last);
    
        return triangles;
    }*/
}