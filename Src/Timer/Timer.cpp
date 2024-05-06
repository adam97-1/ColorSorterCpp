#include "Timer/Timer.hpp"

Timer::Timer()
{

}

Timer::~Timer()
{

}

Timer & Timer::getInstance()
{
	static Timer timer;

	return timer;
}
void Timer::setTimer(ITimer & timer)
{
	m_timer = &timer;
}
bool Timer::setEnable(ITimer::Timer timer, bool OnOff)
{
	if(!m_timer)
		return false;
	return m_timer->setEnable(timer, OnOff);
}
bool Timer::setSourceMode(ITimer::Timer timer, ITimer::SourceModeInternal sourceMode)
{
	if(!m_timer)
		return false;
	return m_timer->setSourceMode(timer, sourceMode);
}
bool Timer::setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal1 sourceMode)
{
	if(!m_timer)
		return false;
	return m_timer->setSourceMode(timer, sourceMode);
}
bool Timer::setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal2 sourceMode)
{
	if(!m_timer)
		return false;
	return m_timer->setSourceMode(timer, sourceMode);
}
bool Timer::setMode(ITimer::Timer timer, ITimer::PwmMode mode)
{
	if(!m_timer)
		return false;
	return m_timer->setMode(timer, mode);
}
bool Timer::setMode(ITimer::Timer timer, ITimer::ModeEncoder mode)
{
	if(!m_timer)
		return false;
	return m_timer->setMode(timer, mode);
}
uint32_t Timer::getCounterValue(ITimer::Timer timer)
{
	if(!m_timer)
		return false;
	return m_timer->getCounterValue(timer);
}
bool Timer::setReloadValue(ITimer::Timer timer, uint32_t value)
{
	if(!m_timer)
		return false;
	return m_timer->setReloadValue(timer, value);
}
uint32_t Timer::getReloadValue(ITimer::Timer timer)
{
	if(!m_timer)
		return 0;
	return m_timer->getReloadValue(timer);
}
bool Timer::setCompareValue(ITimer::Timer timer, ITimer::Chanel chanel, uint32_t value)
{
	if(!m_timer)
		return false;
	return m_timer->setCompareValue(timer, chanel, value);
}
