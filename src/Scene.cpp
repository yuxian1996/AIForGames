#include "Scene.h"

#include "Boid.h"

Scene::Scene(const std::vector<Boid*>& ipBoids, Group* ipGroup)
{
	mpBoids = ipBoids;
	for (auto pBoid : mpBoids)
	{
		initalKinematics.push_back(pBoid->mKinematic);
	}
	mpGroup = ipGroup;
}

Scene::~Scene()
{
	for (auto pBoid : mpBoids)
		delete pBoid;
	if (mpGroup != nullptr)
	{
		delete mpGroup;
		mpGroup = nullptr;
	}

	mpBoids.clear();
}

void Scene::Update(float inDeltaTime)
{
	if (mpGroup != nullptr)
		mpGroup->Update();

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
