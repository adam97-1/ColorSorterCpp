#pragma once

#include "Timer.hpp"
#include "TimerF446.hpp"

class TimerF446 : public ITimer
{
public:
	TimerF446();
	virtual ~TimerF446();

	bool setEnable(ITimer::Timer timer, bool OnOff) override;
	bool setSourceMode(ITimer::Timer timer, ITimer::SourceModeInternal sourceMode) override;
	bool setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal1 sourceMode) override;
	bool setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal2 sourceMode) override;
	bool setMode(ITimer::Timer timer, ITimer::PwmMode mode) override;
	bool setMode(ITimer::Timer timer, ITimer::ModeEncoder mode) override;
	bool setCounterValue(ITimer::Timer timer, uint32_t value) override;
	uint32_t getCounterValue(ITimer::Timer timer) override;
	bool setReloadValue(ITimer::Timer timer, uint32_t value) override;
	uint32_t getReloadValue(ITimer::Timer timer) override;
	bool setCompareValue(ITimer::Timer timer, ITimer::Chanel chanel, uint32_t value) override;

private:
	void * getTimer(ITimer::Timer  timer);
};
