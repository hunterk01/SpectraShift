#include "sfwdraw.h"
#include "GameObjects.h"
#include "CollisionTest.h"
#include <math.h>

void GameObject::SetAngles(GameObject &targetObject)
{

}

void GameObject::Draw()
{
	sfw::drawTexture(GetTexture(textureName), position.x, position.y, dimensions.x, dimensions.y, targetAngle, true, currentFrame);
}

void GameObject::Update()
{
	animTimer += sfw::getDeltaTime();
	currentFrame = sampleAnimation(textureName, animationName, animTimer);
}

void GameObject::onCollision(GameObject &go, float distance)
{
	
}


float doCollision(GameObject &go1, GameObject &go2)
{
	float distance = iTest_Circle(go1.position.x, go1.position.y, go1.radius, go2.position.x, go2.position.y, go2.radius);

	if (distance > 0)
	{
		go1.onCollision(go2, distance);
		go2.onCollision(go1, distance);
	}

	return distance;
}
