//
//  Trackgroup.hpp
//  restartrefrain
//
//  Created by vibber on 14/06/17.
//
//

#ifndef Trackgroup_hpp
#define Trackgroup_hpp

#include <stdio.h>
#include "ofMain.h"
#include <random>

using namespace std;

//A trackgroup is a collection of 3 tracks.
//The 'tracks' array is randomized so that the tracks of the musicians are randomly assigned to a point on the floor
//the indexes of 'tracks' corresponds to a music track (ie. søs, mikkel or jens), and the value is a point in the pointset.
//There are 8 trackgroups in total. They are distributed to the different users.
class Trackgroup {
public:
    array<int, 3> tracks;
    int activeTrack;
    
    void setup();
    void setActiveTrack(int pointID);
    
    Trackgroup() {};
};


#endif /* Trackgroup_hpp */
