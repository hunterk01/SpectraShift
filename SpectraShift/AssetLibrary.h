#pragma once
#include <string>
#include <vector>


// Load and get textures
unsigned GetTexture(const std::string &name);

void LoadTexture(const std::string &name, const char *path, unsigned r, unsigned c);


// Associate animation name with texture frames
unsigned getFrame(const std::string &tname, const std::string &aname, unsigned frame);

unsigned getAnimationLength(const std::string &tname, const std::string &aname);

float getAnimationDuration(const std::string &tname, const std::string &aname);

void addAnimation(const std::string &tname, const std::string &aname, const std::vector<unsigned> &frames, float frameRate = 12.f);

unsigned sampleAnimation(const std::string &tname, const std::string &aname, float timePassed, float speed = 1.f, bool loop = true);


// Function to load all necessary game textures
void LoadAllTextures();