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

	static std::vector<Kinematic> GetPath(glm::vec2 start, glm::vec2 end);


private:
	std::vector<Scene*> mpScenes;
	Boid* mpPlayer;
	const int WIDTH = 1024;
	const int HEIGHT = 768;
	Kinematic mSeekTarget;
	int mSceneIndex;
	int mStartIndex = 0;
	int mEndIndex = 0;
	bool bIsFirst = true;
};
