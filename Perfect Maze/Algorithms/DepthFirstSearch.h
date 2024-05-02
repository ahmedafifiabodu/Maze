#pragma once
#include "SpanningtreeAlgorithmBase.h"

class DepthFirstSearch : public SpanningtreeAlgorithmBase
{
	std::vector<int> parent;
	void InternalDFS(int vertex, const Graph& adjacencyList);

public:
	/**
	 * \brief Generates entire maze spanning tree by randomly selecting next cell and moving using DFS.
	 *		  The interesting fact is that generation starts from the random vertex of a Graph (not just start of a maze).
	 * \param verticesNumber Number of vertices in the graph or cells in the maze.
	 * \param adjacencyList Graph representation
	 * \return A list of pairs of connected maze cells (without walls).
	 */
	std::vector<std::pair<int, int>> SpanningTree(int verticesNumber, const Graph& adjacencyList);

	/**
	 * \brief Finds a path from ENTRY start cell of a maze to the EXIT cell by using DFS.
	 * \param verticesNumber Number of vertices in the graph or cells in the maze.
	 * \param adjacencyList Graph representation
	 * \param startVertex a number of start vertex of a Graph mapped to the start cell of a maze.
	 * \return a path as a numbers of cells/vertexes.
	 */
	std::vector<int> Solve(int verticesNumber, const Graph& adjacencyList, int startVertex);
};
