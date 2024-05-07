#pragma once

#include <cstdint>

class Task
{
public:
	virtual void loop() = 0;
	void setPeriod(uint32_t period);
	uint32_t getPeriod();
	void setPriority(uint32_t priority);
	uint32_t getPriority();

private:
	uint32_t m_period {0};
	uint32_t m_priority {0};
};
