#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>
#include "assets.h"

using namespace std;

FrameBuffer FB;
bool quit = false;
vector<Polygon> map;
Window window;
int key;

int kbhit(void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if(ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

Polygon matrixToPolygon(int object[][2], int col) {
	vector<Point> points;
	points.clear();
	for(int i=0;i<col;i++) {
		points.push_back(Point(object[i][0],object[i][1]));
	}
	return Polygon(points);
}

Polygon p_sumatra = matrixToPolygon(sumatra,sizeof(sumatra)/sizeof(*sumatra));
Polygon p_kalimantan = matrixToPolygon(kalimantan,sizeof(kalimantan)/sizeof(*kalimantan));

void drawMap() {
	FB.drawPolygon(p_sumatra,255,255,0,0);
	FB.drawPolygon(p_kalimantan,255,255,0,0);
}

int main() {
	map.push_back(p_sumatra);
	map.push_back(p_kalimantan);

	system("clear");

	FB.drawLine(Point(0,0), Point(0,400), 255, 255, 0,0);
	FB.drawLine(Point(0,0), Point(599,0), 255, 255, 0,0);
	FB.drawLine(Point(599,0), Point(599,400), 255, 255, 0,0);
	FB.drawLine(Point(0,400), Point(599,400), 255, 255, 0,0);

	drawMap();

	while(!quit){
		if(kbhit()){
			key=getchar();
			//PANGGIL FUNGSI UNTUK REDRAW MOVEMENT
		}
		else {
			FB.drawWindow(window,0,250,250,0);
		}
	}

	system("clear");

	return 0;
}