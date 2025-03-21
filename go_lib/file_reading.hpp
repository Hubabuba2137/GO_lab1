#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <raylib.h>
#include <go_lib.hpp>
#include <go_node.hpp>
#include <go_vertex.hpp>

namespace go{
    std::vector<go::Node> read_nodes(std::string filename);
    std::vector<std::string> load_vertex_info(std::string filename);
    std::vector<go::Vertex> load_vertexes_from_file(std::vector<go::Node> &nodes, std::vector<std::string> &vertex_info);
}