#include "Window.h"

Window::Window() {
	vector<Point> e;
	e.push_back(Point(2,2));
	e.push_back(Point(2,102));
	e.push_back(Point(102,102));
	e.push_back(Point(102,2));

	square = Polygon(e);
}

Point Window::getMidPoint() {
	return Point(square.getMidX(), square.getMidY());
}

Point Window::getTopLeft() {
	return square.e[0];
}

Point Window::getTopRight() {
	return square.e[1];
}

Point Window::getBottomRight() {
	return square.e[2];
}

Point Window::getBottomLeft() {
	return square.e[3];
}

int Window::computeEndpoint(Point P) {
	int result = INSIDE;
 
	if (P.x < getTopLeft().x) {
		result = LEFT;
	}
	else if (P.x > getBottomRight().x)  {
		result = RIGHT;
	}

	if (P.y < getTopLeft().y) {
		result = TOP;
	}
	else if (P.y > getBottomRight().y) {
		result = BOTTOM;
	}
 
	return result;
}