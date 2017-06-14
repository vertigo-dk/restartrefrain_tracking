//
//  Person.cpp
//  restartrefrain
//
//  Created by vibber on 13/06/17.
//
//

#include "Person.hpp"
#include "ofApp.h"

//--------------------------------------------------------------

//Index is the index of the pointset = index of the person it belongs to
//count is the total count of pointsets
void Pointset::setup(int index, int count) {
    ofVec2f floor = *new ofVec2f(FLOORWIDTH, FLOORHEIGHT);
    float radius = CIRCLERADIUS;
    float offset = PI*2/count * index;
    float rad = offset;
    
    for(auto& p:this->values) {
        p.x = floor.x/2 + floor.x/2 * radius * cos( rad );
        p.y = floor.x/2 + floor.y/2 * radius * sin( rad );
        
        rad += PI*2 / 3;
    }
}

void Pointset::setDistances(ofVec2f p1) {
    for (int i = 0; i < values.size(); i++) {
        ofVec2f p2 = values[i];
        this->distances[i] = abs(p1.distance( p2 ));
        //cout << this->distances[i] << "\n";
    }
}

ofVec2f Pointset::returnPoint(int index) {
    return this->values[index];
}

void Pointset::setClosestPoint() {
    int smallestIndex = 0;
    for (int i = 0; i < this->distances.size(); i++) {
        if ( distances[i] < distances[smallestIndex] ) {
            smallestIndex = i;
        }
    }
    this->closestPoint = smallestIndex;
}

//--------------------------------------------------------------

void Person::setActiveTracks() {
    for (auto& tg:this->trackgroups) {
        tg->setActiveTrack(this->points.closestPoint);
    }
}

void Person::resetTrackgroups() {
    this->trackgroups.clear();
}

void Person::addToTrackgroups(Trackgroup* tg) {
    this->trackgroups.push_back(tg);
}

//pointsetIndex equals the index of the person in the people vector.
//It is used to calculate the angle offset of the points in the pointset
void Person::updatePointset(int pointsetIndex, int pointsetCount) {
    this->points = *new Pointset();
    this->points.setup(pointsetIndex, pointsetCount);
}

void Person::draw() {
    ofSetColor(this->color);
    ofSetLineWidth(3);
    
    ofDrawLine(this->coord.x, this->coord.y -5, this->coord.x, this->coord.y+5);
    ofDrawLine(this->coord.x-5, this->coord.y, this->coord.x + 5, this->coord.y);
}

void Person::drawPointset() {
    ofSetColor(this->color);
    
    for(auto& p:this->points.values) {
        ofDrawCircle(p.x, p.y, 10);
    }
    
    //Draw closest point
    ofSetColor(255, 255, 255);
    
    ofVec2f closestPoint = this->points.values[this->points.closestPoint];
    
    ofDrawCircle(closestPoint.x, closestPoint.y, 5);
}

void Person::drawDistanceLine() {
    ofVec2f closestPoint = this->points.values[this->points.closestPoint];
    ofSetColor(this->color);
    
    ofDrawLine(this->coord, closestPoint);
}

void Person::setColor(int index) {
    float hue = (index/8.0) * 255.0;
    this->color = ofColor::fromHsb( hue, 255, 255 );
}

void Person::setCoord(ofVec2f coord) {
    ofVec2f floor = *new ofVec2f(FLOORWIDTH, FLOORHEIGHT);
    this->coord = coord * floor;
}

void Person::updateDistances() {
    this->points.setDistances(this->coord);
    
    this->points.setClosestPoint();
    
    //cout << "closest " << this->points.closestPoint.x << "," << this->points.closestPoint.y << "\n";
}