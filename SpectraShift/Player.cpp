#include "sfwdraw.h"
#include "Player.h"
#include "GameState.h"
#include "AssetLibrary.h"
#include "Background.h"
#include "Menu.h"
#include <math.h>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

float asteroidDelay = .5f, asteroidDelayTarget = 0, asteroidDelayMax = .25f;
bool playerLight = true, compassPointControls = true;
float lightEnergy = 100, darkEnergy = 100, healthTracker = 1000;
float energyGainDelay = .025f, energyGainTimer = 0, energyGainPoint = 3.f;

Player::Player()
{
	textureName = "playerShip";
	animationName = "flying";
	isAlive = true;
	light = playerLight;
	rateOfFire = .3f;
	fireDelay = rateOfFire;
	compassPointControls = true;
	position.x = 450;
	position.y = 450;
	dimensions.x = 50;
	dimensions.y = 45;
	radius = fmax(dimensions.x / 2, dimensions.y / 2) - 5;

	animTimer = 1.5f;
}

// Make player ship always point toward mouse position
void Player::SetPlayerAngles()
{
	// Get difference in player and mouse positions
	float dx = sfw::getMouseX() - position.x;
	float dy = sfw::getMouseY() - position.y;

	// Calculate rotation angle in degrees
	targetAngle = atan2f(dy, dx);
	targetAngle = targetAngle * (180 / PI);

	// Calculate perpendicular angle
	if (-90 > targetAngle && targetAngle > -180)
		perpAngle = targetAngle + 270;
	else
		perpAngle = targetAngle - 90;

	if (perpAngle < -180)
		perpAngle = -(perpAngle + 180);

	// **************** Target and perp angle output to console for debugging ***********
	//std::cout << "Target: " << targetAngle << "  Perp: " << perpAngle << std::endl << std::endl;
}

// Handle player movement with WASD keys
void Player::Movement()
{
	float deltaTime = sfw::getDeltaTime();
	float adjTargetAngle = 0.f, adjPerpAngle = 0.f;

	// Adjust target angle for angles greater than 90 degrees
	if (targetAngle > 90)
		adjTargetAngle = 180 - targetAngle;
	else if (targetAngle < -90)
		adjTargetAngle = -180 - targetAngle;
	else
		adjTargetAngle = targetAngle;

	// Adjust perp angle for angles greater than 90 degrees
	if (perpAngle > 90)
		adjPerpAngle = 180 - perpAngle;
	else if (perpAngle < -90)
		adjPerpAngle = -180 - perpAngle;
	else
		adjPerpAngle = perpAngle;

	// ****************  Adjusted angle output to console for debugging **************
	//std::cout << "adj Target: " << adjTargetAngle << "  adj Perp: " << adjPerpAngle << std::endl << std::endl;

	if (textureName != "explosion")
	{
		// Movement is always in up, down, left, right directions
		if (compassPointControls)
		{
			determineQuadrant();
			if (sfw::getKey(87) || sfw::getKey(83) || sfw::getKey(65) || sfw::getKey(68))
			{
				if (sfw::getKey(87)) // W
				{
					if (position.y < 850)
					{
						position.y = position.y + speed * deltaTime;
						lightSkyPos.y = lightSkyPos.y - (speed / 2.5) * deltaTime;
						darkSkyPos.y = darkSkyPos.y - (speed / 2.5) * deltaTime;
						starfieldPos.y = starfieldPos.y - (speed / 3) * deltaTime;
					}
					else
					{
						position.y = 850;
					}
				}
				if (sfw::getKey(65)) // A
				{
					if (position.x > 50)
					{
						position.x = position.x - speed * deltaTime;
						lightSkyPos.x = lightSkyPos.x + (speed / 2.5) * deltaTime;
						darkSkyPos.x = darkSkyPos.x + (speed / 2.5) * deltaTime;
						starfieldPos.x = starfieldPos.x + (speed / 3) * deltaTime;
					}
					else
					{
						position.x = 50;
					}
				}
				if (sfw::getKey(83)) // S
				{
					if (position.y > 50)
					{
						position.y = position.y - speed * deltaTime;
						lightSkyPos.y = lightSkyPos.y + (speed / 2.5) * deltaTime;
						darkSkyPos.y = darkSkyPos.y + (speed / 2.5) * deltaTime;
						starfieldPos.y = starfieldPos.y + (speed / 3) * deltaTime;
					}
					else
					{
						position.y = 50;
					}
				}
				if (sfw::getKey(68)) // D
				{
					if (position.x < 850)
					{
						position.x = position.x + speed * deltaTime;
						lightSkyPos.x = lightSkyPos.x - (speed / 2.5) * deltaTime;
						darkSkyPos.x = darkSkyPos.x - (speed / 2.5) * deltaTime;
						starfieldPos.x = starfieldPos.x - (speed / 3) * deltaTime;
					}
					else
					{
						position.x = 850;
					}
				}
			}
			else
			{
				trajectory.x = 0;
				trajectory.y = 0;
			}
		}

		// Movement is relative to the direction the player ship is facing
		else
		{
			float speedMod = 20;
			determineQuadrant();

			if (sfw::getKey(87) || sfw::getKey(83) || sfw::getKey(65) || sfw::getKey(68))
			{
				if (sfw::getKey(87)) // W
				{
					if (position.y < 850)
					{
						float targetDistance = sqrtf((position.x - sfw::getMouseX()) * (position.x - sfw::getMouseX())
							+ (position.y - sfw::getMouseY()) * (position.y - sfw::getMouseY()));

						if (targetDistance > 75)
						{
							trajectory.x = abs(cos((adjTargetAngle * PI) / 180));
							trajectory.y = abs(sin((adjTargetAngle * PI) / 180));

							applyVelocity(forwardQuadrant);
						}
					}
					else
					{
						position.y = 850;
					}
				}
				if (sfw::getKey(65)) // A
				{
					if (position.x > 50)
					{
						trajectory.x = abs(cos((adjPerpAngle * PI) / 180));
						trajectory.y = abs(sin((adjPerpAngle * PI) / 180));

						applyVelocity(leftQuadrant);
					}
					else
					{
						position.x = 50;
					}
				}
				if (sfw::getKey(83)) // S
				{
					if (position.y > 50)
					{
						trajectory.x = abs(cos((adjTargetAngle * PI) / 180));
						trajectory.y = abs(sin((adjTargetAngle * PI) / 180));

						applyVelocity(reverseQuadrant);
					}
					else
					{
						position.y = 50;
					}
				}
				if (sfw::getKey(68)) // D
				{
					if (position.x < 850)
					{
						trajectory.x = abs(cos((adjPerpAngle * PI) / 180));
						trajectory.y = abs(sin((adjPerpAngle * PI) / 180));

						applyVelocity(rightQuadrant);
					}
					else
					{
						position.x = 850;
					}
				}
			}
			else
			{
				trajectory.x = 0;
				trajectory.y = 0;
			}
		}

		fireWeapon(adjTargetAngle);
	}

	// ************  Trajectory output to console for debugging **************
	//std::cout << "Trajectory = { " << trajectory.x << ", " << trajectory.y << " }" << std::endl;

	asteroidDelay -= deltaTime;

	if (asteroidDelay <= asteroidDelayTarget)
	{
		gs()->makeAsteroid();
		asteroidDelay = .5f;
		if (asteroidDelayTarget < asteroidDelayMax)
			asteroidDelayTarget += .0005;
	}

	animTimer += sfw::getDeltaTime();
	currentFrame = sampleAnimation(textureName, animationName, animTimer);
}

