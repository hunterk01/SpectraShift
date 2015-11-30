#include <Windows.h>
#include "sfwdraw.h"
#include "GameObjects.h"
#include "AssetLibrary.h"
#include "Menu.h"
#include "Player.h"

MenuState::MenuState()
{
	TitleStarsPosA = { 0, 950 };
	TitleNeb1PosA = { 0, 950 };
	TitleNeb2PosA = { 0, 950 };
	TitleStarsPosB = { 1200, 950 };
	TitleNeb1PosB = { 3004, 950 };
	TitleNeb2PosB = { 2666, 950 };
	TitlePosition = { 450,450 };

	moveTitle = false, showMenu = true, drawCredits = false, drawQuit = false, drawStart = false, drawControls = false,
	drawInstructions = false, menuOpen = false, instructionsOpen = false, controlsOpen = false, quitOpen = false,
	creditsOpen = false, exitGame = false, gameOn = false;;

	buttonDelay = 1.f;
}


void MenuState::Draw()
{
	float deltaTime = sfw::getDeltaTime();

	sfw::drawTexture(GetTexture("BG_stars"), TitleStarsPosA.x, TitleStarsPosA.y, 1200, 1200, 0, false, 0, 0xffffffff);
	sfw::drawTexture(GetTexture("BG_stars"), TitleStarsPosB.x, TitleStarsPosB.y, 1200, 1000, 0, false, 0, 0xffffffff);
	sfw::drawTexture(GetTexture("TitleBG1"), TitleNeb1PosA.x, TitleNeb1PosA.y, 3004, 1000, 0, false, 0, 0xffffff45);
	sfw::drawTexture(GetTexture("TitleBG1"), TitleNeb1PosB.x, TitleNeb1PosB.y, 3004, 1000, 0, false, 0, 0xffffff45);
	sfw::drawTexture(GetTexture("TitleBG2"), TitleNeb2PosB.x, TitleNeb1PosB.y, 2666, 1000, 0, false, 0, 0xffff0045);
	sfw::drawTexture(GetTexture("TitleBG2"), TitleNeb2PosA.x, TitleNeb2PosA.y, 2666, 1000, 0, false, 0, 0xffff0045);

	sfw::drawTexture(GetTexture("target"), sfw::getMouseX(), sfw::getMouseY(), 20, 20, 0, true, 0);
	sfw::drawTexture(GetTexture("title"), TitlePosition.x, TitlePosition.y, 800, 106, 0, true, 0);

	TitleStarsPosA.x -= 25 * deltaTime;
	TitleStarsPosB.x -= 25 * deltaTime;
	TitleNeb1PosA.x -= 45 * deltaTime;
	TitleNeb1PosB.x -= 45 * deltaTime;
	TitleNeb2PosA.x -= 80 * deltaTime;
	TitleNeb2PosB.x -= 80 * deltaTime;

	if (TitleStarsPosA.x <= -1200)	TitleStarsPosA.x = 1200;
	if (TitleStarsPosB.x <= -1200)	TitleStarsPosB.x = 1200;
	if (TitleNeb1PosA.x <= -3004)	TitleNeb1PosA.x = 3004;
	if (TitleNeb1PosB.x <= -3004)	TitleNeb1PosB.x = 3004;
	if (TitleNeb2PosA.x <= -2666)	TitleNeb2PosA.x = 2666;
	if (TitleNeb2PosB.x <= -2666)	TitleNeb2PosB.x = 2666;

	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT))	moveTitle = true;
	
	if (moveTitle)
	{
		TitlePosition.y += 100 * deltaTime;
		menuOpen = true;
	}

	DrawMenu();

	if (TitlePosition.y >= 525)		drawCredits = true;
	if (TitlePosition.y >= 575)		drawQuit = true;
	if (TitlePosition.y >= 625)		drawStart = true;
	if (TitlePosition.y >= 675)		drawControls = true;
	if (TitlePosition.y >= 725)		drawInstructions = true;
	if (TitlePosition.y >= 750)
	{
		TitlePosition.y = 750;
		moveTitle = false;
	}
}

