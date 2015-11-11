#include "sfwdraw.h"
#include "Player.h"
#include "GameObjects.h"
#include "AssetLibrary.h"
#include <math.h>

Player player;

bool compassPointControls = true;

void Player::Movement(vec2 & lightSkyPos, vec2 & darkSkyPos, vec2 & starfieldPos)
{
	if (compassPointControls)
	{
		if (sfw::getKey(87) || sfw::getKey(83) || sfw::getKey(65) || sfw::getKey(68))
		{
			float deltaTime = sfw::getDeltaTime();

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
			velocity.x = 0;
			velocity.y = 0;
		}
	}
	else
	{
		if (sfw::getKey(87) || sfw::getKey(83) || sfw::getKey(65) || sfw::getKey(68))
		{
			float deltaTime = sfw::getDeltaTime();

			if (sfw::getKey(87)) // W
			{
				if (position.y < 850)
				{
					position.x += speed * sin(targetAngle) * deltaTime;
					position.y += speed * cos(targetAngle) * deltaTime;
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
					position.x -= speed * sin(perpAngle) * deltaTime;
					position.y -= speed * cos(perpAngle) * deltaTime;
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
					position.x -= speed * sin(targetAngle) * deltaTime;
					position.y -= speed * cos(targetAngle) * deltaTime;
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
					position.x += speed * cos(perpAngle) * deltaTime;
					position.y += speed * sin(perpAngle) * deltaTime;
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
			velocity.x = 0;
			velocity.y = 0;
		}
	}
}



// Reference for player movement and mouse targeting
// sfw::drawTexture(playerShip, player.position.x, player.position.y, 54, 60, player.targetAngle, true, 0);
// sfw::drawTexture(target, sfw::getMouseX(), sfw::getMouseY(), 20, 20, player.targetAngle, true, 0);