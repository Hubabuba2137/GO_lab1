#pragma once
#include <raylib.h>
#include <vector>


struct Node{
    Vector2 pos;
    float radius = 5.0;

    Node(float x_in, float y_in);
    Node(Vector2 pos_in);
    Node();
    void draw();
};

struct Line{
    Node tab[2];
    Vector2 start;
    Vector2 end;

    Line(Node node_start, Node node_end);

    void draw();
};

struct Vertex{
    std::vector<Node> vertices;
    std::vector<Line> edges;

    Vertex(std::vector<Node> nodes);
    Vertex();
    void create_edges();
    void draw();
    void add_vertex(Node node);

};