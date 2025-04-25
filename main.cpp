#include <raylib.h>
#include <vector>
#include <iostream>
#include <algorithm>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;


float deg_to_rad(float angle){
    return (angle*2*3.1415) / 360;
}

float dist(go::Node a, go::Node b){
    return sqrt(pow(a.pos.x-b.pos.x,2)+pow(a.pos.y-b.pos.y,2));
}

std::vector<go::Node> create_candidates(go::Node node_1, go::Node node_2) {
    std::vector<go::Node> nodes;
    
    float mid_x = (node_1.pos.x + node_2.pos.x) / 2.0f;
    float mid_y = (node_1.pos.y + node_2.pos.y) / 2.0f;
    
    float dx = node_2.pos.x - node_1.pos.x;
    float dy = node_2.pos.y - node_1.pos.y;
    float base_length = sqrt(dx * dx + dy * dy);
    
    float h = (sqrt(3.0f) / 2.0f) * base_length;
    
    float ux = (dy / base_length)/1.5;
    float uy = (dx / base_length)/1.5;
    
    go::Node candidate1(mid_x + ux * h, mid_y + uy * h);
    go::Node candidate2(mid_x - ux * h, mid_y - uy * h);
    
    float cross = dx * (candidate1.pos.y - node_1.pos.y) - dy * (candidate1.pos.x - node_1.pos.x);
    if (cross < 0) {
        nodes.push_back(candidate2); 
    } else {
        nodes.push_back(candidate1);
    }
    
    return nodes;
}

bool isValidTriangle(go::Node a, go::Node b, go::Node c, std::vector<go::Node>& polyNodes){
    float eps = dist(a, b)/2;
    
    if(dist(a, c) - dist(b, c) >= eps){
        return false;
    }
    
    float minDistance = dist(a, b)/1.5;

    for(auto &node : polyNodes){
        if((node.pos.x == a.pos.x && node.pos.y == a.pos.y) || (node.pos.x == b.pos.x && node.pos.y == b.pos.y))
        {
            continue;
        }
        if(dist(node, c) < minDistance){
            return false;
        }
    }
    
    return true;
}


std::vector<go::Triangle> advancing_front(std::vector<go::Node>& polyNodes){
    std::vector<go::Triangle> triangles;
    std::vector<go::Node> temp_nodes = polyNodes;
    
    for(int i = 0; i < temp_nodes.size(); i++){
        std::vector<go::Node> cnd = create_candidates(temp_nodes[i], temp_nodes[(i + 1) % temp_nodes.size()]);
        bool selected = false;
        go::Node A = temp_nodes[i];
        go::Node B = temp_nodes[(i + 1) % temp_nodes.size()];
        float edge_dx = B.pos.x - A.pos.x;
        float edge_dy = B.pos.y - A.pos.y;

        for (auto &candidate : cnd) {
            if (isValidTriangle(A, B, candidate, polyNodes)) {
                float cross = edge_dx * (candidate.pos.y - A.pos.y) - edge_dy * (candidate.pos.x - A.pos.x);
                if (cross > 0) {
                    triangles.push_back(go::Triangle(A, B, candidate));
                    selected = true;
                    break;
                }
            }
            else{
                go::Node C = temp_nodes[(i + 2) % temp_nodes.size()];
                triangles.push_back(go::Triangle(A, B, C));
                selected = true;
                break;
                
            }
        }
        
        if (!selected) {
            for (auto &candidate : cnd) {
                if (isValidTriangle(A, B, candidate, polyNodes)) {
                    triangles.push_back(go::Triangle(A, B, candidate));
                    break;
                }
            }
        }
    }

    return triangles;
}

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);
    std::vector<go::Node> nodes;
    nodes.push_back(go::Node(100, 100));
    nodes.push_back(go::Node(150, 100));
    nodes.push_back(go::Node(200, 100));
    nodes.push_back(go::Node(250, 100));
    nodes.push_back(go::Node(300, 100));
    nodes.push_back(go::Node(350, 100));
    nodes.push_back(go::Node(400, 100));

    nodes.push_back(go::Node(400, 150));
    nodes.push_back(go::Node(400, 200));
    nodes.push_back(go::Node(400, 250));
    nodes.push_back(go::Node(400, 300));
    nodes.push_back(go::Node(400, 350));
    nodes.push_back(go::Node(400, 400));

    nodes.push_back(go::Node(350, 400));
    nodes.push_back(go::Node(300, 400));
    nodes.push_back(go::Node(250, 400));
    nodes.push_back(go::Node(200, 400));
    nodes.push_back(go::Node(150, 400));
    nodes.push_back(go::Node(100, 400));

    nodes.push_back(go::Node(100, 350));
    nodes.push_back(go::Node(100, 300));
    nodes.push_back(go::Node(100, 250));
    nodes.push_back(go::Node(100, 200));
    nodes.push_back(go::Node(100, 150));

    go::Vertex vert(nodes);
    auto triangles = advancing_front(nodes);

    while (WindowShouldClose() == false){

        BeginDrawing();
            ClearBackground(BLACK);
            vert.draw();
            
            for(auto it: triangles){
                it.draw();
            }

        EndDrawing();
    }

    CloseWindow();
}