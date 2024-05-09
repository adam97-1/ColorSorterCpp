#pragma once
#include "Task.hpp"
#include "Timer/ITimer.hpp"

class Encoder : public Task
{
public:
	Encoder(ITimer::Timer timer, uint32_t period, uint32_t priority);
	virtual ~Encoder();

	void loop() override;
	float getSpeed();
	float getPosition();
	void setMaxValue(uint32_t value);
	uint32_t getMaxValue();


private:
	ITimer::Timer m_timer;
	float m_speed	{0};
	float m_position {0};
	uint32_t m_maxValue {0};
	float m_oldPosition {0};
};
