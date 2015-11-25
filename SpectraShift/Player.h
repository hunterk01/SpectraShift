#pragma once
#include <string>
#include "sfwdraw.h"
#include "GameObjects.h"
#include "Background.h"

class GameState;
class MenuState;

class Player : public GameObject
{
public:
	vec2 position = { 450, 450 };
	float speed = 250, fireDelay, rateOfFire;
	int forwardQuadrant, reverseQuadrant, rightQuadrant, leftQuadrant;
	bool compassPointControls;

	Player()
	{
		isAlive = true;
		light = true;
		rateOfFire = .3f;
		compassPointControls = false;
	}

	void SetPlayerAngles();
	
	void Movement();

	void determineQuadrant();

	void applyVelocity(int inQuadrant);

	void fireWeapon(float inAdjTargetAngle);

	void setPlayerWorld(bool inValue);

	bool checkPlayerWorld();
};

