#pragma once
#include <string>
#include "sfwdraw.h"
#include "GameObjects.h"

class GameState;

class Player : public GameObject
{
public:
	vec2 position = { 450, 450 };
	float speed = 250, fireDelay, rateOfFire;
	int forwardQuadrant, reverseQuadrant, rightQuadrant, leftQuadrant;

	Player()
	{
		isAlive = true;
		rateOfFire = 0.6f;
	}

	void SetPlayerAngles();
	
	void Movement();

	void determineQuadrant();

	void applyVelocity(int inQuadrant);

};

