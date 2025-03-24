#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <limits>

#include "go_vertex.hpp"
#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    Vertex::Vertex(std::vector<Node> nodes) {
        // Calculate the centroid of the nodes
        float centroidX = 0.0f, centroidY = 0.0f;
        for (const auto& node : nodes) {
            centroidX += node.pos.x;
            centroidY += node.pos.y;
        }
        centroidX /= nodes.size();
        centroidY /= nodes.size();

        // Sort nodes based on their polar angle relative to the centroid
        std::sort(nodes.begin(), nodes.end(), [centroidX, centroidY](const Node& a, const Node& b) {
            float angleA = atan2(a.pos.y - centroidY, a.pos.x - centroidX);
            float angleB = atan2(b.pos.y - centroidY, b.pos.x - centroidX);
            return angleA < angleB;
        });

        vertices = nodes;
        create_edges();
    }
    
    void Vertex::create_edges(){
        std::vector<Segment> temp;
        std::vector<Node> vert = this->vertices;
    
        
        for(int i=0; i<vertices.size();i++){
    
            if(i<vertices.size()-1){
                Segment temp_line(vert[i], vert[i+1]);
                temp.push_back(temp_line);
            }
            else{
                Segment temp_line(vert[i], vert[0]);
                temp.push_back(temp_line);
            }
        }
    
        this->edges = temp;
    }
    
    void Vertex::draw(){
        for(int i =0; i<edges.size();i++){
            edges[i].draw();
        }
    
        for(int i =0; i<vertices.size();i++){
            vertices[i].draw();
        }
    }
    
    void Vertex::add_vertex(Node node){
        vertices.push_back(node);
        create_edges();
    }

    float Vertex::area(){
        if(this->edges.size() == 3 && this->edges.size()==3){
            float p = (this->edges[0].len()+this->edges[1].len()+this->edges[2].len())/2;
            return sqrt(p*(p - this->edges[0].len())*(p - this->edges[1].len())*p - this->edges[2].len());
        }
        else{
            return 0;
        }
    }

    std::vector<float> Vertex::get_bounds() {
        float min_x = std::numeric_limits<float>::max();
        float max_x = std::numeric_limits<float>::lowest();
        float min_y = std::numeric_limits<float>::max();
        float max_y = std::numeric_limits<float>::lowest();
    
        for (const auto& node : this->vertices) { // Assuming shape.get_nodes() returns a vector of go::Node
            min_x = std::min(min_x, node.pos.x);
            max_x = std::max(max_x, node.pos.x);
            min_y = std::min(min_y, node.pos.y);
            max_y = std::max(max_y, node.pos.y);
        }
    
        return {min_x, max_x, min_y, max_y};
    }
    
}