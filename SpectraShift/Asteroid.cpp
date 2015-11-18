#include "GameObjects.h"
#include "GameState.h"
#include "Asteroid.h"
#include <time.h>


Asteroid::Asteroid(float a_x, float a_y, float dx, float dy, float lifespan)
{
	srand(time(NULL));
	
	speed = 400;
	dimensions.x = 50;
	dimensions.y = 50;
	animationName = "rotation";

	position.x = a_x;
	position.y = a_y;

	trajectory.x = dx;
	trajectory.y = dy;

	lifetime = lifespan;
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

void Asteroid::draw()
{
	sfw::drawTexture(GetTexture("asteroid1"), 250, 250, dimensions.x, dimensions.y, 0, true, currentFrame);
}

void AsteroidSpawn()
{
	int axis = rand() % 1;
	int spawnPoint = rand() % 980;


	if (axis == 0)
	{

	}
	else
	{

	}
}