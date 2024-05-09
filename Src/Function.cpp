#include "Function.hpp"
#include <cmath>

Function::Function()
{

}

Function::~Function()
{

}

float Function::minRadiusDiastance(float position1, float position2)
{
	float distance = 0;

	float distanceUp = minRadiusDiastanceUp(position1, position2);
	float distanceDown = minRadiusDiastanceDown(position1, position2);
	if (distanceUp < distanceDown)
		distance = distanceUp;
	else
		distance = -distanceDown;

	return distance;
}
float Function::minRadiusDiastanceUp(float position1, float position2)
{
	float distance = 0;

	if (position1 >= position2)
		distance = 2 * (float) M_PI - position1 + position2;
	else
		distance = position2 - position1;

	return distance;
}
float Function::minRadiusDiastanceDown(float position1, float position2)
{
	float distance = 0;

	if (position1 >= position2)
		distance = position1 - position2;
	else
		distance = 2 * (float) M_PI - position2 + position1;

	return distance;
}
