#include "Window.h"

Window::Window() {
	vector<Point> e;
	e.push_back(Point(2,2));
	e.push_back(Point(2,152));
	e.push_back(Point(152,152));
	e.push_back(Point(152,2));

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
		result = result|LEFT;
	}
	else if (P.x > getBottomRight().x)  {
		result = result|RIGHT;
	}

	if (P.y < getTopLeft().y) {
		result = result|BOTTOM;
	}
	else if (P.y > getBottomRight().y) {
		result = result|TOP;
	}
 
	return result;
}

void Window::lineClipping(Line line) {
	int endPoint1 = computeEndpoint(line.src);
	int endPoint2 = computeEndpoint(line.dest);
	bool valid = false;

	while (true) {
		if (!(endPoint1|endPoint2)) { //kedua titik line didalam (0000)
			valid = true;
			break;
		} else if (endPoint1 & endPoint2) { //dua2 diluar
			break;
		} else {
			float x, y;
			int point = endPoint1 ? endPoint1 : endPoint2;
			if (point & TOP) {
				x = line.src.x + (line.dest.x - line.src.x) * (getBottomRight().y - line.src.y) / (line.dest.y - line.src.y);
				y = getBottomRight().y;
			} else if (point & BOTTOM) {
				x = line.src.x + (line.dest.x - line.src.x) * (getTopLeft().y - line.src.y) / (line.dest.y - line.src.y);
				y = getTopLeft().y;
			} else if (point & RIGHT) {
				y = line.src.y + (line.dest.y - line.src.y) * (getBottomRight().x - line.src.x) / (line.dest.x - line.src.x);
				x = getBottomRight().x;
			} else if (point & LEFT) {
				y = line.src.y + (line.dest.y - line.src.y) * (getTopLeft().x - line.src.x) / (line.dest.x - line.src.x);
				x = getTopLeft().x;
			}

			if (point == endPoint1) {
				line.src.x = x;
				line.src.y = y;
				endPoint1 = computeEndpoint(line.src);
			} else {
				line.dest.x = x;
				line.dest.y = y;
				endPoint2 = computeEndpoint(line.dest);
			}
		}

	}
	if (valid) {
		lines.push_back(line);
	}
}

void Window::polygonClipping(Polygon P) {
	for(int j=0; j<P.e.size()-1; j++) {
		lineClipping(Line(Point(P.e[j].x,P.e[j].y),Point(P.e[j+1].x,P.e[j+1].y)));
	}
	lineClipping(Line(Point(P.e[P.e.size()-1].x,P.e[P.e.size()-1].y),Point(P.e[0].x,P.e[0].y)));
}

void Window::clipAllPolygon(vector<Polygon> pols) {
	int c = 1;
	if(!pols.empty()) {
		for(int i=0; i<pols.size(); i++) {
			polygonClipping(pols[i]);
		}
	}
}