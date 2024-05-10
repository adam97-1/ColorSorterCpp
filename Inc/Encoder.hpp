#pragma once
#include "Task.hpp"
#include "Timer/ITimer.hpp"

class Encoder : public Task
{
public:
	Encoder(ITimer::Timer timer = ITimer::Timer::Tim1, uint32_t period = 1, uint32_t priority = 1);
	virtual ~Encoder();

	void loop() override;
	float getSpeed() const;
	float getPosition() const;
	void setMaxValue(uint32_t value);
	uint32_t getMaxValue() const;
	void setTimer(ITimer::Timer timer);
	ITimer::Timer getTimer() const;



private:
	ITimer::Timer m_timer;
	float m_speed	{0};
	float m_position {0};
	uint32_t m_maxValue {0};
	float m_oldPosition {0};
};
