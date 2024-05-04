#include "Config/Config.hpp"
#include "system_stm32f4xx.h"

Config::Config()
{
	Clock::getInstance().setClock(m_clock);
	Flash::getInstance().setFlash(m_flash);

}

Config::~Config()
{

}

void Config::Configure()
{
	static Config config;

	Clock::getInstance().setEnable(IClock::Peripheral::Pll, true);
	Clock::getInstance().setEnable(IClock::Peripheral::Pwr, true);
	Clock::getInstance().setEnable(IClock::Peripheral::GpioA, true);
	Clock::getInstance().setEnable(IClock::Peripheral::GpioB, true);
	Clock::getInstance().setEnable(IClock::Peripheral::GpioC, true);
	Clock::getInstance().setEnable(IClock::Peripheral::GpioD, true);
	Clock::getInstance().setEnable(IClock::Peripheral::Tim1, true);
	Clock::getInstance().setEnable(IClock::Peripheral::Tim2, true);
	Clock::getInstance().setEnable(IClock::Peripheral::Tim3, true);
	Clock::getInstance().setEnable(IClock::Peripheral::Tim4, true);
	Clock::getInstance().setEnable(IClock::Peripheral::Tim14, true);

	Flash::getInstance().setLatency(IFlash::Latency::WS5);
	Flash::getInstance().setParametr(IFlash::Parametr::PREFT, true);
	Flash::getInstance().setParametr(IFlash::Parametr::DC, true);
	Flash::getInstance().setParametr(IFlash::Parametr::IC, true);

	IClock::PllConfig pllConfig = {.m = 8, .n = 180, .p = IClock::PllConfig::P::P2, .q = 2, .r = 2, .source = IClock::PllConfig::Source::Hsi};
	Clock::getInstance().setPLLConfig(pllConfig);
	Clock::getInstance().setAhbPrescaler(1);
	Clock::getInstance().setApb1Prescaler(4);
	Clock::getInstance().setApb2Prescaler(2);
	Clock::getInstance().setSource(IClock::Source::Pll);
	SystemCoreClockUpdate();
}
