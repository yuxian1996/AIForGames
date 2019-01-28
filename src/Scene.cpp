#include "Scene.h"

#include "Boid.h"

Scene::Scene(const std::vector<Boid*>& ipBoids)
{
	mpBoids = ipBoids;
	for (auto pBoid : mpBoids)
	{
		initalKinematics.push_back(pBoid->mKinematic);
	}
}

Scene::~Scene()
{
	for (auto pBoid : mpBoids)
		delete pBoid;

	mpBoids.clear();
}

void Scene::Update(float inDeltaTime)
{
	for (auto pBoid : mpBoids)
	{
		pBoid->Update(inDeltaTime);
	}
}

void Scene::Draw()
{
	for (auto pBoid : mpBoids)
	{
		pBoid->Draw();
	}
}

void Scene::Reset()
{
	for(int i = 0; i < mpBoids.size(); i++)
	{
		mpBoids[i]->mKinematic = initalKinematics[i];
	}
}
