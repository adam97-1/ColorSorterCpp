#include "Gpio/Gpio.hpp"
#include "Gpio/IGpio.hpp"
Gpio::Gpio()
{

}
Gpio::~Gpio()
{

}

Gpio& Gpio::getInstance()
{
	static Gpio gpio;

	return gpio;
}
void Gpio::setGpio(IGpio &gpio)
{
	m_gpio = &gpio;
}
bool Gpio::setConfig(IGpio::Gpio gpio, IGpio::Config config)
{
	if(!m_gpio)
		return false;
	return m_gpio->setConfig(gpio, config);
}

bool Gpio::setState(IGpio::Gpio gpio, IGpio::State state)
{
	if(!m_gpio)
		return false;
	return m_gpio->setState(gpio, state);
}
IGpio::State Gpio::getState(IGpio::Gpio gpio)
{
	if(!m_gpio)
		return IGpio::State::Unknow;
	return m_gpio->getState(gpio);
}


