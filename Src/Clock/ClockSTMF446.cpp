

#include "Clock/ClockSTMF446.hpp"
#include <stm32f446xx.h>

ClockSTMF446::ClockSTMF446() {

}

ClockSTMF446::~ClockSTMF446() {
}

bool ClockSTMF446::setSource(Source source)
{
	switch(source)
	{
	case Source::Hse:
		RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
		RCC->CFGR |= RCC_CFGR_SW_HSE;
		while ((RCC->CFGR & RCC_CFGR_SWS_HSE) != RCC_CFGR_SWS_HSE)
			;
		return true;
	case Source::Hsi:
		RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
		RCC->CFGR |= RCC_CFGR_SW_HSI;
		while ((RCC->CFGR & RCC_CFGR_SWS_HSI) != RCC_CFGR_SWS_HSI)
			;
		return true;
	case Source::Pll:
		RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
		RCC->CFGR |= RCC_CFGR_SW_PLL;
		while ((RCC->CFGR & RCC_CFGR_SWS_PLL) != RCC_CFGR_SWS_PLL)
			;
		return true;
	case Source::Pllr:
		RCC->CFGR &= ~(RCC_CFGR_SW_Msk);
		RCC->CFGR |= RCC_CFGR_SW_PLLR;
		while ((RCC->CFGR & RCC_CFGR_SWS_PLLR) != RCC_CFGR_SWS_PLLR)
			;
		return true;
	}
	return false;
}
bool ClockSTMF446::setPLLConfig(PllConfig pllConfig)
{
	if((pllConfig.r  < 2) && (pllConfig.q  > 7))
		return false;
	if((pllConfig.q  < 2) && (pllConfig.q  > 15))
		return false;
	if((pllConfig.n  < 50) && (pllConfig.n  > 432))
		return false;
	if((pllConfig.m  < 2) && (pllConfig.m  > 63))
		return false;

	bool pllOn = (RCC->CR & RCC_CR_PLLON) == RCC_CR_PLLON;

	if(pllOn)
	{
		RCC->CR &= ~RCC_CR_PLLON;
		while((RCC->CR & RCC_CR_PLLRDY) == RCC_CR_PLLRDY)
			;
	}

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk 					| RCC_PLLCFGR_PLLN_Msk 	|
					RCC_PLLCFGR_PLLP_Msk					| RCC_PLLCFGR_PLLQ_Msk	|
					RCC_PLLCFGR_PLLR_Msk);
	RCC->PLLCFGR |= (pllConfig.m << RCC_PLLCFGR_PLLM_Pos						| pllConfig.n << RCC_PLLCFGR_PLLN_Pos 								|
					static_cast<uint32_t>(pllConfig.p) << RCC_PLLCFGR_PLLP_Pos 	| pllConfig.q << RCC_PLLCFGR_PLLQ_Pos 								|
					pllConfig.r << RCC_PLLCFGR_PLLR_Pos   						| static_cast<uint32_t>(pllConfig.source) << RCC_PLLCFGR_PLLSRC_Pos);

	if(pllOn)
	{
		RCC->CR |= RCC_CR_PLLON;
		while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY)
			;
	}

	return true;
}
bool ClockSTMF446::setAhbPrescaler(uint32_t prescaler)
{

	switch(prescaler)
	{
	case 1:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV1;
		return true;
	case 2:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV2;
		return true;
	case 4:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV4;
		return true;
	case 16:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV16;
		return true;
	case 64:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV64;
		return true;
	case 128:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV128;
		return true;
	case 256:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV256;
		return true;
	case 512:
		RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk);
		RCC->CFGR |=  RCC_CFGR_HPRE_DIV512;
		return true;
	}
	return false;
}
bool ClockSTMF446::setApb1Prescaler(uint32_t prescaler)
{
	switch(prescaler)
	{
	case 1:
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE1_DIV1;
		return true;
	case 2:
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE1_DIV2;
		return true;
	case 4:
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE1_DIV4;
		return true;
	case 16:
		RCC->CFGR &= ~(RCC_CFGR_PPRE1_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE1_DIV16;
		return true;
	}
	return false;
}
bool ClockSTMF446::setApb2Prescaler(uint32_t prescaler)
{
	switch(prescaler)
	{
	case 1:
		RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE2_DIV1;
		return true;
	case 2:
		RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE2_DIV2;
		return true;
	case 4:
		RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE2_DIV4;
		return true;
	case 16:
		RCC->CFGR &= ~(RCC_CFGR_PPRE2_Msk);
		RCC->CFGR |=  RCC_CFGR_PPRE2_DIV16;
		return true;
	}
	return false;
}
bool ClockSTMF446::setEnable(Peripheral peripheral, bool OnOff)
{
	switch(peripheral)
	{
	case Peripheral::Hse:
		(OnOff) ? RCC->CR |= RCC_CR_HSEON : RCC->CR &= ~RCC_CR_HSEON ;
		return true;
	case Peripheral::Hsi:
		(OnOff) ? RCC->CR |= RCC_CR_HSION : RCC->CR &= ~RCC_CR_HSION;
		return true;
	case Peripheral::Pll:
		(OnOff) ? RCC->CR |= RCC_CR_PLLON : RCC->CR &= ~RCC_CR_PLLON;
		return true;
	case Peripheral::GpioA:
		(OnOff) ?  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN : RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN;
		return true;
	case Peripheral::GpioB:
		(OnOff) ? RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN : RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN;
		return true;
	case Peripheral::GpioC:
		(OnOff) ? RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN : RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN;
		return true;
	case Peripheral::GpioD:
		(OnOff) ? RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN : RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN;
		return true;
	case Peripheral::Tim1:
		(OnOff) ? RCC->APB2ENR |= RCC_APB2ENR_TIM1EN : RCC->APB2ENR &= ~RCC_APB2ENR_TIM1EN;
		return true;
	case Peripheral::Tim2:
		(OnOff) ? RCC->APB1ENR |= RCC_APB1ENR_TIM2EN : RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
		return true;
	case Peripheral::Tim3:
		(OnOff) ? RCC->APB1ENR |= RCC_APB1ENR_TIM3EN : RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;
		return true;
	case Peripheral::Tim4:
		(OnOff) ? RCC->APB1ENR |= RCC_APB1ENR_TIM4EN : RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN;
		return true;
	case Peripheral::Tim14:
		(OnOff) ? RCC->APB1ENR |= RCC_APB1ENR_TIM14EN : RCC->APB1ENR &= ~RCC_APB1ENR_TIM14EN;
		return true;
	case Peripheral::Usart2:
		(OnOff) ? RCC->APB1ENR |= RCC_APB1ENR_USART2EN : RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
		return true;
	case Peripheral::Pwr:
		(OnOff) ? RCC->APB1ENR |= RCC_APB1ENR_PWREN : RCC->APB1ENR &= ~RCC_APB1ENR_PWREN;
		return true;
	}
	return false;
}
