#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <raylib.h>
#include <go_lib.hpp>

using namespace std;

vector<Node> read_nodes(string filename);
vector<string> load_vertex_info(string filename);
vector<Vertex> load_vertexes_from_file(vector<Node> &nodes, vector<string> &vertex_info);
