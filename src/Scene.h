#pragma once

#include "Kinematic.h"

#include <vector>

class Boid;
class Scene
{

public:
	Scene(const std::vector<Boid*>& ipBoids);
	~Scene();
	void Update(float inDeltaTime);
	void Draw();
	void Reset();

private:
	std::vector<Boid*> mpBoids;
	std::vector<Kinematic> initalKinematics;
};