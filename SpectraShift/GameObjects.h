#pragma once
#include <string>
#include "sfwdraw.h"
#include "AssetLibrary.h"

struct vec2 { float x, y; };

class GameState;

class GameObject
{
public:
	// Game state reference so that everyone can interact with the game state
	static GameState *&gs()
	{
		static GameState *game;
		return game;
	}

	std::string textureName, animationName;
	vec2 position, trajectory, dimensions;
	float targetAngle, perpAngle, speed, radius = fmax(dimensions.x, dimensions.y);
	int health;
	bool light, isAlive;
	float animTimer;
	unsigned currentFrame;

	virtual void SetAngles(GameObject &targetObject);

	virtual void Draw();

	virtual void Update();

	virtual void onCollision(GameObject &go, float distance);
};

float doCollision(GameObject &go1, GameObject &go2);
