#include <iostream>
#include "sfwdraw.h"
#include "AssetLibrary.h"
#include "GameState.h"
#include "GameObjects.h"
#include "Menu.h"
#include "Player.h"
#include "Background.h"
#include "HUD.h"
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>

void main()
{
	srand(time(NULL));
	sfw::initContext(900, 900, "Spectra Shift");
	sfw::setBackgroundColor(BLACK);

	MenuState menu;
	GameState game;

	LoadAllTextures();

	while (!menu.exitGame)
	{
		while (sfw::stepContext())
		{
			if (!menu.gameOn)
			{
				menu.Draw();
			}
			else
			{
				DrawBackground();
				game.update();
				game.draw();

				// Draw HUD
				DrawMeters(0);
				DrawHUD();
				DrawScore();
			}
			if (menu.exitGame)
			{
				sfw::termContext();
			}
			if (game.resetGame)
			{
				menu.gameOn = false;
				menu.quitOpen = true;
				menu.showMenu = false;
			}
		}
	}
}