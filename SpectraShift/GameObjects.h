#pragma once
#include <string>
#include "sfwdraw.h"
#include "AssetLibrary.h"

struct vec2 { float x, y; };

class GameObject
{
public:
	std::string textureName, animationName;
	vec2 position, velocity, dimensions;
	float targetAngle, perpAngle, speed, radius = fmax(dimensions.x, dimensions.y);
	int health;
	bool light, isAlive;
	float animTimer;
	unsigned currentFrame;

	GameObject() {};
	~GameObject() {};

	virtual void SetAngles(GameObject &targetObject);

	virtual void Draw();

	virtual void Update();

	virtual void onCollision(GameObject &go, float distance);
};
