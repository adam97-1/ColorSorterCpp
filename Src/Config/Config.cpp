#include "Config/Config.hpp"
#include "system_stm32f4xx.h"

Config::Config()
{
	Clock::getInstance().setClock(m_clock);
	Flash::getInstance().setFlash(m_flash);
	Gpio::getInstance().setGpio(m_gpio);
	Timer::getInstance().setTimer(m_timer);

}

Config::~Config()
{

}

void Config::Configure()
{
	static Config config;


//////////////////////////////////////////////////////////////////////////////////
/// Flesh
/////////////////////////////////////////////////////////////////////////////////
	Flash::getInstance().setLatency(IFlash::Latency::WS5);
	Flash::getInstance().setParametr(IFlash::Parametr::PREFT, true);
	Flash::getInstance().setParametr(IFlash::Parametr::DC, true);
	Flash::getInstance().setParametr(IFlash::Parametr::IC, true);
//////////////////////////////////////////////////////////////////////////////////
/// Clock
/////////////////////////////////////////////////////////////////////////////////
	IClock::PllConfig pllConfig = {.m = 8, .n = 180, .p = IClock::PllConfig::P::P2, .q = 2, .r = 2, .source = IClock::PllConfig::Source::Hsi};
	Clock::getInstance().setPLLConfig(pllConfig);
	Clock::getInstance().setAhbPrescaler(1);
	Clock::getInstance().setApb1Prescaler(4);
	Clock::getInstance().setApb2Prescaler(2);
	Clock::getInstance().setEnable(IClock::Peripheral::Pll, true);
	Clock::getInstance().setSource(IClock::Source::Pll);

	SystemCoreClockUpdate();

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
//////////////////////////////////////////////////////////////////////////////////
/// UART2
/////////////////////////////////////////////////////////////////////////////////
//	Gpio::getInstance().setConfig(
//			IGpio::Gpio { .port = IGpio::Port::A, .pin = 2},
//			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
//							.typ  = IGpio::Config::Typ::PushPull,
//							.speed = IGpio::Config::Speed::Low,
//							.polarization = IGpio::Config::Polarization::PullUp,
//							.alternateFunction = 7});
//	Gpio::getInstance().setConfig(
//			IGpio::Gpio { .port = IGpio::Port::A, .pin = 3},
//			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
//							.typ  = IGpio::Config::Typ::PushPull,
//							.speed = IGpio::Config::Speed::Low,
//							.polarization = IGpio::Config::Polarization::PullUp,
//							.alternateFunction = 7});
//////////////////////////////////////////////////////////////////////////////////
// TestPin
//////////////////////////////////////////////////////////////////////////////////
Gpio::getInstance().setConfig(
		IGpio::Gpio { .port = IGpio::Port::C, .pin = 3},
		IGpio::Config { .mode = IGpio::Config::Mode::Output,
						.typ  = IGpio::Config::Typ::PushPull,
						.speed = IGpio::Config::Speed::High,
						.polarization = IGpio::Config::Polarization::PullUp,
						.alternateFunction = 0});
//////////////////////////////////////////////////////////////////////////////////
/// ColorDetector
/////////////////////////////////////////////////////////////////////////////////
	// Out -- In Tim3
	Gpio::getInstance().setConfig(
		IGpio::Gpio { .port = IGpio::Port::D, .pin = 2},
		IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
						.typ  = IGpio::Config::Typ::PushPull,
						.speed = IGpio::Config::Speed::Low,
						.polarization = IGpio::Config::Polarization::NoPullUpNoPullDown,
						.alternateFunction = 2});
	// S0
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 5},
			IGpio::Config { .mode = IGpio::Config::Mode::Output,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});
	// S1
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 6},
			IGpio::Config { .mode = IGpio::Config::Mode::Output,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});
	// S2
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 10},
			IGpio::Config { .mode = IGpio::Config::Mode::Output,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});
	// S3
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 11},
			IGpio::Config { .mode = IGpio::Config::Mode::Output,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});
	//Led
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 12},
			IGpio::Config { .mode = IGpio::Config::Mode::Output,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});

	Timer::getInstance().setSourceMode(ITimer::Timer::Tim3,
						ITimer::SourceModeExternal2{.inputFilter = 0,
													.edgeDetect = ITimer::SourceModeExternal2::EdgeDetect::HighOrRising,
													.presacaler = 2});
//////////////////////////////////////////////////////////////////////////////////
/// IrDetectorSel
/////////////////////////////////////////////////////////////////////////////////
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 8},
			IGpio::Config { .mode = IGpio::Config::Mode::Input,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});
//////////////////////////////////////////////////////////////////////////////////
/// IrDetectorCol
/////////////////////////////////////////////////////////////////////////////////
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::C, .pin = 9},
			IGpio::Config { .mode = IGpio::Config::Mode::Input,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 0});
