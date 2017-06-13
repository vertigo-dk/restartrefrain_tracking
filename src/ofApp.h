#pragma once

#include "ofMain.h"
#include <math.h>
#include "ofxOsc.h"
#include <vector>
#include "Person.hpp"

using namespace std;

// listen on port
#define PORT 8112
#define FLOORHEIGHT 400
#define FLOORWIDTH 400
#define CIRCLERADIUS 0.75

class Trackgroup {
public:
    Person* person;
    int point0track;
    int point1track;
    int point2track;
    
    vector<int> tracks;
    
    Trackgroup() {};
    
    void setup(Person* person) {
        this->person = person;
    };
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void updatePerson(int id, ofVec2f pos);
        void deleteInactivePeople();
        void updatePointsAndDistances();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        Trackgroup trackgroups[8];
        vector<Person> people;
        Pointset points;
        Pointset points2;
    
        ofVec2f floorcoord;
        float circleSize = 0.75;
    
        ofxOscReceiver oscReceiver;
        string msg_string;
};