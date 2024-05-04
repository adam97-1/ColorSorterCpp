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
	bool setSource(const IClock::Source source);
	bool setPLLConfig(const IClock::PllConfig pllConfig);
	bool setAhbPrescaler(const uint32_t prescaler);
	bool setApb1Prescaler(const uint32_t prescaler);
	bool setApb2Prescaler(const uint32_t prescaler);
	bool setEnable(IClock::Peripheral peripheral, bool OnOf);

private:
	IClock *m_clock {nullptr};
};

