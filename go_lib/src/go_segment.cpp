#include <raylib.h>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

#include "go_node.hpp"
#include "go_segment.hpp"

namespace go{
    Segment::Segment(Node node_start, Node node_end){
        tab[0] = node_start;
        tab[1] = node_end;
    }
    
    void Segment::draw(){
        DrawLine(tab[0].pos.x, tab[0].pos.y, tab[1].pos.x, tab[1].pos.y, WHITE);
        tab[0].draw();
        tab[1].draw();
    }
    
    void Segment::move(Vector2 vec){
        this->tab[0].pos.x+=vec.x;
        this->tab[0].pos.y+=vec.y;
        this->tab[1].pos.x+=vec.x;
        this->tab[1].pos.y+=vec.y;
    }

    float Segment::len(){
        float dx = tab[1].pos.x - tab[0].pos.x;
        float dy = tab[1].pos.y - tab[0].pos.y;
        return sqrt(dx * dx + dy * dy);
    }
}