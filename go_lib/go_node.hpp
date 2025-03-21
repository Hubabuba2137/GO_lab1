#pragma once
#include <raylib.h>
#include <vector>

namespace go{
    struct Node{
        Vector2 pos;
        float radius = 5.0;

        Node(float x_in, float y_in);
        Node(Vector2 pos_in);
        Node();
        void draw();

        void move(Vector2 vec);
    };
}