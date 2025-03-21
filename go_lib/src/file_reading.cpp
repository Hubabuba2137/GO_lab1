#include <iostream>
#include <raylib.h>
#include <vector>
#include <fstream>
#include <sstream>

#include "go_lib.hpp"
#include "file_reading.hpp"


std::vector<go::Node> go::read_nodes(std::string filename){
    std::fstream plik;
    plik.open(filename);

    if(!plik.good()){
        std::cout<<"Couldn't read a file"<<std::endl;
    }

    std::vector<Node> nodes;
    std::string temp_line;
    
    while(getline(plik, temp_line)){
        if(temp_line != "*ELEMENTS"){
            if(temp_line != "*NODES"){
                //cout<<temp_line<<"\n";
                std::istringstream iss(temp_line);
                std::string temp_id, temp_x, temp_y;
                iss >> temp_id >> temp_x >> temp_y;

                int id = atoi(temp_id.c_str());
                float x = atoi(temp_x.c_str());
                float y = atoi(temp_y.c_str());

                if(id != 0){
                    Node temp_node((Vector2){x,y});
                    nodes.push_back(temp_node);
                }
            }
        }
        else{
            break;
        }
    }

    return nodes;
}

std::vector<std::string> go::load_vertex_info(std::string filename){
    std::vector<std::string> vertex_info;
    std::fstream plik;
    plik.open(filename);

    if(!plik.good()){
        std::cout<<"Couldn't read a file"<<std::endl;
    }

    std::string temp_line;
    
    while(temp_line!="*ELEMENTS"){
        plik>>temp_line;
    }
    while(getline(plik, temp_line)){
        vertex_info.push_back(temp_line);
    }

    return vertex_info;
}

std::vector<go::Vertex> load_vertexes_from_file(std::vector<go::Node> &nodes, std::vector<std::string> &vertex_info){
    std::vector<go::Vertex> result;

    for( std::string temp_line: vertex_info){
        std::vector<int> node_ids;
        std::vector<go::Node> temp_nodes; 

        std::istringstream iss(temp_line);
        std::string token;
        iss >> token;

        if(atoi(token.c_str()) != 0){

            while (iss >> token) {
                int id_temp = atoi(token.c_str());
                node_ids.push_back(id_temp);
            }

            for(int i = 0; i < node_ids.size(); i++){
                temp_nodes.push_back(nodes[node_ids[i]-1]);
                
                //cout<<"\t"<<node_ids[i]<<": x="<<nodes[node_ids[i]-1].pos.x;
                //cout<<" y="<<nodes[node_ids[i]-1].pos.y<<"\n";
            }

            go::Vertex temp_vertex(temp_nodes);
            result.push_back(temp_vertex);
        }
    }
    return result;
}