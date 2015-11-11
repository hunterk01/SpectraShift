#include <iostream>
#include "sfwdraw.h"
#include "AssetLibrary.h"
#include "GameObjects.h"
#include "Menu.h"
#include "Player.h"
#include "Background.h"
#include "HUD.h"

bool exitGame = false, gameOn = false;


void main()
{

	sfw::initContext(900, 900, "Spectra Shift");
	sfw::setBackgroundColor(BLACK);

	void LoadAllTextures();

	while (!exitGame)
	{
		while(gameOn)
		{
			while (sfw::stepContext())
			{
				DrawBackground();
				
				// ***** Print player and mouse positions to console *****
				//std::cout << "{ " << player.position.x << ", " << player.position.y << " }" << std::endl;
				//std::cout << "{ " << sfw::getMouseX() << ", " << sfw::getMouseY() << " }" << std::endl;


				// Draw HUD
				DrawMeters(0, 0, 0);
				DrawHUD();
				DrawScore();

				// Test: Add values to score
				if (sfw::getKey(49))
					CalculateScore(5);
				if (sfw::getKey(50))
					CalculateScore(50);
				if (sfw::getKey(51))
					CalculateScore(125);

				// Test: Meter pointer movement
				if (sfw::getKey(89))
					DrawMeters(5, 0, 0);
				if (sfw::getKey(72))
					DrawMeters(-5, 0, 0);
				if (sfw::getKey(85))
					DrawMeters(0, 5, 0);
				if (sfw::getKey(74))
					DrawMeters(0, -5, 0);
				if (sfw::getKey(73))
					DrawMeters(0, 0, 5);
				if (sfw::getKey(75))
					DrawMeters(0, 0, -5);

			}

		}

	}
}