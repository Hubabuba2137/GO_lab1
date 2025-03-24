#include <iostream>
#include <raylib.h>
#include <chrono>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);
    
    //tylko raz żeby stworzyć plik z tymi node-ami
    go::create_nodes(10000, "D:/Code/Uczelnia/S4/GO/GO_lab01", "test.txt");
    
    std::vector<go::Node> nodes = go::read_nodes("test.txt");

    //creating shape
    std::vector<go::Node> vert;
    vert.push_back((Vector2){100,100});
    vert.push_back((Vector2){100,150});
    vert.push_back((Vector2){400,500});
    vert.push_back((Vector2){300,600});
    vert.push_back((Vector2){450,700});
    vert.push_back((Vector2){600,200});
    vert.push_back((Vector2){300,300});

    go::Vertex mesh(vert);

    //basic approach time
    int n=0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(go::Node it: nodes){
        if(go::is_node_inside(mesh, it)){
            ++n;
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Basic approach time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout<<"Number of nodes inside shape = "<<n<<"\n";

    //advance approach time

    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);
            for(go::Node it: nodes){
                it.draw();
            }
            mesh.draw();
        EndDrawing();
    }

    CloseWindow();
}