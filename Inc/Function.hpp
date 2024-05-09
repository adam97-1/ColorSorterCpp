#pragma once

class Function
{
public:
	Function();
	virtual ~Function();

	static float minRadiusDiastance(float position1, float position2);
private:
	static float minRadiusDiastanceUp(float position1, float position2);
	static float minRadiusDiastanceDown(float position1, float position2);
};

