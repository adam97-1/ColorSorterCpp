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

bool GpioF446::setConfig(IGpio::Gpio gpio, IGpio::Config config)
{
	if(gpio.pin > 16)
		return false;
	if((config.mode == IGpio::Config::Mode::AlternateFunction) && config.alternateFunction > 15)
			return false;

	GPIO_TypeDef *gpio_reg = static_cast<GPIO_TypeDef*>(getGpio(gpio.port));
	if(!gpio_reg)
		return false;

	gpio_reg->MODER &= ~(GPIO_MODER_MODE0_Msk << gpio.pin*2);
	gpio_reg->MODER |= (static_cast<uint32_t>(config.mode) << gpio.pin*2);

	gpio_reg->OTYPER &= ~(GPIO_OTYPER_OT0_Msk << gpio.pin*2);
	gpio_reg->OTYPER |= (static_cast<uint32_t>(config.typ) << gpio.pin*2);

	gpio_reg->PUPDR &= ~(GPIO_PUPDR_PUPD0_Msk << gpio.pin*2);
	gpio_reg->PUPDR |= (static_cast<uint32_t>(config.polarization) << gpio.pin*2);

	if(config.mode == IGpio::Config::Mode::AlternateFunction)
	{
		gpio_reg->AFR[(gpio.pin < 8 ? 0 : 1)] &= ~(GPIO_AFRL_AFSEL0_Msk << (gpio.pin % 8)*4);
		gpio_reg->AFR[(gpio.pin < 8 ? 0 : 1)] |= (config.alternateFunction << (gpio.pin % 8)*4);
	}
	return true;
}

bool GpioF446::setState(IGpio::Gpio gpio, IGpio::State state)
{
	if(state ==  IGpio::State::Unknow)
	 return true;

	if(gpio.pin > 16)
		return false;

	GPIO_TypeDef *gpio_reg = static_cast<GPIO_TypeDef*>(getGpio(gpio.port));
	if(!gpio_reg)
		return false;

	gpio_reg->ODR &= ~(GPIO_ODR_OD0_Msk << gpio.pin*2);
	gpio_reg->ODR |= (static_cast<uint32_t>(state) << gpio.pin*2);
	return true;
}
IGpio::State GpioF446::getState(Gpio gpio)
{
	if(gpio.pin > 16)
		return IGpio::State::Unknow;

	GPIO_TypeDef *gpio_reg = static_cast<GPIO_TypeDef*>(getGpio(gpio.port));
	if(!gpio_reg)
		return IGpio::State::Unknow;

	if((gpio_reg->IDR & (GPIO_IDR_ID0_Msk << gpio.pin*2)) == (GPIO_IDR_ID0_Msk << gpio.pin*2))
		return IGpio::State::High;
	else
		return IGpio::State::Low;
}
