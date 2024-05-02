#pragma once
#include "BaseMaze.h"

class RectangularMaze : public BaseMaze
{
	int width;
	int height;

	int VertexIndex(int row, int column);
	virtual std::tuple<double, double, double, double> GetCoordinateBounds() const;

public:

	RectangularMaze(int width, int height);

	// Create the outlines of the maze.
	// It will be all closed cells
	virtual void InitialiseGraph();
};
