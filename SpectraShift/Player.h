#pragma once
#include <string>
#include "sfwdraw.h"
#include "GameObjects.h"
#include "Background.h"

class GameState;
class MenuState;

extern bool playerLight, compassPointControls;
extern float lightEnergy, darkEnergy, healthTracker;

class Player : public GameObject
{
public:
	float speed = 250, fireDelay, rateOfFire;
	int forwardQuadrant, reverseQuadrant, rightQuadrant, leftQuadrant;

	Player();

	void SetPlayerAngles();
	
	void Movement();

	void determineQuadrant();

	void applyVelocity(int inQuadrant);

	void fireWeapon(float inAdjTargetAngle);

	void energyGain();

	virtual void onCollision(GameObject &go, float distance);

	virtual void draw();
};

