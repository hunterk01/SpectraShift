#include "sfwdraw.h"
#include "GameObjects.h"
#include <math.h>

void GameObject::SetAngles()
{
	// Get difference in player and mouse positions
	float dx = sfw::getMouseX() - position.x;
	float dy = sfw::getMouseY() - position.y;

	// Calculate rotation angle in degrees
	targetAngle = atan2f(dy, dx);
	targetAngle = targetAngle * (180 / PI);

	// Calculate perpendicular angle
	perpAngle = -targetAngle * (180 / PI);


	//std::cout << "Target: " << targetAngle << std::endl << "Perp: " << perpAngle << std::endl << std::endl;
}

void GameObject::Draw()
{

}

void GameObject::Update()
{

}

bool GameObject::hasCollided()
{
	
	return false;
}
