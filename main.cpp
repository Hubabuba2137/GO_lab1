#include <iostream>
#include <raylib.h>
#include <chrono>

#include <fstream>
#include <sstream>

#include "go_lib.hpp"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

struct Missile{
    int x;
    int y;
    
    float radius = 5.0;

    bool detected;
    float move_x;
    float move_y;
    float detection_time;

    Missile(){
        this->x = 0;
        this->y = 0;
        this->move_x = 0;
        this->move_y = 0;
        detected = false;
    }

    Missile(int x, int y, float move_x, float move_y, float detection_time){
        this->x = x;
        this->y = y;
        this->move_x = move_x;
        this->move_y = move_y;
        this->detection_time = detection_time;
        detected = false;
    }

    void set_pos(int x, int y){
        this->x = x;
        this->y = y;
    }

    void move(int dx, int dy){
        this->x += dx;
        this->y += dy;
    }

    void detect(){
        this->detected = true;
    }

    void draw(){
        DrawCircle(x,y,radius, RED);
    }
};

std::vector<std::vector<float>> initial_stat(std::string filepath, std::string filename){
    std::vector<std::vector<float>> result;
    std::string full_path = filepath + "\\" + filename;

    float init_x, init_y;

    std::fstream plik;
    plik.open(full_path);

    if(!plik.good()){
        std::cout<<"Couldn't read a file"<<std::endl;
    }

    plik >> init_x >> init_y;

    std::vector<float> initial_pos;
    initial_pos.push_back(init_x);
    initial_pos.push_back(init_y);
    result.push_back(initial_pos);

    float vec_x, vec_y;
    
    plik >> vec_x >> vec_y;

    
    std::vector<float> move_vec;
    move_vec.push_back(vec_x/-30);
    move_vec.push_back(vec_y/30);
    result.push_back(move_vec);

    return result;
}

std::vector<Missile> missiles(std::string filepath, std::string filename){
    std::vector<Missile> temp;
    std::string full_path = filepath + "\\" + filename;

    std::fstream plik;
    plik.open(full_path);

    if(!plik.good()){
        std::cout<<"Couldn't read a file"<<std::endl;
    }

    std::string temp_line;
        
    while(getline(plik, temp_line)){
        std::istringstream iss(temp_line);
        std::string det_time,temp_x, temp_y, mov_x, mov_y;
        iss >> det_time >> temp_x >> temp_y>> mov_x>> mov_y;

        float init_time = atof(det_time.c_str());
        int pos_x = atoi(temp_x.c_str());
        int pos_y = atoi(temp_y.c_str());
        float move_x = atoi(mov_x.c_str())/50;
        float move_y = atoi(mov_y.c_str())/50;

        Missile mis(pos_x, pos_y, move_x, move_y, init_time);
        temp.push_back(mis);
    }

    return temp;
}

int main () {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "GO");
    SetTargetFPS(60);

    go::prep_file("D:/Code/Uczelnia/S4/GO/GO_lab01/lab4", "craft1_ksztalt.txt", "craft1_ksztalt_prep.txt");
    std::vector<go::Node> nodes = go::read_nodes("D:/Code/Uczelnia/S4/GO/GO_lab01/lab4/craft1_ksztalt_prep.txt");
    go::Vertex spaceShip(nodes);

    std::vector<std::vector<float>> start = initial_stat("D:/Code/Uczelnia/S4/GO/GO_lab01/lab4", "space_craft1.txt");
    spaceShip.set_pos(start[0][0], start[0][1]);

    float move_x = start[1][0];
    float move_y = start[1][1];

    std::vector<Missile> missile = missiles("D:/Code/Uczelnia/S4/GO/GO_lab01/lab4", "missiles2.txt");

    float gameTimer = 0.0f;

    while (WindowShouldClose() == false){

        float deltaTime = GetFrameTime();
        gameTimer += deltaTime;

        spaceShip.move(move_x, move_y);
        if(spaceShip.get_bounds()[0] > SCREEN_WIDTH || spaceShip.get_bounds()[2] > SCREEN_HEIGHT){
            spaceShip.set_pos(start[0][0], start[0][1]);
        }

        for(auto &mis : missile) {
            if(!mis.detected && gameTimer >= mis.detection_time) {
                mis.detect();
                std::cout<<"Missile detected at: "<<mis.x<<", "<<mis.y<<"\n";
            }

            if(mis.detected) {
                mis.x += static_cast<int>(mis.move_x);
                mis.y += static_cast<int>(mis.move_y);
            }
        }

        for(int i=0; i<missile.size();i++){

            if(go::is_node_inside(spaceShip.convex_hull_shape, go::Node(missile[i].x, missile[i].y))){
                std::cout<<"Missile hit spaceship at " << missile[i].x<<", "<< missile[i].y<<"\n";
                missile.erase(missile.begin()+i);
            }
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            
            spaceShip.draw_nodes();
            spaceShip.draw_convex_hull();

            for(auto const &mis : missile) {
                if(mis.detected){
                    DrawCircle(mis.x, mis.y, mis.radius, RED);
                }
            }
            
        EndDrawing();
    }

    CloseWindow();
}