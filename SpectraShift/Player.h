#pragma once
#include <string>
#include "sfwdraw.h"
#include "GameObjects.h"


class Player : public GameObject
{
public:
	vec2 position = { 450, 450 };
	float speed = 250;

	void SetPlayerAngles();
	
	void Movement();
};

