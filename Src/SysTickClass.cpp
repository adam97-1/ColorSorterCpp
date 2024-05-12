#include <stm32f446xx.h>
#include <SysTickClass.hpp>

volatile uint32_t SysTickClass::m_time;

SysTickClass::SysTickClass()
{
	static bool firstRun = true;
	if(firstRun)
	{
		SysTick_Config(SystemCoreClock / 1000);
		NVIC_EnableIRQ(SysTick_IRQn);
		firstRun = false;
	}
}

SysTickClass::~SysTickClass()
{

}

uint32_t SysTickClass::getTime() const
{
	return SysTickClass::m_time;
}

void SysTick_HandlerCpp(void)
{
	SysTickClass::m_time += 1;
}


extern "C" {
	void SysTick_Handler(void)
	{
		SysTick_HandlerCpp();
	}
}
