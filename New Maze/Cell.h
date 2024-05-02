#pragma once
#include <unordered_set>

class Cell {
public:
	int row, column;
	Cell* north;
	Cell* south;
	Cell* east;
	Cell* west;

	std::unordered_set<Cell*> links;

	Cell(int row, int column) : row(row), column(column), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {}

	Cell* link(Cell* cell, bool bidi = true) {
		links.insert(cell);
		if (bidi) {
			cell->link(this, false);
		}
		return this;
	}

	Cell* unlink(Cell* cell, bool bidi = true) {
		links.erase(cell);
		if (bidi) {
			cell->unlink(this, false);
		}
		return this;
	}

	std::unordered_set<Cell*> getLinks() const {
		return links;
	}

	bool linked(Cell* cell) const {
		return links.find(cell) != links.end();
	}

	std::vector<Cell*> neighbors() const {
		std::vector<Cell*> list;
		if (north) list.push_back(north);
		if (south) list.push_back(south);
		if (east)  list.push_back(east);
		if (west)  list.push_back(west);
		return list;
	}
};