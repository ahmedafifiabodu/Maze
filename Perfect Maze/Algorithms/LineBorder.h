#pragma once
#include <tuple>
#include <string>
#include <SFML\Graphics.hpp>
#include "CellBorder.h"

class LineBorder : public CellBorder
{
protected:
	double x1, y1, x2, y2;

public:
	LineBorder(double x1, double y1, double x2, double y2);
	LineBorder(std::tuple<double, double, double, double> xy);
	virtual std::string SVGPrint(const std::string& color) const;
	virtual void Draw(sf::RenderWindow& window, sf::Color& color) const;

	double getX1() const { return x1; }
	double getY1() const { return y1; }
	double getX2() const { return x2; }
	double getY2() const { return y2; }
};
