#include "GameState.h"
#include "Player.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "HUD.h"
#include <vector>

GameState::GameState()
{
	GameObject::gs() = this;
}

void GameState::makeBullet(float x, float y, float dx, float dy, float lifespan)
{
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (!bullets[i].isAlive)
		{
			bullets[i] = Projectile(x, y, dx, dy, lifespan);
			return;
		}
	}
	bullets.push_back(Projectile(x, y, dx, dy, lifespan));
}

void GameState::makeAsteroid()
{
	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (!asteroids[i].isAlive)
		{
			asteroids[i] = Asteroid();
			return;
		}
	}
	asteroids.push_back(Asteroid());
}

void GameState::update()
{
	// Asteroid movement and collision control
	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (asteroids[i].isAlive)
		{
			asteroids[i].update();

			if (player.isAlive && asteroids[i].textureName != "explosion")
			{
				if (playerLight && asteroids[i].light)
				{
					doCollision(player, asteroids[i]);
				}
				else if (!playerLight && !asteroids[i].light)
				{
					doCollision(player, asteroids[i]);
				}
			}
		}
	}

	// Bullet movement and collision control
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].isAlive)
		{
			bullets[i].update();

			if (bullets[i].light)
			{
				for (int j = 0; j < asteroids.size(); ++j)
				{
					if (asteroids[j].isAlive && asteroids[j].light && asteroids[j].textureName != "explosion")
						doCollision(asteroids[j], bullets[i]);
				}
			}
			else
			{
				for (int j = 0; j < asteroids.size(); ++j)
				{
					if (asteroids[j].isAlive && !asteroids[j].light && asteroids[j].textureName != "explosion")
						doCollision(asteroids[j], bullets[i]);
				}
			}
		}
	}

	// Player movement and energy control
	if (player.isAlive)
	{
		player.SetPlayerAngles();
		player.Movement();
		player.energyGain();
	}
}

void GameState::draw()
{
	// Draw asteroids
	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (asteroids[i].isAlive)
			asteroids[i].draw();

		if (asteroids[i].textureName == "explosion")
		{
			if (asteroids[i].currentFrame == 14)
				asteroids[i].isAlive = false;
		}
	}
	
	// Draw bullets
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (bullets[i].isAlive)
			bullets[i].draw();

		if (bullets[i].textureName == "lightBulletHit")
		{
			if (bullets[i].currentFrame == 27)
				bullets[i].isAlive = false;
		}
		else if (bullets[i].textureName == "darkBulletHit")
		{
			if (bullets[i].currentFrame == 81)
				bullets[i].isAlive = false;
		}
	}

	// Draw player
	if (player.isAlive)
	{
		player.draw();

		if (player.currentFrame == 14)
			player.isAlive = false;
	}
	else
	{
		float deltaTime = sfw::getDeltaTime();

		sfw::drawTexture(GetTexture("gameOver"), 450, 450, 428, 68, 0, true, 0);

		if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && buttonDelay < 0)
		{
			resetGame = true;
		}

		buttonDelay -= deltaTime;
	}

	// Draw target reticle
	sfw::drawTexture(GetTexture("target"), sfw::getMouseX(), sfw::getMouseY(), 20, 20, player.targetAngle, true, 0);
}



