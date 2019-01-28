#include "ofApp.h"

#include "Boid.h"
#include "Kinematic.h"
#include "Steering/BasicKinematicSteering.h"
#include "Steering/SeekSteering.h"
#include "Steering/WanderSteering.h"
#include "Scene.h"

#include <graphics/ofGraphics.h>


//--------------------------------------------------------------
void ofApp::setup(){
	
	// setup basic motion
	Kinematic initalKinematic(glm::vec2(10, ofGetWindowHeight() - 10), 0, glm::vec2(100, 0), 0);
	Boid* initialBoid = new Boid(initalKinematic, nullptr, 100, 0, 0, 0, 0, 0, 0);

	BasicKinematicSteering* steering = new BasicKinematicSteering(initialBoid);
	initialBoid->mpKinematicSteering = steering;
	std::vector<Boid*> boids1({initialBoid});
	
	Scene* scene = new Scene(boids1);
	mpScenes.push_back(scene);

	// setup kinematic seek
	mSeekTarget.position = glm::vec2(10, 10);
	Kinematic kinematicSeekKinematic(glm::vec2(10, 10), 0, glm::vec2(0, 0), 0);
	Boid* kinematicSeekBoid = new Boid(kinematicSeekKinematic, &mSeekTarget, 100, 0, 100, 0, 10, 0, 0);
	KinematicSeekSteering* kinematicSeekSteering = new KinematicSeekSteering(kinematicSeekBoid);
	kinematicSeekBoid->mpKinematicSteering = kinematicSeekSteering;
	std::vector<Boid*> boids2({ kinematicSeekBoid });

	scene = new Scene(boids2);
	mpScenes.push_back(scene);

	// setup dynamic seek
	Kinematic dynamicSeekKinematic(glm::vec2(10, 10), 0, glm::vec2(0, 0), 0);
	Boid* dynamicSeekBoid = new Boid(dynamicSeekKinematic, &mSeekTarget, 100, 0, 100, 0, 10, 70, 0.1f);
	DynamicSeekSteering* dynamicSeekSteering = new DynamicSeekSteering(dynamicSeekBoid);
	dynamicSeekBoid->mpDynamicSteering = dynamicSeekSteering;
	std::vector<Boid*> boids3({ dynamicSeekBoid });

	scene = new Scene(boids3);
	mpScenes.push_back(scene);

	// setup kinematic wander
	Kinematic kinematicWanderKinematic(glm::vec2(300, 300), 0, glm::vec2(100, 0), 0);
	Boid* kinematicWanderBoid = new Boid(kinematicWanderKinematic, nullptr, 100, PI * 5, 100, 0, 0, 0, 0);
	KinematicWanderSteering* kinematicWanderSteering = new KinematicWanderSteering(kinematicWanderBoid);
	kinematicWanderBoid->mpKinematicSteering = kinematicWanderSteering;
	std::vector<Boid*> boids4({ kinematicWanderBoid });
	
	scene = new Scene(boids4);
	mpScenes.push_back(scene);

	// setup dynamic wander
	Kinematic dynamicWanderKinematic(glm::vec2(300, 300), 0, glm::vec2(100, 0), 0);
	Boid* dynamicWanderBoid = new Boid(dynamicWanderKinematic, nullptr, 100, PI * 5, 100, 0, 10, 70, 0.1f, 50, 100);
	DynamicWanderSteering* dynamicWanderSteering = new DynamicWanderSteering(dynamicWanderBoid);
	dynamicWanderBoid->mpDynamicSteering = dynamicWanderSteering;
	std::vector<Boid*> boids5({ dynamicWanderBoid });

	scene = new Scene(boids5);
	mpScenes.push_back(scene);


}

//--------------------------------------------------------------
void ofApp::update(){
	mpScenes[mSceneIndex]->Update(ofGetLastFrameTime());
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofBackground(20);

	mpScenes[mSceneIndex]->Draw();

}

void ofApp::exit()
{
	for (auto scene : mpScenes)
	{
		delete scene;
	}

	mpScenes.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int index = key - '1';
	if (index >= 0 && index < mpScenes.size())
	{
		mSceneIndex = index;
		mpScenes[mSceneIndex]->Reset();
	}
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
