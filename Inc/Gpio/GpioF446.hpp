#pragma once

#include "Gpio.hpp"

class GpioF446 : public IGpio
{
public:
	GpioF446();
	~GpioF446();
	bool setConfig(IGpio::Gpio gpio, IGpio::Config config) override;
	bool setState(IGpio::Gpio gpio, IGpio::State state) override;
	IGpio::State getState(IGpio::Gpio gpio) override;

private:
	void * getGpio(IGpio::Port  port);
};
