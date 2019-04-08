#include "Scene.h"

#include "Boid.h"

Scene::Scene(const std::vector<Boid*>& ipBoids, Group* ipGroup, Boid * ipPlayer)
{
	mpPlayer = ipPlayer;
	mpBoids = ipBoids;
	for (auto pBoid : mpBoids)
	{
		initalKinematics.push_back(pBoid->mKinematic);
		pBoid->mpPlayer = ipPlayer;
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
	if (mpPlayer != nullptr)
	{
		delete mpPlayer;
		mpPlayer = nullptr;
	}
}

void Scene::Update(float inDeltaTime)
{
	if (mpGroup != nullptr)
		mpGroup->Update();

	for (auto pBoid : mpBoids)
	{
		pBoid->Update(inDeltaTime);
	}

	if(mpPlayer)
		mpPlayer->Update(inDeltaTime);
}

void Scene::Draw()
{
	for (auto pBoid : mpBoids)
	{
		pBoid->Draw();
	}

	if(mpPlayer)
		mpPlayer->Draw();
}

void Scene::Reset()
{
	for(int i = 0; i < mpBoids.size(); i++)
	{
		mpBoids[i]->mKinematic = initalKinematics[i];
	}
}
