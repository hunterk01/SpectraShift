#include "GameState.h"
#include "Player.h"
#include "Projectile.h"
#include <vector>

void GameState::makeBullet(float x, float y, float dx, float dy, float lifespan)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (!bullets[i].isAlive) // Find an empty spot in our vector
		{
			bullets[i] = Projectile(x, y, dx, dy, lifespan);
			return;
		}
	}
	// if there is no empty spot, generate a new bullet into the vector
	bullets.push_back(Projectile(x, y, dx, dy, lifespan));
}

void GameState::makeExplosion()
{

}

void GameState::makeEnemy()
{

}

void GameState::makeAsteroid()
{

}



GameState::GameState()
{
	// Setup the gamestate pointer that all of the gameobjects share!
	GameObject::gs() = this;
}

// Update objects, check for collision,
// respond to events or special logic that changes how the game plays (ie. player is dead)
void GameState::update()
{
	if (player.isAlive)
	{
		player.SetPlayerAngles();
		player.Movement();
	}

	// example useful for determining when to spawn a new wave of enemies.
	int nBulletsActive = 0;

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].isAlive)
		{
			bullets[i].update();
			if (player.isAlive)
				doCollision(player, bullets[i]);
		}
		else nBulletsActive++;
	}
	
	if (nBulletsActive == 0)
	{
		// Spawn a new wave of enemies (obviously not using Bullets >__>)
	}

	// Collision detection between two objects of the same type
	for (int i = 0; i + 1 < bullets.size(); ++i)
		for (int j = i + 1; j < bullets.size(); ++j)
		{
			doCollision(bullets[i], bullets[j]);
		}
}
	// DRaw everything now!
void GameState::draw()
{
	if (player.isAlive)
	{
		sfw::drawTexture(GetTexture("playerShip"), player.position.x, player.position.y, 54, 60, player.targetAngle, true, 0);
		sfw::drawTexture(GetTexture("target"), sfw::getMouseX(), sfw::getMouseY(), 20, 20, player.targetAngle, true, 0);
	}

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].isAlive)
			bullets[i].draw();
	}
}

// Needs some way to 'spawn/destroy' bullets/enemies.
// Changes in gameplay happen here.


