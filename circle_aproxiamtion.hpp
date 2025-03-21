#pragma once

#include <iostream>
#include <vector>

#include <raylib.h>
#include "go_lib.hpp"

float deg_to_rad(float angle);
std::vector<Node> circle_aproximation(Node center, float radius, int n_points);
Vertex circle_create(Node center, float radius, int n_points);