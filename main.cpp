#include <iostream>
#include <raylib.h>
#include <chrono>

#include <fstream>
#include <sstream>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;



int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    

    while (WindowShouldClose() == false){

        
        BeginDrawing();
            ClearBackground(BLACK);
            
        EndDrawing();
    }

    CloseWindow();
}