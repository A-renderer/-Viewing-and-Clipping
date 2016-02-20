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


View view;
Polygon map_border = matrixToPolygon(border,sizeof(border)/sizeof(*border));
Polygon p_sumatra = matrixToPolygon(sumatra,sizeof(sumatra)/sizeof(*sumatra));
Polygon p_kalimantan = matrixToPolygon(kalimantan,sizeof(kalimantan)/sizeof(*kalimantan));


void drawMap() {
	FB.drawPolygon(map_border,0, 255, 255,0);
	FB.drawPolygon(p_sumatra,0,255,255,0);
	FB.drawPolygon(p_kalimantan,0,255,255,0);
}

void redraw() { //untuk redraw view
	vector<Polygon> temp;
	for(int i=0;i<map.size();i++) {
		int j=0;
		bool found = false;
		while(j<map[i].e.size() && !found) {
			if(not(map[i].e[j].x<window.getTopLeft().x || map[i].e[j].y<window.getTopLeft().y 
				|| map[i].e[j].y>window.getBottomRight().y || map[i].e[j].x>window.getBottomRight().x)) {
				found = true;
				temp.push_back(map[i]);
			}
			j++;
		}
	}

	if(!window.lines.empty()) {
		//FB.cleararea(view.P1.x,view.P1.y,view.P2.x,view.P2.y);
	}

	if(!temp.empty()) {
		cout << "map ga kosong";
		window.clipAllPolygon(temp);
		if(!window.lines.empty()) {
			cout << "lines adaaaa";
			view.setViewLines(window);
			FB.drawView(view,0,250,250,0);	
			view.lines.clear();
			window.lines.clear();
			temp.clear();
		}	
	}
}

void move(int key) {
	//IF KEY LALALALAAAAAA (up, down, right, left, zoom in, zoom out)
	/*else*/if(key=='q'){
		quit=true;
		system("clear");
	}
	system("clear");

	//menggambar ulang peta
	drawMap();

	//menggambar ulang window & view
	FB.drawPolygon(view.pol,255,255,255,0);
	FB.cleararea(view.P1.x,view.P1.y,view.P2.x,view.P2.y);
	redraw();
	FB.drawWindow(window,255,255,255,0);
}

int main() {
	map.push_back(p_sumatra);
	map.push_back(p_kalimantan);

	system("clear");

	drawMap();
	FB.drawPolygon(view.pol,255,255,255,0);
	FB.drawWindow(window,255,255,255,0);
	redraw();

	/*while(!quit){
		if(kbhit()){
			key=getchar();
			//PANGGIL FUNGSI UNTUK REDRAW MOVEMENT
			//move();
		} else {
			redraw();
		}
	}*/

	//system("clear");

	return 0;
}