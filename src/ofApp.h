#pragma once

#include "ofMain.h"
#include <math.h>
#include "ofxOsc.h"
#include <vector>
using namespace std;

// listen on port
#define PORT 8112

class Pointset : public ofBaseApp {
public:
    array<ofVec2f,3> values;
    array<float,3> distances;
    ofVec2f closestPoint;
    
    Pointset() {};
    
    void setup (int index, int count);
    
    void setDistances(ofVec2f p);
    void setClosestPoint();
    ofVec2f returnPoint(int index);
};


class Person {
public:
    int id;
    ofVec2f coord;
    int framesSinceUpdate;
    ofColor color;
    Pointset points;
    
    void setCoord(ofVec2f coord);
    void updatePointset(int pointsetIndex, int pointsetCount);
    void updateDistances();
    void draw();
    void drawPointset();
    void drawDistanceLine();
    void setColor(int index);
    //void updateDistances();
};

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