#pragma once

#include <vector>
#include "EdgeOfEachCellinTheGraph.h"

// Adjacency list of EDGES for UNORIENTED graph of the maze
// Edge Class hold the node on the 2D graph
// NOTE: There is 2 variables which hold "From->Edge" and "To->Edge"

typedef std::vector<std::vector<Edge>> Graph;
