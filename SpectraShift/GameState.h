#pragma once

#include "Player.h"
#include "Projectile.h"
#include "Asteroid.h"
#include <vector>

class GameState
{
	Player player;
	Asteroid asteroid;
	std::vector<Projectile> bullets;
	std::vector<Asteroid> asteroids;
	
public:
	bool resetGame = false;
	float buttonDelay = .7f;

	GameState();

	void makeBullet(float x, float y, float dx, float dy, float lifespan);
	void makeAsteroid();
	void update();
	void draw();
};

