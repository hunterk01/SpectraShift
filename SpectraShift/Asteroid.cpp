#include "GameObjects.h"
#include "GameState.h"
#include "Asteroid.h"
#include "Player.h"
#include "HUD.h"
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

int lightShift = 0, asteroidsDestroyed = 0, maxSpawnRate;

Asteroid::Asteroid()
{
	int asteroidType = rand() % 4;
	
	health = 50;
	speed = 120;
	dimensions.x = 70;
	dimensions.y = 70;
	radius = fmax(dimensions.x / 2, dimensions.y / 2) - 10;

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
	if (go.textureName == "lightShot" || go.textureName == "darkShot")
	{
		health -= 25;
		if (health <= 0)
		{
			if (light)
				lightEnergy += 10;
			else
				darkEnergy += 10;

			CalculateScore(75);

			trajectory.x = 0;
			trajectory.y = 0;
			dimensions.x = 80;
			dimensions.y = 80;
			animTimer = 1.5f;
			currentFrame = 0;
			textureName = "explosion";
			animationName = "bigBoom";
			PlaySound(TEXT("./Assets/Audio/explosion_asteroid.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
	else if (go.textureName == "playerShip" || go.textureName == "explosion")
	{
		trajectory.x = 0;
		trajectory.y = 0;
		dimensions.x = 80;
		dimensions.y = 80;
		animTimer = 1.5f;
		currentFrame = 0;
		textureName = "explosion";
		animationName = "bigBoom";
		PlaySound(TEXT("./Assets/Audio/explosion_asteroid.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
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

void Asteroid::draw()
{
	if (playerLight)
	{
		if (light)
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0xffffccff);
		}
		else
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0x66ccff30);
		}
	}
	else
	{
		if (light)
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0xffffcc40);
		}
		else
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame, 0x66ccffff);
		}
	}
}

void Asteroid::AsteroidSpawn()
{
	int axis = rand() % 4;
	int rotationDirection = rand() % 2;
	int timerChange = rand() % 5;
	
	// Set trajectory
	float slopeX = (rand() % 125) + 325;
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

	// Set spawn location outside the four screen edges
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