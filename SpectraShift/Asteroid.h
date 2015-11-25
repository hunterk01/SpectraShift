#pragma once
#include "GameObjects.h"
#include "GameState.h"

class Asteroid : public GameObject
{
	float lifetime;

public:
	Asteroid();

	virtual void onCollision(GameObject &go, float distance);

	virtual void update();

	virtual void draw(bool inLight);

	void AsteroidSpawn();
};

