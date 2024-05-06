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
	bool setConfig(IGpio::Port port, uint32_t pin, IGpio::Config config);
	bool setState(IGpio::Port port, uint32_t pin, IGpio::State state);
	IGpio::State getState(IGpio::Port port, uint32_t pin);

	IGpio *m_gpio {nullptr};
};
