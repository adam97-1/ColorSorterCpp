#pragma once

#include "Gpio.hpp"

class GpioF446 : public IGpio
{
public:
	GpioF446();
	~GpioF446();
	bool setConfig(IGpio::Port port, uint32_t pin, IGpio::Config config) override;
	bool setState(IGpio::Port port, uint32_t pin, IGpio::State state) override;
	IGpio::State getState(IGpio::Port port, uint32_t pin) override;

private:
	void * getGpio(IGpio::Port  port);
};
