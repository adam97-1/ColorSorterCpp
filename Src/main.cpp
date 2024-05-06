#include <Config/Config.hpp>
#include "SysTickClass.hpp"
#include <stm32f446xx.h>
int main(void)
{
	Config::Configure();

	SysTickClass sysTick;
	while(true)
	{
		uint32_t time = sysTick.getTime();
	}
}
