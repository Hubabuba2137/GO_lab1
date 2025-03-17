#include <iostream>
#include <vector>

#include <raylib.h>
#include "go_lib.hpp"

#include "line_eq.hpp"

Line_equation::Line_equation(Node a, Node b){
    if((a.pos.x - b.pos.x) != 0){
        this->a_coe = ((a.pos.y-b.pos.y)/(a.pos.x-b.pos.x));
        std::cout<<this->a_coe<<"\n";
        this->b_coe = a.pos.y - this->a_coe*a.pos.x;
        std::cout<<b_coe<<"\n";
    }
    else{
        this->a_coe = 0;
        this->b_coe = 0;
    }
}

void Line_equation::draw(int window_x, bool write_text){
    int start_x = 100-window_x;
    int start_y = this->a_coe * start_x + this->b_coe; 
    int end_x = window_x+100;
    int end_y = this->a_coe * end_x + this->b_coe;

    DrawLine(start_x, start_y, end_x, end_y, RED);

    if(write_text){
        int text_pos_x = (start_x + end_x) / 2;
        int text_pos_y = this->a_coe * text_pos_x + this->b_coe + 50;
        
        std::string text = "y = ";
        text += std::to_string(this->a_coe);
        text += "x + ";
        text += std::to_string(this->b_coe);

        DrawText(text.c_str(), text_pos_x, text_pos_y, 10, WHITE);
    }
}

bool Line_equation::solve_equation(float x, float y){
    if(y == this->a_coe*x + this->b_coe){
        return true;
    }
    else{
        return false;
    }
}