#pragma once

#include <iostream>
#include <vector>

#include <raylib.h>
#include "go_lib.hpp"

struct Line_equation{
    float a_coe;
    float b_coe;

    Line_equation(Node a, Node b);
    void draw(int window_x, bool write_text);
    bool solve_equation(float x, float y);
};