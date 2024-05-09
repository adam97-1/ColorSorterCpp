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
	bool setCounterValue(ITimer::Timer timer, uint32_t value);
	uint32_t getCounterValue(ITimer::Timer timer);
	bool setReloadValue(ITimer::Timer timer, uint32_t value);
	uint32_t getReloadValue(ITimer::Timer timer);
	bool setCompareValue(ITimer::Timer timer, ITimer::Chanel chanel, uint32_t value);
	bool setEnableOutput(ITimer::Timer timer, ITimer::Chanel chanel, bool OnOff);
	bool setEnableCompare(ITimer::Timer timer, ITimer::Chanel chanel, bool OnOff);
	bool setCompareMode(ITimer::Timer timer, ITimer::Chanel chanel, ITimer::CompareMode mode);

private:
	ITimer *m_timer {nullptr};


};

