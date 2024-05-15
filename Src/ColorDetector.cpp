#include "ColorDetector.hpp"
#include "Timer/Timer.hpp"
#include "Gpio/Gpio.hpp"

ColorDetector::ColorDetector()
{
	setPeriod(1);
	setPriority(1);
}
ColorDetector::ColorDetector(const Config &config, uint32_t period, uint32_t priority) : m_config{config}
{
	setPeriod(period);
	setPriority(priority);
	setColorPrescaler(ColorDetector::Prescaler::_100);
	setColorFilter(ColorDetector::Filter::None);
}

ColorDetector::~ColorDetector()
{

}

void ColorDetector::loop()
{
	static uint8_t subColorMeasurement = 0;

		if (m_isColorMeasurment == false && false)
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
			m_color.green = frequency;
			setColorFilter(Filter::Blue);
			break;
		case 3:
			m_color.blue = frequency;
			setColorFilter(Filter::None);
			setStateLed(false);
			m_isColorMeasurment = false;
			for(uint32_t i = 0; i < m_endObserverList; i++)
				m_observers[i]->onColorReady(this, m_color);
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

const ColorDetector::Config & ColorDetector::getConfig() const
{
	return m_config;
}
void ColorDetector::setConfig(const ColorDetector::Config &config)
{
	m_config = config;
	setColorPrescaler(ColorDetector::Prescaler::_100);
	setColorFilter(ColorDetector::Filter::None);
}

void ColorDetector::addOnserver(ColorDetectorOnserver* observer)
{
	m_observers[m_endObserverList] = observer;
	m_endObserverList++;
}

