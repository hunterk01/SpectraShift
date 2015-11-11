#pragma once
#include <string>
#include "sfwdraw.h"
#include "Player.h"
#include "AssetLibrary.h"

struct vec2 { float x, y; };

class GameObject
{
public:
	std::string textureName, animationName;
	vec2 position, velocity, dimensions;
	float targetAngle, perpAngle, speed;
	int health;
	bool light, isAlive;
	float animTimer;
	unsigned currentFrame;

	// Constructor

	// Destructor

	virtual void SetAngles();
	virtual void Draw();
	virtual void Update();
	virtual bool hasCollided();
};