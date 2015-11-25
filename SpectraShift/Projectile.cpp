#include "GameObjects.h"
#include "GameState.h"
#include "Projectile.h"


Projectile::Projectile(float a_x, float a_y, float dx, float dy, float lifespan)
{
	
	
	textureName = "darkShot";
	animationName = "pulse";
	animTimer = .25f;
	
	speed = 500;
	
	position.x = a_x;
	position.y = a_y;

	trajectory.x = dx;
	trajectory.y = dy;

	dimensions.x = 25;
	dimensions.y = 25;

	lifetime = lifespan;
}

void Projectile::onCollision(GameObject & go, float distance)
{
	// we could react to collisions here
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
	sfw::drawTexture(GetTexture("bullet"), position.x, position.y, dimensions.x, dimensions.y, 0, true, currentFrame);
}
