#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    // Setup OSC
    
    cout << "listening for osc messages on port " << INPORT << "\n";
    oscReceiver.setup(INPORT);
    oscSender.setup(HOST, OUTPORT);
    
    updateTrackgroupTracks();
    
    appEnabled = 0;
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
            
            msg_string += "OSC IN: person " + ofToString(id) + " [" + ofToString(position.x) + ", " + ofToString(position.y) + "] \n";
            
            updatePerson(id, position);
        }
    }
    
    setFramesSinceUpdate();
    
    deleteInactivePeople();
    
    updatePointsAndDistances();
    
    checkForNoPeople();
    
    distributeTrackgroups();
    
    setActiveTracks();

    sendOSCTrackgroupMessages();
    
    sendOtherOSCMessages();
}

//--------------------------------------------------------------

void ofApp::setFramesSinceUpdate() {
    for (auto& person:people) {
        person.framesSinceUpdate++;
    }
}

void ofApp::sendOtherOSCMessages() {
    ofxOscMessage m;
    m.setAddress("/enabled");
    m.addIntArg(appEnabled);
    oscSender.sendMessage(m, false);
}

void ofApp::sendOSCTrackgroupMessages() {
    if (appEnabled == 0) {
        return;
    }
    for (int i = 0; i < trackgroups.size(); i++) {
        Trackgroup tg = trackgroups[i];
        cout << "active track: " << tg.activeTrack << "\n";
        
        ofxOscMessage m;
        m.setAddress("/trackgroup/" + ofToString(i));
        m.addIntArg(tg.activeTrack);
        oscSender.sendMessage(m, false);
    }
}

void ofApp::setActiveTracks() {
    for (auto& person: people) {
        person.setActiveTracks();
    }
}

void ofApp::checkForNoPeople() {
    if (people.size() == 0) {
        updateTrackgroupTracks();
        appEnabled = 0;
    } else {
        appEnabled = 1;
    }
}

void ofApp::distributeTrackgroups() {
    
    //cout << "size of people vector: " << people.size() << "\n";
    
    for (auto& person:people) {
        person.resetTrackgroups();
    }
    
    if (people.size() > 0) {
        for (int i = 0; i < trackgroups.size(); i++) {
            int remainder = i % people.size();
            
            people[remainder].addToTrackgroups(&trackgroups[i]);
        }
      
        //for (int j = 0; j < people.size(); j++) {
        //    cout << "Person " << j << " has " << people[j].trackgroups.size() << " trackgroups \n";
        //}

    }
}

void ofApp::updateTrackgroupTracks() {
    for (auto& tg:trackgroups) {
        tg.setup();
    }
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
