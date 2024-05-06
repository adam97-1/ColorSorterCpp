#pragma once

#include "ITimer.hpp"
#include <cstdint>

class Timer
{
private:
	Timer();
	virtual ~Timer();
public:
	static Timer & getInstance();
	void setTimer(ITimer & timer);
	bool setEnable(ITimer::Timer timer, bool OnOff);
	bool setSourceMode(ITimer::Timer timer, ITimer::SourceModeInternal sourceMode);
	bool setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal1 sourceMode);
	bool setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal2 sourceMode);
	bool setMode(ITimer::Timer timer, ITimer::PwmMode mode);
	bool setMode(ITimer::Timer timer, ITimer::ModeEncoder mode);
	uint32_t getCounterValue(ITimer::Timer timer);
	bool setReloadValue(ITimer::Timer timer, ITimer::Chanel chanel, uint32_t value);

private:
	ITimer *m_timer {nullptr};


};