//////////////////////////////////////////////////////////////////////////////////
/// EncoderMotorDriv
/////////////////////////////////////////////////////////////////////////////////
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::A, .pin = 8},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullDown,
							.alternateFunction = 1});
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::A, .pin = 9},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullDown,
							.alternateFunction = 1});
	Timer::getInstance().setMode(ITimer::Timer::Tim1,
								ITimer::ModeEncoder{ .inputFilter = 0,
													.edgeDetectT1 = ITimer::ModeEncoder::EdgeDetect::NoInvertedRising,
													.edgeDetectT2 = ITimer::ModeEncoder::EdgeDetect::NoInvertedRising,
													.mode = ITimer::ModeEncoder::Mode::BothDependingTi});
	Timer::getInstance().setReloadValue(ITimer::Timer::Tim1, 2472);
//////////////////////////////////////////////////////////////////////////////////
/// EncoderMotorSel
/////////////////////////////////////////////////////////////////////////////////
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::A, .pin = 5},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullDown,
							.alternateFunction = 1});
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::B, .pin = 3},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullDown,
							.alternateFunction = 1});
	Timer::getInstance().setMode(ITimer::Timer::Tim2,
								ITimer::ModeEncoder{ .inputFilter = 0,
													.edgeDetectT1 = ITimer::ModeEncoder::EdgeDetect::NoInvertedRising,
													.edgeDetectT2 = ITimer::ModeEncoder::EdgeDetect::NoInvertedRising,
													.mode = ITimer::ModeEncoder::Mode::BothDependingTi});
	Timer::getInstance().setReloadValue(ITimer::Timer::Tim2, 2472);
//////////////////////////////////////////////////////////////////////////////////
/// MotorSel
/////////////////////////////////////////////////////////////////////////////////
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::A, .pin = 7},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 9});

	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::B, .pin = 6},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 2});
	Timer::getInstance().setMode(ITimer::Timer::Tim4, ITimer::PwmMode::EdgeAligned);
	Timer::getInstance().setEnableOutput(ITimer::Timer::Tim4, ITimer::Chanel::Ch1, true);
	Timer::getInstance().setCompareMode(ITimer::Timer::Tim4, ITimer::Chanel::Ch1, ITimer::CompareMode::Pwm2);
	Timer::getInstance().setReloadValue(ITimer::Timer::Tim4, 2000);
	Timer::getInstance().setMode(ITimer::Timer::Tim14, ITimer::PwmMode::EdgeAligned);
	Timer::getInstance().setEnableOutput(ITimer::Timer::Tim14, ITimer::Chanel::Ch1, true);
	Timer::getInstance().setCompareMode(ITimer::Timer::Tim14, ITimer::Chanel::Ch1, ITimer::CompareMode::Pwm2);
	Timer::getInstance().setReloadValue(ITimer::Timer::Tim14, 2000);
//////////////////////////////////////////////////////////////////////////////////
/// MotorDriv
/////////////////////////////////////////////////////////////////////////////////
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::B, .pin = 8},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 2});
	Gpio::getInstance().setConfig(
			IGpio::Gpio { .port = IGpio::Port::B, .pin = 9},
			IGpio::Config { .mode = IGpio::Config::Mode::AlternateFunction,
							.typ  = IGpio::Config::Typ::PushPull,
							.speed = IGpio::Config::Speed::Low,
							.polarization = IGpio::Config::Polarization::PullUp,
							.alternateFunction = 2});
	Timer::getInstance().setMode(ITimer::Timer::Tim4, ITimer::PwmMode::EdgeAligned);
	Timer::getInstance().setEnableOutput(ITimer::Timer::Tim4, ITimer::Chanel::Ch3, true);
	Timer::getInstance().setCompareMode(ITimer::Timer::Tim4, ITimer::Chanel::Ch3, ITimer::CompareMode::Pwm2);
	Timer::getInstance().setEnableOutput(ITimer::Timer::Tim4, ITimer::Chanel::Ch4, true);
	Timer::getInstance().setCompareMode(ITimer::Timer::Tim4, ITimer::Chanel::Ch4, ITimer::CompareMode::Pwm2);
	Timer::getInstance().setReloadValue(ITimer::Timer::Tim4, 2000);

//////////////////////////////////////////////////////////////////////////////////
/// ModuleEnable
/////////////////////////////////////////////////////////////////////////////////
	Timer::getInstance().setEnable(ITimer::Timer::Tim1, true);
	Timer::getInstance().setEnable(ITimer::Timer::Tim2, true);
	Timer::getInstance().setEnable(ITimer::Timer::Tim3, true);
	Timer::getInstance().setEnable(ITimer::Timer::Tim4, true);
	Timer::getInstance().setEnable(ITimer::Timer::Tim14, true);
}
