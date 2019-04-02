#pragma once

#include "../Boid.h"

class Boid;

class Context
{
public:
	Context() = default;
	Context(Boid* ipBoid) : mpBoid(ipBoid) {}
	virtual ~Context() = default;

	Boid* GetOwner() const { assert(mpBoid != nullptr); return mpBoid; }

private:
	Boid* mpBoid;
};