#include <iostream>
#include <sstream>
#include <raylib.h>
#include <vector>

#include <fstream>

#include "go_lib.hpp"
#include "file_reading.hpp"
#include "line_eq.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    Node a(400, 200);
    Node b(600, 600);

    Line line(a,b);

    Node c(500, 700);
    Node d(100, 500);

    Segment seg(c,d);
    std::cout<<is_on_right_of_line(c, line)<<"\n";
    std::cout<<is_on_right_of_line(d, line)<<"\n";

    Node e(300,400);
    Node f = flip_node_around_line(e, line);
    Node g = flip_node_around_segment(e, seg);

    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);
            line.draw(SCREEN_WIDTH, true);
            seg.draw();
            e.draw();
            f.draw();
            g.draw();
        EndDrawing();
    }

    CloseWindow();
}