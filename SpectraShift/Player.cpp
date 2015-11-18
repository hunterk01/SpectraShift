#include "sfwdraw.h"
#include "Player.h"
#include "GameState.h"
#include "AssetLibrary.h"
#include "Background.h"
#include <math.h>
#include <iostream>

bool compassPointControls = false;

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

	// Movement is always in up, down, left, right directions
	if (compassPointControls)
	{
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
					trajectory.x = abs(cos((adjTargetAngle * PI) / 180));
					trajectory.y = abs(sin((adjTargetAngle * PI) / 180));
					
					applyVelocity(forwardQuadrant);
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

	
	// ************  Trajectory output to console for debugging **************
	//std::cout << "Trajectory = { " << trajectory.x << ", " << trajectory.y << " }" << std::endl;

	// Control for firing projectiles
	fireDelay -= sfw::getDeltaTime();
	
	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && fireDelay < 0)
	{
		fireDelay = rateOfFire;
		gs()->makeBullet(position.x, position.y, sfw::getMouseX(), sfw::getMouseY(), 2.f);
	}


}

void Player::determineQuadrant()
{
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

			lightSkyPos.x -= trajectory.x * (speed / 2.5) * deltaTime;
			darkSkyPos.x -= trajectory.x * (speed / 2.5) * deltaTime;
			starfieldPos.x -= trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 850;
		}
		
		if (position.y < 850)
		{
			position.y += trajectory.y * speed * deltaTime;

			lightSkyPos.y -= trajectory.y * (speed / 2.5) * deltaTime;
			darkSkyPos.y -= trajectory.y * (speed / 2.5) * deltaTime;
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

			lightSkyPos.x += trajectory.x * (speed / 2.5) * deltaTime;
			darkSkyPos.x += trajectory.x * (speed / 2.5) * deltaTime;
			starfieldPos.x += trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 50;
		}
	
		if (position.y < 850)
		{
			position.y += trajectory.y * speed * deltaTime;

			lightSkyPos.y -= trajectory.y * (speed / 2.5) * deltaTime;
			darkSkyPos.y -= trajectory.y * (speed / 2.5) * deltaTime;
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

			lightSkyPos.x += trajectory.x * (speed / 2.5) * deltaTime;
			darkSkyPos.x += trajectory.x * (speed / 2.5) * deltaTime;
			starfieldPos.x += trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 50;
		}

		if (position.y > 50)
		{
			position.y -= trajectory.y * speed * deltaTime;

			lightSkyPos.y += trajectory.y * (speed / 2.5) * deltaTime;
			darkSkyPos.y += trajectory.y * (speed / 2.5) * deltaTime;
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

			lightSkyPos.x -= trajectory.x * (speed / 2.5) * deltaTime;
			darkSkyPos.x -= trajectory.x * (speed / 2.5) * deltaTime;
			starfieldPos.x -= trajectory.x * (speed / 3) * deltaTime;
		}
		else
		{
			position.x = 850;
		}

		if (position.y > 50)
		{
			position.y -= trajectory.y * speed * deltaTime;

			lightSkyPos.y += trajectory.y * (speed / 2.5) * deltaTime;
			darkSkyPos.y += trajectory.y * (speed / 2.5) * deltaTime;
			starfieldPos.y += trajectory.y * (speed / 3) * deltaTime;
		}
		else
		{
			position.y = 50;
		}
	}
}