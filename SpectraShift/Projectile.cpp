#include "GameObjects.h"
#include "GameState.h"
#include "Projectile.h"
#include "Player.h"

Projectile::Projectile(float a_x, float a_y, float dx, float dy, float lifespan)
{
	if (playerLight)
	{
		textureName = "darkShot";
		light = true;
	}
	else
	{
		textureName = "lightShot";
		light = false;
	}

	isAlive = true;
	animationName = "pulse";
	animTimer = .25f;
	speed = 500;
	dimensions.x = 25;
	dimensions.y = 25;
	radius = fmax(dimensions.x / 2, dimensions.y / 2) - 7;
	position.x = a_x;
	position.y = a_y;
	trajectory.x = dx;
	trajectory.y = dy;
	lifetime = lifespan;
}

void Projectile::onCollision(GameObject & go, float distance)
{
	if (light)
	{
		textureName = "darkBulletHit";
	}
	else
	{
		textureName = "lightBulletHit";
	}
	
	animationName = "smallBoom";
	trajectory.x = 0;
	trajectory.y = 0;
	dimensions.x = 30;
	dimensions.y = 30;
	animTimer = .25f;
}

void Projectile::update()
{
	lifetime -= sfw::getDeltaTime();
	isAlive = lifetime > 0;
	animTimer += sfw::getDeltaTime();
	currentFrame = sampleAnimation(textureName, animationName, animTimer);

	position.x += trajectory.x * speed * sfw::getDeltaTime();
	position.y += trajectory.y * speed * sfw::getDeltaTime();
}

void Projectile::draw()
{
	if (playerLight)
	{
		if (light)
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, 0, true, currentFrame, 0xffffffff);
		}
		else
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, 0, true, currentFrame, 0xffffff30);
		}
		}
	else
	{
		if (!light)
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, 0, true, currentFrame, 0xffffffff);
		}
		else
		{
			sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, 0, true, currentFrame, 0xffffff40);
		}
	}
}
