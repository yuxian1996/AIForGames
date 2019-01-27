#pragma once

#include <vector>

template<class T>
class Manager
{
public:
	static Manager* Instance()
	{
		static Manager* spInstance = new Manager;
		
		return spInstance;
	}

	void Update(float inDeltaTime);
	void Add(const T& newObject);
	void Destroy(const T& destroyedObject);

private:
	std::vector<T> mObjects;
	std::vector<T> mKillingObjects;
};

template<class T>
inline void Manager<T>::Update(float inDeltaTime)
{
	for (auto obj : mKillingObjects)
	{
		auto index = std::find(mObjects.begin(), mObjects.end(), obj) - mObjects.begin();
		mObjects.erase(mObjects.begin() + index);
	}

	for (auto& obj : mObjects)
		obj.Update(inDeltaTime);
}

template<class T>
inline void Manager<T>::Add(const T & newObject)
{
	mObjects.push_back(newObject);
}

template<class T>
inline void Manager<T>::Destroy(const T & destroyedObject)
{
	mKillingObjects.push_back(destroyedObject);
}