void Player::determineQuadrant()
{
	// Calculate which quadrant each player direction is facing when in forward relative controls
	if (90 >= targetAngle && targetAngle >= 0)
	{
		forwardQuadrant = 1;
		leftQuadrant = 2;
		reverseQuadrant = 3;
		rightQuadrant = 4;
	}
	if (180 >= targetAngle && targetAngle > 90)
	{
		forwardQuadrant = 2;
		leftQuadrant = 3;
		reverseQuadrant = 4;
		rightQuadrant = 1;
	}
	if (-90 > targetAngle && targetAngle >= -180)
	{
		forwardQuadrant = 3;
		leftQuadrant = 4;
		reverseQuadrant = 1;
		rightQuadrant = 2;
	}
	if (0 >= targetAngle && targetAngle >= -90)
	{
		forwardQuadrant = 4;
		leftQuadrant = 1;
		reverseQuadrant = 2;
		rightQuadrant = 3;
	}
}

void Player::applyVelocity(int inQuadrant)
{
	float deltaTime = sfw::getDeltaTime();
	if (inQuadrant == 1)
	{
		if (position.x < 850)
		{
			position.x += trajectory.x * speed * deltaTime;

			lightSkyPos.x -= trajectory.x * (speed / 2) * deltaTime;
			darkSkyPos.x -= trajectory.x * (speed / 2) * deltaTime;
			starfieldPos.x -= trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 850;
		}
		
		if (position.y < 850)
		{
			position.y += trajectory.y * speed * deltaTime;

			lightSkyPos.y -= trajectory.y * (speed / 2) * deltaTime;
			darkSkyPos.y -= trajectory.y * (speed / 2) * deltaTime;
			starfieldPos.y -= trajectory.y * (speed / 3) * deltaTime;
		}
		else
		{
			position.y = 850;
		}
	}
	else if (inQuadrant == 2)
	{
		if (position.x > 50)
		{
			position.x -= trajectory.x * speed * deltaTime;

			lightSkyPos.x += trajectory.x * (speed / 2) * deltaTime;
			darkSkyPos.x += trajectory.x * (speed / 2) * deltaTime;
			starfieldPos.x += trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 50;
		}
	
		if (position.y < 850)
		{
			position.y += trajectory.y * speed * deltaTime;

			lightSkyPos.y -= trajectory.y * (speed / 2) * deltaTime;
			darkSkyPos.y -= trajectory.y * (speed / 2) * deltaTime;
			starfieldPos.y -= trajectory.y * (speed / 3) * deltaTime;
		}
		else
		{
			position.y = 850;
		}
	}
	else if (inQuadrant == 3)
	{
		if (position.x > 50)
		{
			position.x -= trajectory.x * speed * deltaTime;

			lightSkyPos.x += trajectory.x * (speed / 2) * deltaTime;
			darkSkyPos.x += trajectory.x * (speed / 2) * deltaTime;
			starfieldPos.x += trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 50;
		}

		if (position.y > 50)
		{
			position.y -= trajectory.y * speed * deltaTime;

			lightSkyPos.y += trajectory.y * (speed / 2) * deltaTime;
			darkSkyPos.y += trajectory.y * (speed / 2) * deltaTime;
			starfieldPos.y += trajectory.y * (speed / 3) * deltaTime;
		}
		else
		{
			position.y = 50;
		}
	}
	else if (inQuadrant == 4)
	{
		if (position.x < 850)
		{
			position.x += trajectory.x * speed * deltaTime;

			lightSkyPos.x -= trajectory.x * (speed / 2) * deltaTime;
			darkSkyPos.x -= trajectory.x * (speed / 2) * deltaTime;
			starfieldPos.x -= trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 850;
		}

		if (position.y > 50)
		{
			position.y -= trajectory.y * speed * deltaTime;

			lightSkyPos.y += trajectory.y * (speed / 2) * deltaTime;
			darkSkyPos.y += trajectory.y * (speed / 2) * deltaTime;
			starfieldPos.y += trajectory.y * (speed / 3) * deltaTime;
		}
		else
		{
			position.y = 50;
		}
	}
}

