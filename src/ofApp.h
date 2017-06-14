#pragma once

#include "ofMain.h"
#include <math.h>
#include "ofxOsc.h"
#include <vector>
#include "Person.hpp"
#include "Trackgroup.hpp"

using namespace std;

// listen on port
#define INPORT 8112
#define OUTPORT 8113
#define HOST "localhost"

#define FLOORHEIGHT 800
#define FLOORWIDTH 800
#define CIRCLERADIUS 0.75

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    
        void updatePerson(int id, ofVec2f pos);
        void deleteInactivePeople();
        void updatePointsAndDistances();
        void updateTrackgroupTracks();
        void distributeTrackgroups();
        void checkForNoPeople();
        void setActiveTracks();
        void sendOSCTrackgroupMessages();
        void sendOtherOSCMessages();
        void setFramesSinceUpdate();
    
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
    
        array<Trackgroup,8> trackgroups;
        vector<Person> people;
        int appEnabled;
    
        ofxOscReceiver oscReceiver;
        ofxOscSender oscSender;
    
        string msg_string;
};