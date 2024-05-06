#pragma once

#include "IClock.hpp"

class Clock
{
private:
	Clock();
	virtual ~Clock();
public:
	static Clock &getInstance();
	void setClock(IClock &clock);
	bool setSource(IClock::Source source);
	bool setPLLConfig(IClock::PllConfig pllConfig);
	bool setAhbPrescaler(uint32_t prescaler);
	bool setApb1Prescaler(uint32_t prescaler);
	bool setApb2Prescaler(uint32_t prescaler);
	bool setEnable(IClock::Peripheral peripheral, bool OnOf);

private:
	IClock *m_clock {nullptr};
};

