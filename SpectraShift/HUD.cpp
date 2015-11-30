#include "sfwdraw.h"
#include "HUD.h"
#include "AssetLibrary.h"
#include "Player.h"
#include <map>
#include <fstream>

int scoreValues[7] = { 0,0,0,0,0,0 };
float healthPosY, lightPosY, darkPosY;
bool hudTexturesLoaded = false;

void DrawMeters(float inHealth)
{
	healthTracker += inHealth;

	// Set upper and lower bounds
	if (healthTracker < 0)		healthTracker = 0;
	if (healthTracker > 1000)	healthTracker = 1000;
	if (lightEnergy < 0)		lightEnergy = 0;
	if (lightEnergy > 100)		lightEnergy = 100;
	if (darkEnergy < 0)			darkEnergy = 0;
	if (darkEnergy > 100)		darkEnergy = 100;

	// Set value meter pointer positions
	healthPosY = (healthTracker * 0.090) + 10;
	lightPosY = (lightEnergy * 0.9) + 10;
	darkPosY = (darkEnergy * 0.9) + 10;

	sfw::drawTexture(GetTexture("valueMeter"), 820, 55, 15, 95, 0, true, 0, 0xff0000cc);
	sfw::drawTexture(GetTexture("valueMeter"), 845, 55, 15, 95, 0, true, 0, 0xffff00cc);
	sfw::drawTexture(GetTexture("valueMeter"), 870, 55, 15, 95, 0, true, 0, 0x0000ffcc);
	sfw::drawTexture(GetTexture("healthPtr"), 830, healthPosY, 7, 7, 0, true, 0, 0xffffffcc);
	sfw::drawTexture(GetTexture("lightPtr"), 855, lightPosY, 7, 7, 0, true, 0, 0xffffffcc);
	sfw::drawTexture(GetTexture("darkPtr"), 880, darkPosY, 7, 7, 0, true, 0, 0xffffffcc);
}

void DrawHUD()
{
	sfw::drawTexture(GetTexture("hudBottom"), 0, 170, 900, 170, 0, false, 0, 0x00ff0085);
	sfw::drawTexture(GetTexture("hudTopRight"), 801, 900, 99, 83, 0, false, 0, 0x00ff0085);
}

void CalculateScore(int inScore)
{
	int hundreds = 0, tens = 0, ones = 0;

	if (inScore >= 100)
	{
		hundreds = inScore / 100;
		tens = (inScore % 100) / 10;
		ones = (inScore % 100) % 10;
	}
	if (inScore < 100)
	{
		tens = (inScore % 100) / 10;
		ones = (inScore % 100) % 10;
	}
	else
	{
		ones = inScore;
	}

	scoreValues[5] += ones;
	scoreValues[4] += tens;
	scoreValues[3] += hundreds;

	if (scoreValues[5] > 9)
	{
		scoreValues[5] = scoreValues[5] % 10;
		scoreValues[4] += 1;
	}
	if (scoreValues[4] > 9)
	{
		scoreValues[4] = scoreValues[4] % 10;
		scoreValues[3] += 1;
	}
	if (scoreValues[3] > 9)
	{
		scoreValues[3] = scoreValues[3] % 10;
		scoreValues[2] += 1;
	}
	if (scoreValues[2] > 9)
	{
		scoreValues[2] = scoreValues[2] % 10;
		scoreValues[1] += 1;
	}
	if (scoreValues[1] > 9)
	{
		scoreValues[1] = scoreValues[1] % 10;
		scoreValues[0] += 1;
	}
}

void DrawScore()
{
	sfw::drawTexture(GetTexture("scoreFont"), 50, 48, 32, 32, 0, true, scoreValues[0] + 48, 0x00ff0060);
	sfw::drawTexture(GetTexture("scoreFont"), 75, 48, 32, 32, 0, true, scoreValues[1] + 48, 0x00ff0060);
	sfw::drawTexture(GetTexture("scoreFont"), 100, 48, 32, 32, 0, true, scoreValues[2] + 48, 0x00ff0060);
	sfw::drawTexture(GetTexture("scoreFont"), 125, 48, 32, 32, 0, true, scoreValues[3] + 48, 0x00ff0060);
	sfw::drawTexture(GetTexture("scoreFont"), 150, 48, 32, 32, 0, true, scoreValues[4] + 48, 0x00ff0060);
	sfw::drawTexture(GetTexture("scoreFont"), 175, 48, 32, 32, 0, true, scoreValues[5] + 48, 0x00ff0060);
}