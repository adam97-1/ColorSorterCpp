#pragma once

#include "Gpio.hpp"

class GpioF446 : public IGpio
{
public:
	GpioF446();
	~GpioF446();
	bool setConfig(IGpio::Pin pin, IGpio::Config config) override;
	bool setState(IGpio::Pin pin, IGpio::State state) override;
	IGpio::State getState(IGpio::Pin pin) override;
};
