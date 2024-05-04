#pragma once

#include "Clock/ClockSTMF446.hpp"
#include "Flash/FlashF446.hpp"

class Config
{

private:
	Config();
	virtual ~Config();

	ClockSTMF446 m_clock;
	FlashF446 m_flash;
public:
	static void Configure();

};
