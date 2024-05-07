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
	bool setConfig(IGpio::Gpio gpio, IGpio::Config config);
	bool setState(IGpio::Gpio gpio, IGpio::State state);
	IGpio::State getState(IGpio::Gpio gpio);

	IGpio *m_gpio {nullptr};
};
