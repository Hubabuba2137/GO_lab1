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

    float cross(const Vector2& a, const Vector2& b, const Vector2& c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    bool is_convex(const Vector2& prev, const Vector2& curr, const Vector2& next) {
        return cross(prev, curr, next) > 0; // zakładamy CCW (counter-clockwise)
    }


    bool is_ear(const std::vector<Node>& poly, int i) {
        int prev = (i - 1 + poly.size()) % poly.size();
        int next = (i + 1) % poly.size();

        if (!is_convex(poly[prev].pos, poly[i].pos, poly[next].pos))
            return false;

        Vertex triangle({ poly[prev], poly[i], poly[next] });

        for (int j = 0; j < poly.size(); ++j) {
            if (j == prev || j == i || j == next)
                continue;
            if (is_node_inside_trian(triangle, poly[j]))
                return false;
        }

        return true;
    }

    std::vector<Vertex> ear_cut_triangulation(const Vertex& polygon) {
        std::vector<Node> verts = polygon.vertices;
        std::vector<Vertex> triangles;

        if (verts.size() < 3) {
            std::cout << "Polygon too small to triangulate\n";
            return {};
        }

        while (verts.size() > 3) {
            bool ear_found = false;

            for (int i = 0; i < verts.size(); ++i) {
                if (is_ear(verts, i)) {
                    int prev = (i - 1 + verts.size()) % verts.size();
                    int next = (i + 1) % verts.size();

                    std::vector<Node> tri = { verts[prev], verts[i], verts[next] };
                    triangles.push_back(Vertex(tri));
                    verts.erase(verts.begin() + i);
                    ear_found = true;
                    break;
                }
            }

            if (!ear_found) {
                // Wielokąt nie jest prosty lub coś poszło nie tak
                break;
            }
        }

        if (verts.size() == 3) {
            triangles.push_back(Vertex(verts));
        }

        return triangles;
    }
}