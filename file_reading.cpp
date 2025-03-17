#include <iostream>
#include <raylib.h>
#include <vector>
#include <fstream>
#include <sstream>

#include "go_lib.hpp"
#include "file_reading.hpp"


vector<Node> read_nodes(string filename){
    fstream plik;
    plik.open(filename);

    if(!plik.good()){
        std::cout<<"Couldn't read a file"<<std::endl;
    }

    vector<Node> nodes;
    std::string temp_line;
    
    while(getline(plik, temp_line)){
        if(temp_line != "*ELEMENTS"){
            if(temp_line != "*NODES"){
                //cout<<temp_line<<"\n";
                std::istringstream iss(temp_line);
                string temp_id, temp_x, temp_y;
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

vector<string> load_vertex_info(string filename){
    vector<string> vertex_info;
    fstream plik;
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

vector<Vertex> load_vertexes_from_file(vector<Node> &nodes, vector<string> &vertex_info){
    vector<Vertex> result;

    for(string temp_line: vertex_info){
        vector<int> node_ids;
        vector<Node> temp_nodes; 

        std::istringstream iss(temp_line);
        string token;
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

            Vertex temp_vertex(temp_nodes);
            result.push_back(temp_vertex);
        }
    }
    return result;
}