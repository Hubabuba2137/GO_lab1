#include <iostream>
#include <raylib.h>
#include <chrono>

#include <fstream>
#include <sstream>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;


void advancing_front(std::vector<go::Node> &nodes, int radius) {
    
}

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    std::vector<go::Node> nodes;
    /*
    nodes.push_back((Vector2){100, 100});
    nodes.push_back((Vector2){120, 140});
    nodes.push_back((Vector2){160, 200});
    nodes.push_back((Vector2){200, 400});
    nodes.push_back((Vector2){400, 400});
    nodes.push_back((Vector2){500, 300});
    nodes.push_back((Vector2){323, 150});
    */
    
    nodes.push_back((Vector2){100, 100});
    nodes.push_back((Vector2){100, 500});
    nodes.push_back((Vector2){500, 100});
    nodes.push_back((Vector2){500, 500});

    go::Vertex shape(nodes);
    std::vector<go::Node> points = shape.gen_bp(20);

    while (WindowShouldClose() == false){

        
        BeginDrawing();
            ClearBackground(BLACK);
            shape.draw();

            for(auto it: points){
                it.draw();
            }
            
        EndDrawing();
    }

    CloseWindow();
}