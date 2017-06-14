//
//  Person.hpp
//  restartrefrain
//
//  Created by vibber on 13/06/17.
//
//

#ifndef Person_hpp
#define Person_hpp

#include "ofMain.h"
#include "Trackgroup.hpp"
#include <stdio.h>

class Pointset : public ofBaseApp {
public:
    array<ofVec2f,3> values;
    array<float,3> distances;
    int closestPoint;
    
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
    vector<Trackgroup*> trackgroups;
    
    void setCoord(ofVec2f coord);
    void updatePointset(int pointsetIndex, int pointsetCount);
    void updateDistances();
    void draw();
    void drawPointset();
    void drawDistanceLine();
    void setColor(int index);
    void resetTrackgroups();
    void addToTrackgroups(Trackgroup* group);
    void setActiveTracks();
};


#endif /* Person_hpp */
