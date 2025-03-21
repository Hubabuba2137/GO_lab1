#include <iostream>
#include <vector>
#include <cmath>

#include <raylib.h>
#include "go_lib.hpp"

float deg_to_rad(float angle){
    return (angle*2*3.1415) / 360;
}

std::vector<Node> circle_aproximation(Node center, float radius, int n_points){
    std::vector<Node> circle_points;
    float step = 360/n_points;
    float angle=0;
    float clock_hand_x=0;
    float clock_hand_y=0;

    for(int i=0; i<n_points;i++){
        clock_hand_x = cos(deg_to_rad(angle))* radius;
        clock_hand_y = sin(deg_to_rad(angle))* radius;
        //std::cout<<"("<<clock_hand_x<<", "<<clock_hand_y<<")\n";

        Node temp(clock_hand_x+center.pos.x, clock_hand_y+center.pos.y);
        circle_points.push_back(temp);
        angle += step;
    }

    return circle_points;
}

Vertex circle_create(Node center, float radius, int n_points){
    return Vertex(circle_aproximation(center, radius, n_points));
}