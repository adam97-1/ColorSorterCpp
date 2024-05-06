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
bool Gpio::setConfig(IGpio::Port port, uint32_t pin, IGpio::Config config)
{
	if(!m_gpio)
		return false;
	return m_gpio->setConfig(port, pin, config);
}

bool Gpio::setState(IGpio::Port port, uint32_t pin, IGpio::State state)
{
	if(!m_gpio)
		return false;
	return m_gpio->setState(port, pin, state);
}
IGpio::State Gpio::getState(IGpio::Port port, uint32_t pin)
{
	if(!m_gpio)
		return IGpio::State::Unknow;
	return m_gpio->getState(port, pin);
}


