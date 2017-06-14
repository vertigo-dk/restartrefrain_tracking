//
//  Trackgroup.cpp
//  restartrefrain
//
//  Created by vibber on 14/06/17.
//
//

#include "Trackgroup.hpp"

void Trackgroup::setActiveTrack(int pointID) {
    for (int i = 0; i < this->tracks.size(); i++) {
        if (this->tracks[i] == pointID) {
            this->activeTrack = i;
        }
    }
}

void Trackgroup::setup() {
    for (int i=0; i<this->tracks.size(); i++) {
        this->tracks[i] = i;  // fill the array in order
    }
    
    random_device rd;
    mt19937 g(rd());
    
    shuffle(this->tracks.begin(), this->tracks.end(), g);
    
    /*
     cout << "shuffle: ";
     
     for (auto& t:this->tracks) {
     cout << t << " ";
     }
     cout << "\n";
     */
}