void MenuState::DrawMenu()
{
	float mouseX = 0, mouseY = 0;
	
	if (menuOpen)
	{
		if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && drawInstructions)
		{
			mouseX = sfw::getMouseX();
			mouseY = sfw::getMouseY();
		}

		if (showMenu)
		{
			if (drawInstructions)	sfw::drawTexture(GetTexture("instructions"), 450, 625, 461, 65, 0, true, 0);
			if (drawControls)		sfw::drawTexture(GetTexture("controls"), 450, 525, 357, 65, 0, true, 0);
			if (drawStart)			sfw::drawTexture(GetTexture("start"), 450, 425, 425, 63, 0, true, 0);
			if (drawQuit)			sfw::drawTexture(GetTexture("quit"), 450, 325, 381, 63, 0, true, 0);
			if (drawCredits)		sfw::drawTexture(GetTexture("credits"), 450, 225, 272, 63, 0, true, 0);


			// Handle click on Controls and function call
			if (669.5 > mouseX && mouseX > 219.5 && 657.5 > mouseY && mouseY > 592.5 && !instructionsOpen)
			{
				showMenu = false;
				instructionsOpen = true;
			}
			// Handle mouse click on Controls button
			else if (628.5 > mouseX && mouseX > 271.5 && 557.5 > mouseY && mouseY > 492.5 && !controlsOpen)
			{
				showMenu = false;
				controlsOpen = true;
			}
			// Handle mouse click on Start button
			else if (662.5 > mouseX && mouseX > 237.5 && 456.5 > mouseY && mouseY > 393.5)
			{
				gameOn = true;
			}
			// Handle mouse click on Quit button
			else if (640.5 > mouseX && mouseX > 259.5 && 356.5 > mouseY && mouseY > 293.5 && !quitOpen)
			{
				showMenu = false;
				quitOpen = true;
			}
			// Handle mouse click on Credits button
			else if (586 > mouseX && mouseX > 314 && 256.5 > mouseY && mouseY > 193.5 && !creditsOpen)
			{
				showMenu = false;
				creditsOpen = true;
			}
		}

		if (instructionsOpen)	DrawInstructions();
		if (controlsOpen)		DrawControls();
		if (quitOpen)			QuitGame();
		if (creditsOpen)		DrawCredits();
	}
}

void MenuState::DrawInstructions()
{
	float mouseX = 0, mouseY = 0;
	
	sfw::drawTexture(GetTexture("instructionText"), 450, 550, 640, 243, 0, true, 0);
	sfw::drawTexture(GetTexture("back"), 700, 200, 113, 40, 0, true, 0);

	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT))
	{
		mouseX = sfw::getMouseX();
		mouseY = sfw::getMouseY();
	}

	if (755.5 > mouseX && mouseX > 644.5 && 220 > mouseY && mouseY > 180)
	{
		showMenu = true;
		instructionsOpen = false;
	}
}

void MenuState::DrawControls()
{
	float mouseX = 0, mouseY = 0;
	
	sfw::drawTexture(GetTexture("targetText"), 450, 600, 630, 159, 0, true, 0);
	sfw::drawTexture(GetTexture("forward"), 405, 500, 415, 41, 0, true, 0);
	sfw::drawTexture(GetTexture("forwardText"), 455, 400, 640, 148, 0, true, 0);
	sfw::drawTexture(GetTexture("compass"), 357, 300, 319, 39, 0, true, 0);
	sfw::drawTexture(GetTexture("compassText"), 450, 220, 630, 118, 0, true, 0);
	sfw::drawTexture(GetTexture("back"), 700, 125, 113, 40, 0, true, 0);

	// Draw check boxes
	sfw::drawLine(150, 520, 190, 520);
	sfw::drawLine(150, 480, 190, 480);
	sfw::drawLine(150, 480, 150, 520);
	sfw::drawLine(190, 480, 190, 520);
	sfw::drawLine(150, 320, 190, 320);
	sfw::drawLine(150, 280, 190, 280);
	sfw::drawLine(150, 280, 150, 320);
	sfw::drawLine(190, 280, 190, 320);

	// Draw X
	if (!compassPointControls)
	{
		sfw::drawTexture(GetTexture("Xmark"), 170, 500, 35, 35, 0, true, 0);
	}
	else
	{
		sfw::drawTexture(GetTexture("Xmark"), 170, 300, 35, 35, 0, true, 0);
	}

	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT))
	{
		mouseX = sfw::getMouseX();
		mouseY = sfw::getMouseY();
	}

	if (190 > mouseX && mouseX > 150 && 520 > mouseY && mouseY > 480)
	{
		compassPointControls = false;
	}
	else if (190 > mouseX && mouseX > 150 && 320 > mouseY && mouseY > 280)
	{
		compassPointControls = true;
	}
	else if (755.5 > mouseX && mouseX > 644.5 && 145 > mouseY && mouseY > 105)
	{
		showMenu = true;
		controlsOpen = false;
	}
}

void MenuState::DrawCredits()
{
	float mouseX = 0, mouseY = 0;
	
	sfw::drawTexture(GetTexture("creditsText"), 450, 450, 444, 435, 0, true, 0);
	sfw::drawTexture(GetTexture("back"), 700, 200, 113, 40, 0, true, 0);

	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT))
	{
		mouseX = sfw::getMouseX();
		mouseY = sfw::getMouseY();
	}

	if (755.5 > mouseX && mouseX > 644.5 && 220 > mouseY && mouseY > 180)
	{
		showMenu = true;
		creditsOpen = false;
	}
}

void MenuState::QuitGame()
{
	deltaTime = sfw::getDeltaTime();

	sfw::drawTexture(GetTexture("thanks"), 450, 450, 800, 59, 0, true, 0);

	if (sfw::getMouseButton(MOUSE_BUTTON_LEFT) && buttonDelay < 0)
	{
		exitGame = true;
		gameOn = false;
	}
	
	buttonDelay -= deltaTime;
}