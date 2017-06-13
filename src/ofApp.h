#pragma once

#include "ofMain.h"
#include <math.h>
#include "ofxOsc.h"
#include <vector>
#include "Person.hpp"
#include <random>

using namespace std;

// listen on port
#define PORT 8112
#define FLOORHEIGHT 400
#define FLOORWIDTH 400
#define CIRCLERADIUS 0.75

//A trackgroup is a collection of 3 tracks.
//The 'tracks' array is randomized so that the tracks of the musicians are randomly assigned to a point on the floor
//the indexes of 'tracks' corresponds to a pointset in a Person object, and the value is the track (ie. mikkel, s¿s or Jens)
//There are 8 trackgroups in total. They are distributed to the different users.
class Trackgroup {
    public:
        array<int, 3> tracks;
        void setup();
    
        void getTrackForClosestPoint();
    
        Trackgroup() {};
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void updatePerson(int id, ofVec2f pos);
        void deleteInactivePeople();
        void updatePointsAndDistances();
        void updateTrackgroupTracks();
    
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
    
        //Trackgroup trackgroups[8];
        vector<Person> people;
    
    
        ofxOscReceiver oscReceiver;
        string msg_string;
};