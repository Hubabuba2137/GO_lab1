#include <iostream>
#include <raylib.h>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    go::Node a(400, 200);
    go::Node b(600, 600);

    go::Line line(a,b);

    go::Node c(500, 700);
    go::Node d(100, 500);

    go::Segment seg(c,d);
    std::cout<<go::is_on_right_of_line(c, line)<<"\n";
    std::cout<<go::is_on_right_of_line(d, line)<<"\n";

    go::Node e(300,400);
    go::Node f = flip_node_around_line(e, line);
    go::Node g = flip_node_around_segment(e, seg);
    

    go::Node center(150,150);
    
    float radius = 100;
    go::Vertex circle = go::circle_create(center, radius, 5);

    //seg.move((Vector2){200,0});

    while (WindowShouldClose() == false){
        
        BeginDrawing();
            ClearBackground(BLACK);
            line.draw(SCREEN_WIDTH, true);
            a.draw();
            b.draw();
            seg.draw();
            e.draw();
            f.draw();
            g.draw();

            DrawCircleLines(center.pos.x, center.pos.y, radius, BLUE);
            circle.draw();

        EndDrawing();
    }

    CloseWindow();
}