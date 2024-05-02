#include "RectangularMaze.h"

int RectangularMaze::VertexIndex(int row, int column)
{
	return row * width + column;
}

std::tuple<double, double, double, double> RectangularMaze::GetCoordinateBounds() const
{
	return std::make_tuple(0, 0, width, height);
}

RectangularMaze::RectangularMaze(int width, int height) : BaseMaze(width* height, 0, width* height - 1)
{
	this->width = width;
	this->height = height;
}

void RectangularMaze::InitialiseGraph()
{
	BaseMaze::InitialiseGraph();

	// Insitialize the upper and lower bounderies
	for (int i = 0; i < width; ++i)
	{
		edgesList[VertexIndex(0, i)].push_back(
			{ -1, std::make_shared<LineBorder>(i, 0, i + 1, 0) });
		edgesList[VertexIndex(height - 1, i)].push_back(
			{ -1, std::make_shared<LineBorder>(i, height, i + 1, height) });
	}

	// Insitialize the right and left bounderies
	// Leaving a space for the start and exit (they are fixed)
	for (int i = 0; i < height; ++i)
	{
		if (i != 0)
			edgesList[VertexIndex(i, 0)].push_back(
				{ -1, std::make_shared<LineBorder>(0, i, 0, i + 1) });

		if (i != height - 1)
			edgesList[VertexIndex(i, 0)].push_back(
				{ -1, std::make_shared<LineBorder>(width, i, width, i + 1) });
	}

	// Add horizontally adjacent cells of a maze row by row.
	// If we would draw a grid: grid would have all vertical lines drawn.
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; ++j)
		{
			std::shared_ptr<LineBorder> ptr = std::make_shared<LineBorder>(j + 1, i, j + 1, i + 1);
			edgesList[VertexIndex(i, j)].push_back({ VertexIndex(i, j + 1), ptr });
			edgesList[VertexIndex(i, j + 1)].push_back({ VertexIndex(i, j), ptr });
		}
	}

	// Add vertically adjacent cells of a maze column by column.
	// If we would draw a grid: grid would have all horizontal lines drawn.
	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			std::shared_ptr<LineBorder> ptr = std::make_shared<LineBorder>(j, i + 1, j + 1, i + 1);
			edgesList[VertexIndex(i, j)].push_back({ VertexIndex(i + 1, j), ptr });
			edgesList[VertexIndex(i + 1, j)].push_back({ VertexIndex(i, j), ptr });
		}
	}
}