#include <iostream>
#include <raylib.h>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);
    
    std::vector<go::Node> vert;
    vert.push_back((Vector2){100,100});
    vert.push_back((Vector2){100,150});
    vert.push_back((Vector2){400,500});
    vert.push_back((Vector2){600,200});
    vert.push_back((Vector2){300,300});

    go::Vertex mesh(vert);

    go::Node a(200,250);
    go::Node b(500,450);
    go::Node c(450, 300);

    std::cout<<go::is_node_inside(mesh, a)<<"\n";
    std::cout<<go::is_node_inside(mesh, b)<<"\n";
    std::cout<<go::is_node_inside(mesh, c)<<"\n";

    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);
            mesh.draw();
            a.draw();
            b.draw();
            c.draw();
        EndDrawing();
    }

    CloseWindow();
}