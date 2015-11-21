#include "GameState.h"
#include "Player.h"
#include "Projectile.h"
#include "Asteroid.h"
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

void GameState::makeAsteroids(float x, float y, float dx, float dy, float lifespan)
{
	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (!asteroids[i].isAlive) // Find an empty spot in our vector
		{
			asteroids[i] = Asteroid(x, y, dx, dy, lifespan);
			return;
		}
	}
	// if there is no empty spot, generate a new bullet into the vector
	asteroids.push_back(Asteroid(x, y, dx, dy, lifespan));
}

void GameState::makeExplosion()
{

}

void GameState::makeEnemy()
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

	// Bullet spawn control
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
	
	// Asteroid spawn control
	int nAsteroidsActive = 0;
	
	if (nAsteroidsActive == 0)
	{
		for (int i = 0; i < asteroids.size(); ++i)
		{
			if (asteroids[i].isAlive)
			{
				asteroids[i].update();
				if (player.isAlive)
					doCollision(player, asteroids[i]);
			}
			else nAsteroidsActive++;
		}
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
		sfw::drawTexture(GetTexture("playerShip"), player.position.x, player.position.y, 50, 45, player.targetAngle, true, 0);
		sfw::drawTexture(GetTexture("target"), sfw::getMouseX(), sfw::getMouseY(), 20, 20, player.targetAngle, true, 0);
	}

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].isAlive)
			bullets[i].draw();
	}

	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (asteroids[i].isAlive)
			asteroids[i].draw();
	}
}

// Needs some way to 'spawn/destroy' bullets/enemies.
// Changes in gameplay happen here.


