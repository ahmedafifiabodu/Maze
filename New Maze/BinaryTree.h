#pragma once
#include "Grid.h"

class BinaryTree {
public:
	static Grid on(Grid& grid) {
		grid.eachCell([&](Cell& cell) {
			std::vector<Cell*> neighbors;
			if (cell.north) neighbors.push_back(cell.north);
			if (cell.east) neighbors.push_back(cell.east);

			if (!neighbors.empty()) {
				int index = rand() % neighbors.size();
				Cell* neighbor = neighbors[index];

				cell.link(neighbor);
			}
			});

		return grid;
	}
};
