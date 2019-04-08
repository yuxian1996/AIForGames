#pragma once

#include "Kinematic.h"
#include "Group.h"

#include <vector>

class Boid;
class Scene
{

public:
	Scene(const std::vector<Boid*>& ipBoids, Group* ipGroup = nullptr, Boid * ipPlayer = nullptr);
	~Scene();
	void Update(float inDeltaTime);
	void Draw();
	void Reset();

	Boid* GetPlayer() { return mpPlayer; }

private:
	Boid* mpPlayer;
	std::vector<Boid*> mpBoids;
	Group* mpGroup;
	std::vector<Kinematic> initalKinematics;
};