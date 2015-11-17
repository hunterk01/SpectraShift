#pragma once
#include <string>
#include "sfwdraw.h"
#include "GameObjects.h"


class Player : public GameObject
{
public:
	vec2 position = { 450, 450 };
	float speed = 250;
	int forwardQuadrant, reverseQuadrant, rightQuadrant, leftQuadrant;

	void SetPlayerAngles();
	
	void Movement();

	void determineQuadrant();

	void applyVelocity(int inQuadrant);

};

