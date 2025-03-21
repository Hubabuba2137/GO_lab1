#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include "go_lib.hpp"
#include "line_eq.hpp"

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

void Node::move(Vector2 vec){
    this->pos.x += vec.x;
    this->pos.y += vec.y;
}

Segment::Segment(Node node_start, Node node_end){
    tab[0] = node_start;
    tab[1] = node_end;
}

void Segment::draw(){
    DrawLine(tab[0].pos.x, tab[0].pos.y, tab[1].pos.x, tab[1].pos.y, WHITE);
    tab[0].draw();
    tab[1].draw();
}

void Segment::move(Vector2 vec){
    this->tab[0].pos.x+=vec.x;
    this->tab[0].pos.x+=vec.y;
    this->tab[1].pos.x+=vec.x;
    this->tab[1].pos.x+=vec.y;
}

Line::Line(Node a, Node b){
    this->start = a.pos;
    this->end = b.pos;
    
    if(a.pos.x != b.pos.x){
        this->a_coe = (a.pos.y - b.pos.y) / (a.pos.x - b.pos.x);
        this->b_coe = a.pos.y - this->a_coe * a.pos.x;
    }
    else{
        this->a_coe = 0;
        this->b_coe = a.pos.x; 
    }
}

void Line::draw(int window_x, bool write_text){
    int start_x, start_y, end_x, end_y;

    if(this->start.x != this->end.x){
        start_x = 100 - window_x;
        start_y = this->a_coe * start_x + this->b_coe; 
        end_x = window_x + 100;
        end_y = this->a_coe * end_x + this->b_coe;
    }
    else{
        start_x = this->start.x;
        start_y = 100 - window_x; //zakładamy że ekran jest kwadratem
        end_x = start_x;
        end_y = window_x + 100;
    }

    DrawLine(start_x, start_y, end_x, end_y, RED);

    if(write_text){
        if(this->start.x != this->end.x){
            int text_pos_x = this->start.x;
            int text_pos_y = this->a_coe * text_pos_x + this->b_coe + 50;
        
            std::string text = "y = " + std::to_string(this->a_coe) + "x + " + std::to_string(this->b_coe);
            DrawText(text.c_str(), text_pos_x, text_pos_y, 10, WHITE);
        }
        else{
            int text_pos_x = start_x + 20; 
            int text_pos_y = (start_y + end_y) / 2;
            std::string text = "x = " + std::to_string(start_x);
            DrawText(text.c_str(), text_pos_x, text_pos_y, 10, WHITE);
        }
    }
}

bool Line::solve_equation(float x, float y){
    if(y == this->a_coe*x + this->b_coe){
        return true;
    }
    else{
        return false;
    }
}

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