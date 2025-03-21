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

    void move(Vector2 vec);
};

struct Segment{
    Node tab[2];

    Segment(Node node_start, Node node_end);
    bool solve_seg(float x, float y);
    void draw();

    void move(Vector2);
};

struct Line{
    float a_coe;
    float b_coe;

    Vector2 start;
    Vector2 end;

    Line(Node a, Node b);
    void draw(int window_x, bool write_text);
    bool solve_equation(float x, float y);
};

struct Vertex{
    std::vector<Node> vertices;
    std::vector<Segment> edges;

    Vertex(std::vector<Node> nodes);
    Vertex();
    void create_edges();
    void draw();
    void add_vertex(Node node);

};

bool is_on_segment(Node node, Segment seg);
bool is_on_line(Node node, Line line);
bool is_on_right_of_line(Node node, Line line);

Node flip_node_around_line(Node node, Line line);
Node flip_node_around_segment(Node node, Segment seg);

float deg_to_rad(float angle);
std::vector<Node> circle_aproximation(Node center, float radius, int n_points);
Vertex circle_create(Node center, float radius, int n_points);