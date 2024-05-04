#pragma once

#include "IGpio.hpp"

class Gpio
{
private:
	Gpio();
	virtual ~Gpio();

public:
	static Gpio& getInstance();
	void setGpio(IGpio &gpio);
	bool setConfig(IGpio::Pin pin, IGpio::Config config);
	bool setState(IGpio::Pin pin, IGpio::State state);
	IGpio::State getState(IGpio::Pin pin);

	IGpio *m_gpio {nullptr};
};
