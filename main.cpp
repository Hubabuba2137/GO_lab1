#include <iostream>
#include <raylib.h>
#include <chrono>

#include <algorithm>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);
    
    go::create_nodes(20, "D:/Code/Uczelnia/S4/GO/GO_lab01", "test.txt");
    std::vector<go::Node> nodes = go::read_nodes("test.txt");

    std::vector<go::Node> hull = go::convex_hull(nodes);
    go::Vertex hullver(hull);

    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);

            for(go::Node it:nodes){
                it.draw();
            }

            hullver.draw();

        EndDrawing();
    }

    CloseWindow();
}