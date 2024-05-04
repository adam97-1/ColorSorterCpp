#include "Gpio/GpioF446.hpp"
#include <stm32f446xx.h>

GpioF446::GpioF446()
{

}
GpioF446::~GpioF446()
{

}

bool GpioF446::setConfig(IGpio::Pin pin, IGpio::Config config)
{
	if(pin.pin > 16)
		return false;

	GPIO_TypeDef *gpio;
	switch(pin.port)
	{
	case IGpio::Pin::Port::A:
		gpio = GPIOA;
		break;
	case IGpio::Pin::Port::B:
		gpio = GPIOB;
		break;
	case IGpio::Pin::Port::C:
		gpio = GPIOC;
		break;
	case IGpio::Pin::Port::D:
		gpio = GPIOD;
		break;
	case IGpio::Pin::Port::E:
		gpio = GPIOE;
		break;
	case IGpio::Pin::Port::F:
		gpio = GPIOF;
		break;
	case IGpio::Pin::Port::G:
		gpio = GPIOG;
		break;
	case IGpio::Pin::Port::H:
		gpio = GPIOH;
		break;
	default:
		return false;
	}
	gpio->MODER &= ~(GPIO_MODER_MODE0_Msk << pin.pin*2);
	gpio->MODER |= (static_cast<uint32_t>(config.mode) << pin.pin*2);

	gpio->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << pin.pin*2);
	gpio->OTYPER |= (static_cast<uint32_t>(config.typ) << pin.pin*2);

	gpio->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << pin.pin*2);
	gpio->PUPDR |= (static_cast<uint32_t>(config.polarization) << pin.pin*2);

	if(config.mode == IGpio::Config::Mode::AlternateFunction)
	{
		gpio->AFR[(pin.pin < 8 ? 0 : 1)] &= ~(GPIO_AFRL_AFSEL0_Msk << pin.pin*2);
		gpio->AFR[(pin.pin < 8 ? 0 : 1)] |= (config.alternateFunction << pin.pin*2);
	}
	return true;
}

bool GpioF446::setState(IGpio::Pin pin, IGpio::State state)
{
	if(state ==  IGpio::State::Unknow)
	 return true;

	if(pin.pin > 16)
		return false;

	GPIO_TypeDef *gpio;
	switch(pin.port)
	{
	case IGpio::Pin::Port::A:
		gpio = GPIOA;
		break;
	case IGpio::Pin::Port::B:
		gpio = GPIOB;
		break;
	case IGpio::Pin::Port::C:
		gpio = GPIOC;
		break;
	case IGpio::Pin::Port::D:
		gpio = GPIOD;
		break;
	case IGpio::Pin::Port::E:
		gpio = GPIOE;
		break;
	case IGpio::Pin::Port::F:
		gpio = GPIOF;
		break;
	case IGpio::Pin::Port::G:
		gpio = GPIOG;
		break;
	case IGpio::Pin::Port::H:
		gpio = GPIOH;
		break;
	default:
		return false;
	}

	gpio->ODR &= ~(GPIO_ODR_OD0_Msk << pin.pin*2);
	gpio->ODR |= (static_cast<uint32_t>(state) << pin.pin*2);
	return true;
}
IGpio::State GpioF446::getState(IGpio::Pin pin)
{
	if(pin.pin > 16)
		return IGpio::State::Unknow;

	GPIO_TypeDef *gpio;
	switch(pin.port)
	{
	case IGpio::Pin::Port::A:
		gpio = GPIOA;
		break;
	case IGpio::Pin::Port::B:
		gpio = GPIOB;
		break;
	case IGpio::Pin::Port::C:
		gpio = GPIOC;
		break;
	case IGpio::Pin::Port::D:
		gpio = GPIOD;
		break;
	case IGpio::Pin::Port::E:
		gpio = GPIOE;
		break;
	case IGpio::Pin::Port::F:
		gpio = GPIOF;
		break;
	case IGpio::Pin::Port::G:
		gpio = GPIOG;
		break;
	case IGpio::Pin::Port::H:
		gpio = GPIOH;
		break;
	default:
		return IGpio::State::Unknow;
	}

	if((gpio->IDR & (GPIO_IDR_ID0_Msk << pin.pin*2)) == (GPIO_IDR_ID0_Msk << pin.pin*2))
		return IGpio::State::High;
	else
		return IGpio::State::Low;
}