void Player::fireWeapon(float inAdjTargetAngle)
{
	float bulletTrajectoryX, bulletTrajectoryY, energyPerShot = 4;
	
	fireDelay -= sfw::getDeltaTime();

	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && fireDelay < 0)
	{
		if ((playerLight && darkEnergy >= energyPerShot) || (!playerLight && lightEnergy >= energyPerShot))
		{
			float mouseX, mouseY;
			fireDelay = rateOfFire;

			if (playerLight)
				darkEnergy -= energyPerShot;
			else
				lightEnergy -= energyPerShot;

			bulletTrajectoryX = abs(cos((inAdjTargetAngle * PI) / 180));
			bulletTrajectoryY = abs(sin((inAdjTargetAngle * PI) / 180));

			if (forwardQuadrant == 1)
				gs()->makeBullet(position.x, position.y, bulletTrajectoryX, bulletTrajectoryY, 2.f);
			else if (forwardQuadrant == 2)
				gs()->makeBullet(position.x, position.y, -bulletTrajectoryX, bulletTrajectoryY, 2.f);
			else if (forwardQuadrant == 3)
				gs()->makeBullet(position.x, position.y, -bulletTrajectoryX, -bulletTrajectoryY, 2.f);
			else if (forwardQuadrant == 4)
				gs()->makeBullet(position.x, position.y, bulletTrajectoryX, -bulletTrajectoryY, 2.f);

			PlaySound(TEXT("./Assets/Audio/weapon_player.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
}

void Player::energyGain()
{
	if (energyGainTimer >= energyGainPoint)
	{
		if (playerLight)
		{
			lightEnergy += 5;
			energyGainTimer = 0;
		}
		else
		{
			darkEnergy += 5;
			energyGainTimer = 0;
		}
	}
	energyGainTimer += energyGainDelay;
}

void Player::onCollision(GameObject & go, float distance)
{
	if (go.textureName == "asteroid1" || go.textureName == "asteroid2" || go.textureName == "asteroid3" || go.textureName == "asteroid4")
	{
		healthTracker -= 200;
		if (healthTracker <= 0)
		{
			trajectory.x = 0;
			trajectory.y = 0;
			dimensions.x = 70;
			dimensions.y = 70;
			currentFrame = 0;
			animTimer = 1.5f;
			textureName = "explosion";
			animationName = "bigBoom";
			PlaySound(TEXT("./Assets/Audio/explosion_player.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
	}
}

void Player::draw()
{
	sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame);
}




