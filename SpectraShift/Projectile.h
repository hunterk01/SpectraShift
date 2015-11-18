#pragma once

#include "GameObjects.h"
#include "GameState.h"

class Projectile : public GameObject
{
	float lifetime;

public:
	Projectile(float a_x, float a_y, float dx, float dy, float lifespan);

	virtual void onCollision(GameObject &go, float distance);

	virtual void update();

	virtual void draw();
};