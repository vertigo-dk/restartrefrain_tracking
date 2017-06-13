#include "ofApp.h"

void Trackgroup::setup() {
    for (int i=0; i<this->tracks.size(); i++) {
        this->tracks[i] = i;  // fill the array in order
    }
    
    random_device rd;
    mt19937 g(rd());
    
    shuffle(this->tracks.begin(), this->tracks.end(), g);
    
    cout << "shuffle: ";
    
    for (auto& t:this->tracks) {
        cout << t << " ";
    }
    cout << "\n";
}

//--------------------------------------------------------------
void ofApp::setup(){

    // Setup OSC
    
    cout << "listening for osc messages on port " << PORT << "\n";
    oscReceiver.setup(PORT);
    
    //updateTrackGroups();
    
    Trackgroup tg = *new Trackgroup();
    tg.setup();
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


void updateTrackgroupTracks() {
    
}

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
    ofVec2f floorcoord = *new ofVec2f(FLOORWIDTH, FLOORHEIGHT);
    ofDrawRectangle(0, 0, floorcoord.x, floorcoord.y);
    
    //Draw users and points

    for (auto& person:people) {
        ofSetColor(person.color);
        
        person.draw();
        
        person.drawPointset();
        
        //person.drawDistanceLine();
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
