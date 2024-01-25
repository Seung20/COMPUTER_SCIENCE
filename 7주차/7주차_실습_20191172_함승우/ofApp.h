#pragma once
#include <stdlib.h>
#include "ofMain.h"
#define EPSILON 0.01

struct LineSegment {
	int x1;
	int x2;
	int y1;
	int y2;
	double slope;
	double x_coef;
	double y_coef;
	double constant;

};

struct Dot {
	int x1;
	int y1;
};

class WaterLine {

public:
	WaterLine(int num_of_line);
	~WaterLine();

	void reset();
	void update();
	void draw();
	void calculate_path(LineSegment* lineseg, int num_of_line);

	Dot* path{0};

	float uniqueColor_r, uniqueColor_g, uniqueColor_b;
	float scale;
	int hexcolor;

	int path_idx;
	int draw_complete;
	int calc_complete;
	ofPoint start_dot;
	float dot_radius;
};

class ofApp : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void resetWater();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	LineSegment* lineseg;
	Dot* dot;

	/* WaterFall-related member variables Regions */
	

	
	// flag variables
	int currentIndex;
	int num_of_line;
	int num_of_dot;
	int draw_flag;
	int load_flag;
	int waterfall_start_flag;
	int selection_dot;


	
	//string originalFileExtension;

	// Line segment and dot related variables
	/* WaterFall-related member functions */
	ofPoint target_dot;
	float water_radius;
	float dot_diameter;
	
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void initializeWaterLines(); // 2nd week portion.


	vector <WaterLine> wl;


};







