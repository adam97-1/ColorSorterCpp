#pragma once

#include "Clock/ClockSTMF446.hpp"
#include "Flash/FlashF446.hpp"
#include "Gpio/GpioF446.hpp"
#include "Timer/TimerF446.hpp"

class Config
{

private:
	Config();
	virtual ~Config();

	ClockSTMF446 m_clock;
	FlashF446 m_flash;
	GpioF446 m_gpio;
	TimerF446 m_timer;
public:
	static void Configure();

};
