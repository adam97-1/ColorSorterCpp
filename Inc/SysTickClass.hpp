#pragma once

#include <cstdint>

class SysTickClass
{
    friend void SysTick_HandlerCpp(void);
public:
	SysTickClass();
	virtual ~SysTickClass();
	uint32_t getTime();
private:
	static volatile uint32_t m_time;
};
