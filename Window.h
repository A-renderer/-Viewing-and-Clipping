#ifndef WINDOW_H
#define WINDOW_H

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 3
#define TOP 4

#include "Line.h"
#include "Polygon.h"
#include <vector>

class Window {
	public:
		Polygon square;
		vector<Line> lines;

		Window();
		Point getMidPoint();
		Point getTopLeft();
		Point getBottomRight();
};

#endif