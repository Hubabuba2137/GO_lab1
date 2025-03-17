#include <iostream>
#include <sstream>
#include <raylib.h>
#include <vector>

#include <fstream>

#include "go_lib.hpp"
#include "file_reading.hpp"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    string file_name = "input.txt";
    vector<Node> nodes = read_nodes(file_name);
    vector<string> vertex_info = load_vertex_info(file_name);

    vector<Vertex> shapes = load_vertexes_from_file(nodes, vertex_info);

    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);
            for(Vertex shape: shapes){
                shape.draw();
            }
        EndDrawing();
    }

    CloseWindow();
}