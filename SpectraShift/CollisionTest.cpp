#include <cmath>
#include "CollisionTest.h"
#include "GameObjects.h"

float iTest_Circle(float x1, float y1, float r1, float x2, float y2, float r2)
{
	return (r1 + r2) - sqrtf((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
