#pragma once
#include <random>
#include "GraphForSpanningTreeAlgorithm.h"

// This is a portion form the main Spanning Tree Algorithm
// I have use only the part wihch generate the maze
// However, the part which handle the cell design is in " .h"

class SpanningtreeAlgorithmBase
{
protected:
	std::vector<std::pair<int, int>> spanningTree;
	std::random_device randomDevice;
	std::mt19937 generator;

public:
	SpanningtreeAlgorithmBase()
	{
		// Using the Random Class to generate the graph.
		generator = std::mt19937(randomDevice());
	}

	/**
	 * \brief Generates entire maze spanning tree by randomly selecting next cell and moving using DFS.
	 * \param verticesNumber Number of vertices in the graph or cells in the maze.
	 * \param adjacencylist Graph representation
	 * \return A list of pairs of connected maze cells (without walls).
	 */

	virtual std::vector<std::pair<int, int>> SpanningTree(int verticesNumber, const Graph& adjacencylist) = 0;
};
