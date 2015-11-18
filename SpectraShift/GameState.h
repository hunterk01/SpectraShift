#pragma once

#include "Player.h"
#include "Projectile.h"
#include <vector>

class GameState
{
	Player player; 	// store all of our gameobjects
	std::vector<Projectile> bullets;

public:
	// Parameters may match the constructor for the bullet
	void makeBullet(float x, float y, float dx, float dy, float lifespan);

	void makeExplosion();
	void makeEnemy();
	void makeAsteroid();

	GameState();

	void update();

	void draw();

	// Needs some way to 'spawn/destroy' bullets/enemies.

	// Changes in gameplay happen here.
};

