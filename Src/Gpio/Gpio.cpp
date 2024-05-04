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
bool Gpio::setConfig(IGpio::Pin pin, IGpio::Config config)
{
	if(!m_gpio)
		return false;
	return m_gpio->setConfig(pin, config);
}

bool Gpio::setState(IGpio::Pin pin, IGpio::State state)
{
	if(!m_gpio)
		return false;
	return m_gpio->setState(pin, state);
}
IGpio::State Gpio::getState(IGpio::Pin pin)
{
	if(!m_gpio)
		return IGpio::State::Unknow;
	return m_gpio->getState(pin);
}


