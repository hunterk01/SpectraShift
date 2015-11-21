#include "sfwdraw.h"
#include "GameObjects.h"
#include "AssetLibrary.h"
#include "Menu.h"

vec2 TitleStarsPosA = { 0, 950 };
vec2 TitleNeb1PosA = { 0, 950 };
vec2 TitleNeb2PosA = { 0, 950 };
vec2 TitleStarsPosB = { 1200, 950 };
vec2 TitleNeb1PosB = { 3004, 950 };
vec2 TitleNeb2PosB = { 2666, 950 };
vec2 TitlePosition = { 450,450 };

bool moveTitle = false, drawCredits = false, drawQuit = false, drawStart = false, drawControls = false, 
		drawInstructions = false, menuOpen = false, instructionsOpen = false, controlsOpen = false, quitOpen = false,
		creditsOpen = false;

void DrawTitleScreen()
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

void DrawMenu()
{
	float mouseX = 0, mouseY = 0;
	
	if (menuOpen)
	{
		if (sfw::getMouseButton(MOUSE_BUTTON_LEFT))
		{
			mouseX = sfw::getMouseX();
			mouseY = sfw::getMouseY();
		}

		if (drawInstructions)	sfw::drawTexture(GetTexture("instructions"), 450, 625, 461, 65, 0, true, 0);
		if (drawControls)		sfw::drawTexture(GetTexture("controls"), 450, 525, 357, 65, 0, true, 0);
		if (drawStart)			sfw::drawTexture(GetTexture("start"), 450, 425, 425, 63, 0, true, 0);
		if (drawQuit)			sfw::drawTexture(GetTexture("quit"), 450, 325, 381, 63, 0, true, 0);
		if (drawCredits)		sfw::drawTexture(GetTexture("credits"), 450, 225, 272, 63, 0, true, 0);

		// Handle click on Controls and function call
		if (669.5 > mouseX && mouseX > 219.5 && 657.5 > mouseY && mouseY > 592.5)
		{
			menuOpen = false;
			instructionsOpen = true;
		}
		// Handle mouse click on Controls button
		else if (628.5 > mouseX && mouseX > 271.5 && 557.5 > mouseY && mouseY > 492.5)
		{
			menuOpen = false;
			controlsOpen = true;
		}
		// Handle mouse click on Start button
		else if (662.5 > mouseX && mouseX > 237.5 && 456.5 > mouseY && mouseY > 393.5)
		{
			menuOpen = false;

		}
		// Handle mouse click on Quit button
		else if (640.5 > mouseX && mouseX > 259.5 && 356.5 > mouseY && mouseY > 293.5)
		{
			menuOpen = false;
			quitOpen = true;
		}
		// Handle mouse click on Credits button
		else if (586 > mouseX && mouseX > 314 && 256.5 > mouseY && mouseY > 193.5)
		{
			menuOpen = false;
			creditsOpen = true;
		}

		if (instructionsOpen)	DrawInstructions();
		if (controlsOpen)		DrawControls();
		if (quitOpen)			QuitGame();
		if (creditsOpen)		DrawCredits();
	}
}

void DrawInstructions()
{
	// Draw Instructions

	// Draw back button and handle click condition
}

void DrawControls()
{
	// Draw target reticle info
	
	sfw::drawTexture(GetTexture("forward"), 500, 550, 415, 41, 0, true, 0);
	// Draw control scheme info

	sfw::drawTexture(GetTexture("compass"), 452, 400, 319, 39, 0, true, 0);
	// Draw control scheme info

	sfw::drawTexture(GetTexture("back"), 700, 200, 113, 40, 0, true, 0);
	// Handle click on back button
}

void DrawCredits()
{
	// Draw credits list

	// Draw "Back" button
	// Handle click on back button
}


void QuitGame()
{
	// Draw "Thanks" screen
	// Handle exit on click
}