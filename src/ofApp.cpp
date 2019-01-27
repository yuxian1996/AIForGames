#include "ofApp.h"

#include "Boid.h"
#include "Kinematic.h"
#include "Steering/BasicKinematicSteering.h"
#include "Steering/SeekSteering.h"

#include <graphics/ofGraphics.h>


//--------------------------------------------------------------
void ofApp::setup(){
		
	Kinematic initalKinematic(glm::vec2(10, ofGetWindowHeight() - 10), 0, glm::vec2(100, 0), 0);
	Boid* initialBoid = new Boid(initalKinematic);

	BasicKinematicSteering* steering = new BasicKinematicSteering(initialBoid->GetKinematic(), nullptr, 100, 1, 100, 10);
	initialBoid->AddSteering(steering);
	mpBoids.push_back(initialBoid);

	mSeekTarget.position = glm::vec2(10, 10);
	Kinematic kinematicSeekKinematic(glm::vec2(10, 10), 0, glm::vec2(0, 0), 0);
	Boid* kinematicSeekBoid = new Boid(kinematicSeekKinematic);
	KinematicSeekSteering* kinematicSeekSteering = new KinematicSeekSteering(kinematicSeekBoid->GetKinematic(), &mSeekTarget, 100, 0, 100, 10);
	kinematicSeekBoid->AddSteering(kinematicSeekSteering);
	mpBoids.push_back(kinematicSeekBoid);

	Kinematic dynamicSeekKinematic(glm::vec2(ofGetWindowWidth() - 10), 0, glm::vec2(0, 0), 0);
	Boid* dynamicSeekBoid = new Boid(dynamicSeekKinematic);
	DynamicSeekSteering* dynamicSeekSteering = new DynamicSeekSteering(dynamicSeekBoid->GetKinematic(), &mSeekTarget, 100, 0, 100, 10, 10, 20, 1.0f);
	dynamicSeekBoid->AddSteering(dynamicSeekSteering);
	mpBoids.push_back(dynamicSeekBoid);
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto& boid : mpBoids)
		boid->Update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(20);
	//mCamera.begin();


	for (const auto& boid : mpBoids)
		boid->Draw();

	//mCamera.end();

}

void ofApp::exit()
{
	for (auto pBoid : mpBoids)
	{
		delete pBoid;
	}

	mpBoids.clear();
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
	mSeekTarget.position = glm::vec2(x, y);
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
