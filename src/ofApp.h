#pragma once

#include "ofMain.h"

#include "Scene.h"

class Boid;

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void exit() override;


	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


private:
	std::vector<Scene*> mpScenes;
	Boid* mpBoid;
	const int WIDTH = 1024;
	const int HEIGHT = 768;
	Kinematic mSeekTarget;
	int mSceneIndex;
	int mStartIndex = 0;
	int mEndIndex = 0;
	bool bIsFirst = true;
};
