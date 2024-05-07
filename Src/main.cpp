#include <Config/Config.hpp>
#include "TaskMenager.hpp"
#include "IrDetector.hpp"
#include "ColorDetector.hpp"
ColorDetector::Color m_color;
void Func(ColorDetector::Color color)
{
	m_color = color;
}

int main(void)
{
	Config::Configure();
	TaskMenager taskMenager;
	IrDetector irDetectorSel(IGpio::Gpio {.port  = IGpio::Port::C, .pin = 8}, 100, 1);
	IrDetector irlDetectorCol(IGpio::Gpio {.port =  IGpio::Port::C, .pin = 9}, 100, 1);
	ColorDetector colorDetector(ColorDetector::Config{.s0 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 6},
													.s1 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 5},
													.s2 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 10},
													.s3 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 11},
													.led = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 12},
													.timInput = ITimer::Timer::Tim3}, 10, 1);

	taskMenager.addTask(irDetectorSel);
	taskMenager.addTask(irlDetectorCol);
	taskMenager.addTask(colorDetector);
	colorDetector.setColorReady(Func);
	while(true)
	{
		taskMenager.run();
		colorDetector.measurementColor();
	}
}
