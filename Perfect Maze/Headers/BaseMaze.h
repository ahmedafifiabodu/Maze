#pragma once
#include <tuple>
#include <string>
#include <SFML\Graphics.hpp>

#include "../Algorithms/SpanningtreeAlgorithmBase.h"
#include "../Algorithms/DepthFirstSearch.h"
#include "../Algorithms/LineBorder.h"

class BaseMaze
{
private:

	// This funtion will remove the unnecessary broders between the connected cells
	void RemoveBorders(const std::vector<std::pair<int, int>>& spanningTreeEdges);

	// This funtion is used to solve the maze
	// However, I will use it to solve the maze. Thus, generate the correct path in order to remove the walls
	void Solve(const std::vector<std::pair<int, int>>& spanningTreeEdges);

protected:

	// To get the coordination of 2 point
	virtual std::tuple<double, double, double, double> GetCoordinateBounds() const = 0;

	// The Maze is drawn in Graph !!
	//Graph edgesList;

	std::vector<std::vector<Edge>> edgesList;
	Graph solution;

	int verticesNumber;
	int startVertex;
	int endVertex;

public:

	BaseMaze(int verticesNumber = 0, int startVertex = 0, int endVertex = 1);

	// Create a Graph to represent the maze
	// It will create a grind with cells (Each cell is closed for now)
	virtual void InitialiseGraph() = 0;

	// We will use the Spanning Tree Algorithm to create the maze
	// After the Algorithm created the maze; we will adjust it onto the graph which we created before
	void GenerateMaze(SpanningtreeAlgorithmBase* algorithm);
	void PrintMazeSVG(const std::string& filename) const;
	void Draw(sf::RenderWindow& window, sf::Color& color) const;

	int getVerticesNumber() const { return verticesNumber; }
	const std::vector<std::vector<Edge>>& getEdgesList() const { return edgesList; }
};
