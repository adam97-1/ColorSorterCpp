#include "Clock/Clock.hpp"

Clock::Clock()
{
	// TODO Auto-generated constructor stub

}


Clock::~Clock()
{
	// TODO Auto-generated destructor stub
}

Clock &Clock::getInstance()
{
	static Clock clock;

	return clock;
}

void Clock::setClock(IClock &clock)
{
	m_clock = &clock;
}

bool Clock::setSource(const IClock::Source source)
{
	if(!m_clock)
		return false;
	return m_clock->setSource(source);
}

bool Clock::setPLLConfig(const IClock::PllConfig pllConfig)
{
	if(!m_clock)
		return false;
	return m_clock->setPLLConfig(pllConfig);
}
bool Clock::setAhbPrescaler(const uint32_t prescaler)
{
	if(!m_clock)
		return false;
	return m_clock->setAhbPrescaler(prescaler);
}
bool Clock::setApb1Prescaler(const uint32_t prescaler)
{
	if(!m_clock)
		return false;
	return m_clock->setApb1Prescaler(prescaler);
}
bool Clock::setApb2Prescaler(const uint32_t prescaler)
{
	if(!m_clock)
		return false;
	return m_clock->setApb2Prescaler(prescaler);
}
bool Clock::setEnable(IClock::Peripheral peripheral, bool OnOff)
{
	if(!m_clock)
		return false;
	return m_clock->setEnable(peripheral, OnOff);
}

