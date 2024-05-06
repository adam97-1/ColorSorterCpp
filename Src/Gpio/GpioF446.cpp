#include "Gpio/GpioF446.hpp"
#include <stm32f446xx.h>

GpioF446::GpioF446()
{

}
GpioF446::~GpioF446()
{

}

void * GpioF446::getGpio(IGpio::Port port)
{
	switch(port)
		{
		case IGpio::Port::A:
			return GPIOA;
		case IGpio::Port::B:
			return GPIOB;
		case IGpio::Port::C:
			return GPIOC;
		case IGpio::Port::D:
			return GPIOD;
		case IGpio::Port::E:
			return GPIOE;
		case IGpio::Port::F:
			return GPIOF;
		case IGpio::Port::G:
			return GPIOG;
		case IGpio::Port::H:
			return GPIOH;
		default:
			return nullptr;
		}
}

bool GpioF446::setConfig(IGpio::Port port, uint32_t pin, IGpio::Config config)
{
	if(pin > 16)
		return false;
	if((config.mode == IGpio::Config::Mode::AlternateFunction) && config.alternateFunction > 15)
			return false;

	GPIO_TypeDef *gpio = static_cast<GPIO_TypeDef*>(getGpio(port));
	if(!gpio)
		return false;

	gpio->MODER &= ~(GPIO_MODER_MODE0_Msk << pin*2);
	gpio->MODER |= (static_cast<uint32_t>(config.mode) << pin*2);

	gpio->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << pin*2);
	gpio->OTYPER |= (static_cast<uint32_t>(config.typ) << pin*2);

	gpio->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << pin*2);
	gpio->PUPDR |= (static_cast<uint32_t>(config.polarization) << pin*2);

	if(config.mode == IGpio::Config::Mode::AlternateFunction)
	{
		gpio->AFR[(pin < 8 ? 0 : 1)] &= ~(GPIO_AFRL_AFSEL0_Msk << pin*2);
		gpio->AFR[(pin < 8 ? 0 : 1)] |= (config.alternateFunction << pin*2);
	}
	return true;
}

bool GpioF446::setState(IGpio::Port port, uint32_t pin, IGpio::State state)
{
	if(state ==  IGpio::State::Unknow)
	 return true;

	if(pin > 16)
		return false;

	GPIO_TypeDef *gpio = static_cast<GPIO_TypeDef*>(getGpio(port));
	if(!gpio)
		return false;

	gpio->ODR &= ~(GPIO_ODR_OD0_Msk << pin*2);
	gpio->ODR |= (static_cast<uint32_t>(state) << pin*2);
	return true;
}
IGpio::State GpioF446::getState(IGpio::Port port, uint32_t pin)
{
	if(pin > 16)
		return IGpio::State::Unknow;

	GPIO_TypeDef *gpio = static_cast<GPIO_TypeDef*>(getGpio(port));
	if(!gpio)
		return IGpio::State::Unknow;

	if((gpio->IDR & (GPIO_IDR_ID0_Msk << pin*2)) == (GPIO_IDR_ID0_Msk << pin*2))
		return IGpio::State::High;
	else
		return IGpio::State::Low;
}
