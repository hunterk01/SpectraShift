#include "GameObjects.h"
#include "GameState.h"
#include "Asteroid.h"
#include <time.h>

int lightShift = 0;

Asteroid::Asteroid()
{
	int asteroidType = rand() % 4;
		
	speed = 125;
	dimensions.x = 70;
	dimensions.y = 70;

	switch (asteroidType)
	{
	case 0:	textureName = "asteroid1";	break;
	case 1:	textureName = "asteroid2";	break;
	case 2:	textureName = "asteroid3";	break;
	case 3:	textureName = "asteroid4";	break;
	}
	animationName = "rotation";

	lifetime = 15.f;
	animTimer = 0.2f;

	AsteroidSpawn();
}

void Asteroid::onCollision(GameObject & go, float distance)
{

}

void Asteroid::update()
{
	lifetime -= sfw::getDeltaTime();
	isAlive = lifetime > 0;
	animTimer += sfw::getDeltaTime();
	currentFrame = sampleAnimation(textureName, animationName, animTimer);

	position.x += trajectory.x * speed * sfw::getDeltaTime();
	position.y += trajectory.y * speed * sfw::getDeltaTime();
}

void Asteroid::draw(bool inLight)
{
	if (inLight)
	{
		if (light)
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0xffffffff);
		}
		else
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0xffffff30);
		}
	}
	else
	{
		if (light)
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0xffffff30);
		}
		else
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0xffffffff);
		}
	}
}

void Asteroid::AsteroidSpawn()
{
	int axis = rand() % 4;
	int rotationDirection = rand() % 2;
	int timerChange = rand() % 5;
	
	// Set trajectory
	float slopeX = (rand() % 175) + 275;
	slopeX = slopeX / 1000;
	float slopeY = 1 - slopeX;

	speed += rand() % 50;
	animTimer += timerChange * .1;
	
	if (lightShift == 0)
	{
		light = true;
		lightShift = 1;
	}
	else
	{
		light = false;
		lightShift = 0;
	}

	
	// Set random draw rotation
	if (rotationDirection == 0)
		targetAngle = rand() % 180;
	else
		targetAngle = -(rand() % 180);

	if (axis == 0)
	{
		position.x = -50;
		position.y = rand() % 900;

		if (position.y >= 450)
		{
			trajectory.x = slopeX;
			trajectory.y = -slopeY;
		}
		else if (position.y < 450)
		{
			trajectory.x = slopeX;
			trajectory.y = slopeY;
		}

	}
	else if (axis == 1)
	{
		position.x = 950;
		position.y = rand() % 900;

		if (position.y >= 450)
		{
			trajectory.x = -slopeX;
			trajectory.y = -slopeY;
		}
		else if (position.y < 450)
		{
			trajectory.x = -slopeX;
			trajectory.y = slopeY;
		}
	}
	else if (axis == 2)
	{
		position.x = rand() % 900;
		position.y = -50;
		
		if (position.x >= 450)
		{
			trajectory.x = -slopeX;
			trajectory.y = slopeY;
		}
		else if (position.y < 450)
		{
			trajectory.x = slopeX;
			trajectory.y = slopeY;
		}
	}
	else if (axis == 3)
	{
		position.x = rand() % 900;
		position.y = 950;

		if (position.x >= 450)
		{
			trajectory.x = -slopeX;
			trajectory.y = -slopeY;
		}
		else if (position.y < 450)
		{
			trajectory.x = slopeX;
			trajectory.y = -slopeY;
		}
	}
}