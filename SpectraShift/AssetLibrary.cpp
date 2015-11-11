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
	LoadTexture("BG_stars", "./Sprites/BG/starfield.png", 1, 1);
	LoadTexture("BG_light", "./Sprites/BG/blue_ring_nebula.png", 1, 1);
	LoadTexture("BG_dark", "./Sprites/BG/sky_dark.png", 1, 1);
	
	// HUD Textures
	LoadTexture("valueMeter", "./Sprites/HUD/valueMeter.png", 1, 1);
	LoadTexture("healthPtr", "./Sprites/HUD/pointer.png", 1, 1);
	LoadTexture("lightPtr", "./Sprites/HUD/pointer.png", 1, 1);
	LoadTexture("darkPtr", "./Sprites/HUD/pointer.png", 1, 1);
	LoadTexture("hudTopRight", "./Sprites/HUD/hudTopRight.png", 1, 1);
	LoadTexture("hudBottom", "./Sprites/HUD/gameHUD.png", 1, 1);
	LoadTexture("scoreFont", "./Sprites/Text/scoreFont.png", 16, 16);

	// Ship Textures
	LoadTexture("playerShip", "./Sprites/Ships/redFighter.png", 1, 1);

	// Asteroid Textures
	LoadTexture("asteroid1", "./Sprites/Objects/asteroid1.png", 5, 4);
	LoadTexture("asteroid2", "./Sprites/Objects/asteroid2.png", 5, 4);
	LoadTexture("asteroid3", "./Sprites/Objects/asteroid3.png", 5, 4);
	LoadTexture("asteroid4", "./Sprites/Objects/asteroid4.png", 5, 4);

	// SFX Textures

}

