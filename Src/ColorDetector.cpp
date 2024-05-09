#include "ColorDetector.hpp"
#include "Timer/Timer.hpp"
#include "Gpio/Gpio.hpp"

ColorDetector::ColorDetector(Config config, uint32_t period, uint32_t priority) : m_config{config}
{
	setPeriod(period);
	setPriority(priority);
	m_colorReady = [](Color color){};
	setColorPrescaler(ColorDetector::Prescaler::_100);
	setColorFilter(ColorDetector::Filter::None);
}

ColorDetector::~ColorDetector()
{

}


void ColorDetector::setColorReady(std::function<void(Color)> func)
{
    m_colorReady = func;
}

template<class C, void (C::*Function)(ColorDetector::Color)>
void ColorDetector::setColorReady(C *instance)
{
	m_colorReady = std::bind(Function, instance, std::placeholders::_1);
}

void ColorDetector::loop()
{
	static uint8_t subColorMeasurement = 0;

		if (m_isColorMeasurment == false)
			return;

		uint32_t frequency = Timer::getInstance().getCounterValue(m_config.timInput);
		Timer::getInstance().setCounterValue(m_config.timInput, 0);
		switch (subColorMeasurement)
		{
		case 0:
			m_color.none = frequency;
			setColorFilter(Filter::Red);
			break;
		case 1:
			m_color.red = frequency;
			setColorFilter(Filter::Green);
			break;
		case 2:
			m_color.blue = frequency;
			setColorFilter(Filter::Blue);
			break;
		case 3:
			m_color.green = frequency;
			setColorFilter(Filter::None);
			setStateLed(false);
			m_isColorMeasurment = false;
			m_colorReady(m_color);
			break;
		default:
			break;
		}
		subColorMeasurement++;
		subColorMeasurement %= 4;
}
void ColorDetector::setColorPrescaler(ColorDetector::Prescaler prescaler)
{
	switch(prescaler)
	{
	case ColorDetector::Prescaler::_0:
		Gpio::getInstance().setState(m_config.s0, IGpio::State::Low);
		Gpio::getInstance().setState(m_config.s1, IGpio::State::Low);
		break;
	case ColorDetector::Prescaler::_2:
		Gpio::getInstance().setState(m_config.s0, IGpio::State::Low);
		Gpio::getInstance().setState(m_config.s1, IGpio::State::High);
		break;
	case ColorDetector::Prescaler::_80:
		Gpio::getInstance().setState(m_config.s0, IGpio::State::High);
		Gpio::getInstance().setState(m_config.s1, IGpio::State::Low);
		break;
	case ColorDetector::Prescaler::_100:
		Gpio::getInstance().setState(m_config.s0, IGpio::State::High);
		Gpio::getInstance().setState(m_config.s1, IGpio::State::High);
		break;
	}
}
void ColorDetector::setColorFilter(ColorDetector::Filter filter)
{
	switch(filter)
	{
	case ColorDetector::Filter::None:
		Gpio::getInstance().setState(m_config.s2, IGpio::State::High);
		Gpio::getInstance().setState(m_config.s3, IGpio::State::Low);
		break;
	case ColorDetector::Filter::Red:
		Gpio::getInstance().setState(m_config.s2, IGpio::State::Low);
		Gpio::getInstance().setState(m_config.s3, IGpio::State::Low);
		break;
	case ColorDetector::Filter::Green:
		Gpio::getInstance().setState(m_config.s2, IGpio::State::High);
		Gpio::getInstance().setState(m_config.s3, IGpio::State::High);
		break;
	case ColorDetector::Filter::Blue:
		Gpio::getInstance().setState(m_config.s2, IGpio::State::Low);
		Gpio::getInstance().setState(m_config.s3, IGpio::State::High);
		break;
	}
}
void ColorDetector::setStateLed(bool OnOff)
{
	Gpio::getInstance().setState(m_config.led, (OnOff) ? IGpio::State::High :IGpio::State::Low);
}

void ColorDetector::measurementColor()
{
	setStateLed(true);
	m_isColorMeasurment = true;
}

