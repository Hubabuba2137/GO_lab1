#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

#include "go_vertex.hpp"
#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    Vertex::Vertex(std::vector<Node> nodes){
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

    
}