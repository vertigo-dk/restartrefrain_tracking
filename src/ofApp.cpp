#include "ofApp.h"

ofVec2f getFloorCoord() {
    return *new ofVec2f(400,400);
}
float getCircleRadius() {
    return 0.75;
}

//--------------------------------------------------------------

//Index is the index of the pointset = index of the person it belongs to
//count is the total count of pointsets
void Pointset::setup(int index, int count) {
    ofVec2f floor = getFloorCoord();
    float radius = getCircleRadius();
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
    this->closestPoint = this->returnPoint(smallestIndex);
}

//--------------------------------------------------------------
void ofApp::setup(){

    // Setup OSC
    
    cout << "listening for osc messages on port " << PORT << "\n";
    oscReceiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){

    // OSC MESSAGES

    int count = 0;
    msg_string = "";
    
    while(oscReceiver.hasWaitingMessages()){
    
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        if(m.getAddress() == "/tracker/person"){
            int id = m.getArgAsInt32(1); //identifier
            ofVec2f position;
            position.x = m.getArgAsFloat(2); // pos X
            position.y = m.getArgAsFloat(3); // pos Y
            
            msg_string += "person " + ofToString(id) + " [" + ofToString(position.x) + ", " + ofToString(position.y) + "] \n";
            
            updatePerson(id, position);
        }
    }
    
    deleteInactivePeople();
    
    updatePointsAndDistances();
}

//--------------------------------------------------------------

//pointsetIndex is the number of the person in the people vector.
//It is also used to calculate the offset of the points in the pointset
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
    ofDrawCircle(this->points.closestPoint.x, this->points.closestPoint.y, 5);
}

void Person::drawDistanceLine() {
     ofSetColor(this->color);
    
    ofDrawLine(this->coord, this->points.closestPoint);
}

void Person::setColor(int index) {
    float hue = (index/8.0) * 255.0;
    cout << " color " << hue << "\n";
    this->color = ofColor::fromHsb( hue, 255, 255 );
}

void Person::setCoord(ofVec2f coord) {
    this->coord = coord * getFloorCoord();
}

void Person::updateDistances() {
    this->points.setDistances(this->coord);
    
    this->points.setClosestPoint();
    
    cout << "closest " << this->points.closestPoint.x << "," << this->points.closestPoint.y << "\n";
}

//--------------------------------------------------------------

void ofApp::updatePointsAndDistances() {
    int pointsetCount = people.size();
    
    for (int i = 0; i<pointsetCount; i++) {
        people[i].updatePointset(i, pointsetCount);
        people[i].updateDistances();
    }
}

//Inactive persons are deleted
void ofApp::deleteInactivePeople() {
    vector<Person> newPeople;

    for (auto& person:people) {
        if (person.framesSinceUpdate < 10) {
            //cout << "push" << "\n";
            newPeople.push_back(person);
        }
    }
    people = newPeople;
}

// Find the person and write the new position into it. If ID is not found a new person is
// created.
void ofApp::updatePerson(int id, ofVec2f pos) {
    bool found = false;
    
    for (auto& person:people) {
        person.framesSinceUpdate++;
        if (person.id == id) {
            person.setCoord(pos);
            person.framesSinceUpdate = 0;
            found = true;
        }
    }
    if(!found) {
        Person newPerson;
        newPerson.id = id;
        newPerson.setCoord(pos);
        newPerson.framesSinceUpdate = 0;
        newPerson.setColor(people.size());
        people.push_back(newPerson);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor (255, 255, 255);
    ofVec2f floorcoord = getFloorCoord();
    ofDrawRectangle(0, 0, floorcoord.x, floorcoord.y);
    
    //Draw users and points

    for (auto& person:people) {
        ofSetColor(person.color);
        
        person.draw();
        
        person.drawPointset();
        
        person.drawDistanceLine();
    }
       
    if(msg_string != "") {
        cout << msg_string << "\n";
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
