#include "ofApp.h"

#include "Boid.h"
#include "Kinematic.h"

#include <graphics/ofGraphics.h>


//--------------------------------------------------------------
void ofApp::setup(){
	
	ofSetCircleResolution(64);
	
	Kinematic initalKinematic(glm::vec2(0, HEIGHT), 0, glm::vec2(10, 0), 0);
	Boid initialBoid(initalKinematic);

	mBoids.push_back(initialBoid);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto& boid : mBoids)
		boid.Update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(20);
	//mCamera.begin();


	for (const auto& boid : mBoids)
		boid.Draw();

	ofSetColor(255);

	//mCamera.end();

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
