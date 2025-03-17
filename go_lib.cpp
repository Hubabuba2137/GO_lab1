#include <raylib.h>
#include <vector>
#include "go_lib.hpp"

using namespace std;


Node::Node(float x_in, float y_in){
    //pos = (Vector2){x_in, SCREEN_HEIGHT-y_in}; //normalny ukłąd współrzędnych
    pos = (Vector2){x_in, y_in};
}

Node::Node(Vector2 pos_in){
    pos = pos_in;
}

Node::Node(){
    pos = (Vector2){0,0};
}

void Node::draw(){
    DrawCircle(pos.x, pos.y, radius, GREEN);
}

Line::Line(Node node_start, Node node_end){
    tab[0] = node_start;
    tab[1] = node_end;

    start = tab[0].pos;
    end = tab[1] .pos;
}

void Line::draw(){
    DrawLine(tab[0].pos.x, tab[0].pos.y, tab[1].pos.x, tab[1].pos.y, WHITE);
}

Vertex::Vertex(std::vector<Node> nodes){
    vertices = nodes;

    create_edges();
}

Vertex::Vertex(){
    
}

void Vertex::create_edges(){
    vector<Line> temp;
    vector<Node> vert = this->vertices;

    vert.push_back(vertices[0]);
    
    for(int i=0; i<vertices.size();i++){
        Line temp_line(vert[i], vert[i+1]);
        temp.push_back(temp_line);
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