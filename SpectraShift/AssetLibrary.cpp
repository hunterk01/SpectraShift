#include "sfwdraw.h"
#include "AssetLibrary.h"
#include <string>
#include <map>

static std::map<std::string, unsigned> textures;


// Load and get textures
unsigned GetTexture(const std::string &name)
{
	return textures[name];
}

void LoadTexture(const std::string &name, const char *path, unsigned r, unsigned c)
{
	textures[name] = sfw::loadTextureMap(path, r, c);
}


// Associate animation name with texture frames
static std::map<std::string, std::map<std::string, std::vector<unsigned >> > animations;

static std::map<std::string, std::map<std::string, float> > frameRates;


unsigned getFrame(const std::string &tname, const std::string &aname, unsigned frame)
{
	return animations[tname][aname][frame];
}


unsigned getAnimationLength(const std::string &tname, const std::string &aname)
{
	return animations[tname][aname].size();
}


float getAnimationDuration(const std::string &tname, const std::string &aname)
{
	return getAnimationLength(tname, aname) / frameRates[tname][aname];
}


void addAnimation(const std::string &tname, const std::string &aname, const std::vector<unsigned> &frames, float frameRate)
{
	animations[tname][aname] = frames;
	frameRates[tname][aname] = frameRate;
}


unsigned sampleAnimation(const std::string &tname, const std::string &aname, float timePassed, float speed, bool loop)
{
	unsigned index = (timePassed / getAnimationDuration(tname, aname)) * (getAnimationLength(tname, aname));
	
	if (loop)
		index %= getAnimationLength(tname, aname);
	else if (index == getAnimationLength(tname, aname))
		index--;

	return getFrame(tname, aname, index);
}



// Function to load all necessary game textures
void LoadAllTextures()
{
	// Background Textures
	LoadTexture("BG_stars", "./Assets/BG/starfield.png", 1, 1);
	LoadTexture("BG_light", "./Assets/BG/skyLight.png", 1, 1);
	LoadTexture("BG_dark", "./Assets/BG/skyDark.png", 1, 1);
	LoadTexture("TitleBG1", "./Assets/BG/TitleBG_Nebula1.png", 1, 1);
	LoadTexture("TitleBG2", "./Assets/BG/TitleBG_Nebula2.png", 1, 1);
	
	// HUD Textures
	LoadTexture("valueMeter", "./Assets/HUD/valueMeter.png", 1, 1);
	LoadTexture("healthPtr", "./Assets/HUD/pointer.png", 1, 1);
	LoadTexture("lightPtr", "./Assets/HUD/pointer.png", 1, 1);
	LoadTexture("darkPtr", "./Assets/HUD/pointer.png", 1, 1);
	LoadTexture("hudTopRight", "./Assets/HUD/hudTopRight.png", 1, 1);
	LoadTexture("hudBottom", "./Assets/HUD/hudBottom.png", 1, 1);
	LoadTexture("scoreFont", "./Assets/Fonts/scoreFont.png", 16, 16);

	// Ship Textures
	LoadTexture("playerShip", "./Assets/Ships/playerShip.png", 1, 1);
	LoadTexture("target", "./Assets/Objects/target.png", 1, 1);

	// Asteroid Textures
	LoadTexture("asteroid1", "./Assets/Objects/asteroid1.png", 5, 4);
	LoadTexture("asteroid2", "./Assets/Objects/asteroid2.png", 5, 4);
	LoadTexture("asteroid3", "./Assets/Objects/asteroid3.png", 5, 4);
	LoadTexture("asteroid4", "./Assets/Objects/asteroid4.png", 5, 4);

	// Asteroid Animations
	addAnimation("asteroid1", "rotation", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
	addAnimation("asteroid2", "rotation", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
	addAnimation("asteroid3", "rotation", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });
	addAnimation("asteroid4", "rotation", { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18 });

	// SFX Textures
	LoadTexture("yellowBullet", "./Assets/SFX/yellowBullet.png", 1, 1);

	// Text Objects
	LoadTexture("title", "./Assets/Fonts/SpectraShiftTitle.png", 1, 1);
	LoadTexture("controls", "./Assets/Fonts/textControls.png", 1, 1);
	LoadTexture("credits", "./Assets/Fonts/textCredits.png", 1, 1);
	LoadTexture("instructions", "./Assets/Fonts/textInstructions.png", 1, 1);
	LoadTexture("quit", "./Assets/Fonts/textQuit.png", 1, 1);
	LoadTexture("start", "./Assets/Fonts/textStart.png", 1, 1);
	LoadTexture("thanks", "./Assets/Fonts/textThanks.png", 1, 1);
	LoadTexture("Xmark", "./Assets/Fonts/textX.png", 1, 1);
	LoadTexture("forward", "./Assets/Fonts/textForward.png", 1, 1);
	LoadTexture("compass", "./Assets/Fonts/textCompass.png", 1, 1);
	LoadTexture("back", "./Assets/Fonts/textBack.png", 1, 1);
	LoadTexture("targetText", "./Assets/Text/targetText.png", 1, 1);
	LoadTexture("forwardText", "./Assets/Text/forwardText.png", 1, 1);
	LoadTexture("compassText", "./Assets/Text/compassText.png", 1, 1);
	LoadTexture("creditsText", "./Assets/Text/creditsText.png", 1, 1);
	
}

