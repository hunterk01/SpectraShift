#pragma once

class MenuState
{
public:
	vec2 TitleStarsPosA, TitleNeb1PosA, TitleNeb2PosA, TitleStarsPosB, TitleNeb1PosB, TitleNeb2PosB, TitlePosition;

	bool moveTitle, showMenu, drawCredits, drawQuit, drawStart, drawControls, drawInstructions, menuOpen,
		instructionsOpen, controlsOpen, quitOpen, creditsOpen, exitGame, gameOn;

	float buttonDelay, deltaTime;

	MenuState();

	void Draw();
	void DrawMenu();
	void DrawInstructions();
	void DrawControls();
	void DrawCredits();
	void QuitGame();
};
