#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second

    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255, 255, 255);
    ofSetLineWidth(4);

    currentIndex = 0;
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
    selection_dot = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(127, 23, 31);  // Set the drawing color to brown

    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);


    ofSetLineWidth(5);
    if (draw_flag) {
        int i;
        for (i = 0; i < num_of_line; i++) {
            ofDrawLine(lineseg[i].x1, lineseg[i].y1, lineseg[i].x2, lineseg[i].y2);
        }
        for (i = 0; i < num_of_dot; i++) {
            if (selection_dot == i)
                ofSetColor(255, 0, 0);
            else
                ofSetColor(0);

            ofDrawCircle(dot[i].x1, dot[i].y1, dot_diameter / 2);
        }



        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */



         // 2nd week portion.
        ofSetLineWidth(2);
        if (waterfall_start_flag) {
            for (unsigned int i = 0; i < wl.size(); i++) {
                if (wl[i].path == NULL) continue;
                if (wl[i].calc_complete == 0)
                    wl[i].calculate_path(lineseg, num_of_line);
                wl[i].draw();
            }

        }
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
    }
    if (key == 'q') {
        // Reset flags
        draw_flag = 0;

        // Free the dynamically allocated memory exits.
        if (lineseg != NULL) {
            free(lineseg);
            lineseg = NULL;
        }

        cout << "Memory for line segement has been freed." << endl;

        if (dot != NULL) {
            free(dot);
            dot = NULL;
        }

        cout << "Memory for dot has been freed." << endl;

        _Exit(0);
    }
    if (key == 'd') {
        if (!load_flag) return;

        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
        draw_flag = 1;
        target_dot.x = dot[selection_dot].x1;
        target_dot.y = dot[selection_dot].y1;

        /* draw();*/

    }
    if (key == 's') {
        if (load_flag) {
            resetWater();
            for (unsigned int i = 0; i < wl.size(); i++) {
                if (wl[i].calc_complete == 0)
                    wl[i].calculate_path(lineseg, num_of_line);
            }
            if (draw_flag) {
                waterfall_start_flag = 1;
            }
        }
    }
    if (key == 'e') {
        if (draw_flag)
            waterfall_start_flag = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (key == 'l') {
        // Open the Open File Dialog
        ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt for Waterfall");

        // Check whether the user opened a file
        if (openFileResult.bSuccess) {
            ofLogVerbose("User selected a file");

            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }

    if (key == OF_KEY_RIGHT) {
        selection_dot++;
        if (selection_dot == num_of_dot)
            selection_dot = 0;

        target_dot.x = dot[selection_dot].x1;
        target_dot.y = dot[selection_dot].y1;
        cout << "Selcted Dot Coordinate is (" << target_dot.x << ", " << target_dot.y << ")" << endl;
    }
    if (key == OF_KEY_LEFT) {

        selection_dot--;
        if (selection_dot < 0)
            selection_dot = num_of_dot - 1;

        target_dot.x = dot[selection_dot].x1;
        target_dot.y = dot[selection_dot].y1;

        cout << "Selcted Dot Coordinate is (" << target_dot.x << ", " << target_dot.y << ")" << endl;
    }
}

void ofApp::resetWater() {
    for (unsigned int i = 0; i < wl.size(); i++) {
        //wl[i].start_dot.x = ofRandom(dot[selection_dot].x1-dot_diameter/2, dot[selection_dot].x1+dot_diameter/2);
        wl[i].start_dot.x = target_dot.x;
        wl[i].start_dot.y = target_dot.y;
        wl[i].reset();
    }
}




void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {
    //Path to the comma delimited file
    //string fileName = "input.txt";

    string fileName = openFileResult.getName();
    ofFile file(fileName);

    if (!file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;

    ofBuffer buffer(file);

    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;


    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
    int idx = 0;

    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;

        // Split line into strings
        vector<string> words = ofSplitString(line, " ");


        if (words.size() == 1) {
            if (input_type == 0) { // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
                if (!lineseg)
                    lineseg = (LineSegment*)malloc(sizeof(LineSegment) * num_of_line);

            }
            else { // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
                if (!dot)
                    dot = (Dot*)malloc(sizeof(Dot) * num_of_dot);
            }
        }
        else if (words.size() >= 2) {
            if (!input_type) { // Input for actual information of lines
                lineseg[idx].x1 = atoi(words[0].c_str());
                lineseg[idx].y1 = atoi(words[1].c_str());
                lineseg[idx].x2 = atoi(words[2].c_str());
                lineseg[idx].y2 = atoi(words[3].c_str());

                if (lineseg[idx].x1 < 0 || lineseg[idx].x1 > ofGetWidth()) {
                    cout << "Out-of-range x1: " << lineseg[idx].x1 << endl;
                    return;
                }
                else if (lineseg[idx].y1 < 0 || lineseg[idx].y1 > ofGetHeight()) {
                    cout << "Out-of-range: " << lineseg[idx].y1 << endl;
                    return;
                }
                else if (lineseg[idx].x2 < 0 || lineseg[idx].x2 > ofGetWidth()) {
                    cout << "Out-of-range: " << lineseg[idx].x2 << endl;
                    return;
                }
                else if (lineseg[idx].y2 < 0 || lineseg[idx].y2 > ofGetHeight()) {
                    cout << "Out-of-range: " << lineseg[idx].y2 << endl;
                    return;
                }

                double temp_constant = 0.0f;

                lineseg[idx].slope = (double)(lineseg[idx].y2 - lineseg[idx].y1) / (int)(lineseg[idx].x2 - lineseg[idx].x1);
                lineseg[idx].x_coef = (double)(lineseg[idx].y2 - lineseg[idx].y1);
                lineseg[idx].y_coef = (double)((lineseg[idx].x2 - lineseg[idx].x1) * (-1));
                temp_constant = lineseg[idx].slope * (-1) * lineseg[idx].x1 + lineseg[idx].y1;
                lineseg[idx].constant = (double)temp_constant * (lineseg[idx].x2 - lineseg[idx].x1);


                idx++;

                if (idx >= num_of_line) {
                    input_type = 1;
                    idx = 0;
                }
            }
            else { // Input for actual information of dots.
                dot[idx].x1 = atoi(words[0].c_str());
                dot[idx].y1 = atoi(words[1].c_str());
                

                idx++;
                if (idx >= num_of_dot)
                    input_type = 0;
            } // End of else if.
        } // End of for-loop (Read file line by line).   
    }
    
    int num = 50;
    wl.assign(num, WaterLine(num_of_line));
    dot_diameter = 20.0f;
    for (unsigned int i = 0; i < wl.size(); i++) {
        //wl[i].start_dot.x = ofRandom(dot[selection_dot].x1-dot_diameter/2, dot[selection_dot].x1+dot_diameter/2);
        wl[i].start_dot.x = dot[selection_dot].x1;
        wl[i].start_dot.y = dot[selection_dot].y1;
        wl[i].dot_radius = dot_diameter / 2;
    }
    resetWater();

}

void ofApp::initializeWaterLines() {
    ;
}


void WaterLine::reset() {
    //the unique val allows us to set color for each water line.
    uniqueColor_r = ofRandom(0, 100);
    uniqueColor_g = ofRandom(0, 100);
    uniqueColor_b = ofRandom(185, 255);

    calc_complete = 0;
    draw_complete = 0;

    path_idx = 0;
}

void WaterLine::draw() {
    if (calc_complete) {
        ofSetLineWidth(5);

        ofSetColor(uniqueColor_r, uniqueColor_g, uniqueColor_b);
        for (int i = 0; i < path_idx - 1; i++) {
            uniqueColor_r = ofRandom(0, 100);
            uniqueColor_g = ofRandom(0, 100);
            uniqueColor_b = ofRandom(185, 255);
            ofSetColor(uniqueColor_r, uniqueColor_g, uniqueColor_b);
            ofDrawLine(path[i].x1 - 1, path[i].y1 - 1, path[i + 1].x1 + 1, path[i + 1].y1 + 1);
        }
    }
    draw_complete = 1;
}
void WaterLine::update() {
}

void WaterLine::calculate_path(LineSegment* lineseg, int num_of_line) {
    path[path_idx].x1 = start_dot.x;
    path[path_idx].y1 = start_dot.y;
    path_idx++;

    for (; start_dot.y <= ofGetHeight() - 50; start_dot.y++) {
        for (int i = 0; i < num_of_line; i++) {
            // 1) Ignore line that located higher than water particle.
            if (start_dot.y >= lineseg[i].y1 && start_dot.y >= lineseg[i].y2) continue;
            // 2) Check whether the dot point exists between the each end of line segment.
            // If pos.x exists btw. y1 and y2 then, eventually hit the line segment.q
            if (lineseg[i].x1 < lineseg[i].x2) {
                if (start_dot.x <= lineseg[i].x1 || start_dot.x >= lineseg[i].x2)
                    continue;
            }
            else if (lineseg[i].x1 > lineseg[i].x2) {
                if (start_dot.x <= lineseg[i].x2 || start_dot.x >= lineseg[i].x1)
                    continue;
            }
            // Slope °è»ê
            double temp_slope = (double)(start_dot.y - lineseg[i].y1) / (start_dot.x - lineseg[i].x1);
            // Dot exists in line

            if (abs(temp_slope - lineseg[i].slope) <= EPSILON) {
                path[path_idx].x1 = start_dot.x;
                path[path_idx].y1 = start_dot.y + 2;
                path_idx++;

                // Debug output
                //cout << "[" << i << "]" << "x: " << start_dot.x << " " << "y: " << start_dot.y << endl;
                if (lineseg[i].slope < 0) {
                    path[path_idx - 1].x1++;
                    start_dot.x = lineseg[i].x1;
                    start_dot.y = lineseg[i].y1 - 2;
                }
                else {
                    path[path_idx - 1].x1--;
                    start_dot.x = lineseg[i].x2;
                    start_dot.y = lineseg[i].y2 - 2;
                }
                path[path_idx].x1 = start_dot.x;
                path[path_idx].y1 = start_dot.y;
                path_idx++;

                // Debug output
                //cout << "[" << i << "]" << "x: " << start_dot.x << " " << "y: " << start_dot.y << endl;
            }
        }
    }
    // Last path
    path[path_idx].x1 = start_dot.x;
    path[path_idx].y1 = start_dot.y;
    path_idx++;

    calc_complete = 1;
}

WaterLine::WaterLine(int num_of_line) {
    draw_complete = 0;
    calc_complete = 0;

    uniqueColor_r = ofRandom(0, 255);
    uniqueColor_g = ofRandom(0, 255);
    uniqueColor_b = ofRandom(185, 255);


    path_idx = 0;
    if (!path)
        path = (Dot*)malloc(sizeof(Dot) * (2*num_of_line+4));
}


WaterLine::~WaterLine() {
    free(path);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}




