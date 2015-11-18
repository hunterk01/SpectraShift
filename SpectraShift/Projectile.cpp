#include "GameObjects.h"
#include "GameState.h"
#include "Projectile.h"


Projectile::Projectile(float a_x, float a_y, float dx, float dy, float lifespan)
{
	speed = 500;
	
	position.x = a_x;
	position.y = a_y;

	trajectory.x = dx;
	trajectory.y = dy;

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

	position.x += trajectory.x * speed * sfw::getDeltaTime();
	position.y += trajectory.y * speed * sfw::getDeltaTime();
}

void Projectile::draw()
{
	sfw::drawTexture(GetTexture("yellowBullet"), position.x, position.y, 20, 20, 0, true, 0);
}
