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
    //go::create_nodes(10000, "D:/Code/Uczelnia/S4/GO/GO_lab01", "test.txt");
    
    std::vector<go::Node> nodes = go::read_nodes("test.txt");

    //creating shape
    go::Node c(300, 400);
    go::Vertex shape = go::circle_create(c, 100, 5);
    int n=0;
    //basic approach time
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(go::Node it: nodes){
        if(go::is_node_inside(shape, it)){
            ++n;
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "basic approach time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
    std::cout<<"Number of nodes inside shape = "<<n<<"\n";
    
    //advance approach time
    n=0;
    std::chrono::steady_clock::time_point begin_2 = std::chrono::steady_clock::now();
    for(go::Node it: nodes){
        std::vector<float> bounds = shape.get_bounds(); //min_x, max_x, min_y, max_y
        if(it.pos.x >= bounds[0] || it.pos.y <= bounds[1], it.pos.y >= bounds[2], it.pos.y <= bounds[3]){
            if(go::is_node_inside(shape, it)){
                ++n;
            }
        }
    }
    std::chrono::steady_clock::time_point end_2 = std::chrono::steady_clock::now();

    std::cout << "Improved basic approach time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end_2 - begin_2).count() << "[ms]" << std::endl;
    std::cout<<"Number of nodes inside shape = "<<n<<"\n";
    
    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);
            
            for(go::Node it: nodes){
                it.draw();
            }
            shape.draw();
        EndDrawing();
    }

    CloseWindow();
}