#include "Timer/TimerF446.hpp"
#include <stm32f446xx.h>

TimerF446::TimerF446()
{

}

TimerF446::~TimerF446()
{

}
void * TimerF446::getTimer(ITimer::Timer  timer)
{
	switch(timer)
	{
	case ITimer::Timer::Tim1:
		return TIM1;
		break;
	case ITimer::Timer::Tim2:
		return TIM2;
		break;
	case ITimer::Timer::Tim3:
		return TIM3;
		break;
	case ITimer::Timer::Tim4:
		return TIM4;
		break;
	case ITimer::Timer::Tim5:
		return TIM5;
		break;
	case ITimer::Timer::Tim6:
		return TIM6;
		break;
	case ITimer::Timer::Tim7:
		return TIM7;
		break;
	case ITimer::Timer::Tim8:
		return TIM8;
		break;
	case ITimer::Timer::Tim9:
		return TIM9;
		break;
	case ITimer::Timer::Tim10:
		return TIM10;
		break;
	case ITimer::Timer::Tim11:
		return TIM11;
		break;
	case ITimer::Timer::Tim12:
		return TIM12;
		break;
	case ITimer::Timer::Tim13:
		return TIM13;
		break;
	case ITimer::Timer::Tim14:
		return TIM14;
		break;
	default:
		return nullptr;
	}
}
bool TimerF446::setEnable(ITimer::Timer timer, bool OnOff)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;

	(OnOff) ? tim->CR1 |= TIM_CR1_CEN : tim->CR1 &= ~TIM_CR1_CEN;
	return true;
}
bool TimerF446::setSourceMode(ITimer::Timer timer, ITimer::SourceModeInternal sourceMode)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;
	tim->SMCR &= ~TIM_SMCR_SMS_Msk;
	return true;
}
bool TimerF446::setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal1 sourceMode)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;
	if(sourceMode.inputFilter > 16)
		return false;

	tim->CCMR1 &= ~(TIM_CCMR1_CC2S_Msk);
	tim->CCMR1 |= (1 << TIM_CCMR1_CC2S_Pos);

	tim->CCMR1 &= ~(TIM_CCMR1_IC2F_Msk);
	tim->CCMR1 |= (sourceMode.inputFilter << TIM_CCMR1_IC2F_Pos);

	switch(sourceMode.edgeDetect)
	{
	case ITimer::SourceModeExternal1::EdgeDetect::NoInvertedRising:
		tim->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
		break;
	case ITimer::SourceModeExternal1::EdgeDetect::InvertedFalling:
		tim->CCER &= ~(TIM_CCER_CC2NP);
		tim->CCER |= (TIM_CCER_CC2P);
		break;
	case ITimer::SourceModeExternal1::EdgeDetect::NoInvertedBoth:
		tim->CCER |= (TIM_CCER_CC2NP);
		tim->CCER |= (TIM_CCER_CC2P);
		break;
	}

	tim->SMCR &= ~TIM_SMCR_SMS_Msk;
	tim->SMCR |= (0b111 <<TIM_SMCR_SMS_Pos);

	tim->SMCR &= ~(TIM_SMCR_ECE);

	tim->SMCR &= ~TIM_SMCR_TS_Msk;
	tim->SMCR |= (0b110 <<TIM_SMCR_TS_Pos);
	return true;
}
bool TimerF446::setSourceMode(ITimer::Timer timer, ITimer::SourceModeExternal2 sourceMode)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;
	if(sourceMode.inputFilter > 16)
		return false;

	if(sourceMode.presacaler > 8 || sourceMode.presacaler < 1)
		return false;

	tim->SMCR &= ~(TIM_SMCR_ETF_Msk);
	tim->SMCR |= (sourceMode.inputFilter << TIM_SMCR_ETF_Pos);

	tim->SMCR &= ~(TIM_SMCR_ETPS_Msk);
	switch(sourceMode.presacaler)
	{
	case 1:
		tim->SMCR |= (0 << TIM_SMCR_ETPS_Pos);
		break;
	case 2:
		tim->SMCR |= (1 << TIM_SMCR_ETPS_Pos);
		break;
	case 4:
		tim->SMCR |= (2 << TIM_SMCR_ETPS_Pos);
		break;
	case 8:
		tim->SMCR |= (4 << TIM_SMCR_ETPS_Pos);
		break;
	}
	(sourceMode.edgeDetect == ITimer::SourceModeExternal2::EdgeDetect::HighOrRising) ?
			(tim->SMCR &= ~(TIM_SMCR_ETP))
			: (tim->SMCR |= (TIM_SMCR_ETP));

	tim->SMCR |= (TIM_SMCR_ECE);
	return true;
}
bool TimerF446::setMode(ITimer::Timer timer, ITimer::PwmMode mode)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;

	tim->CR1 &= ~TIM_CR1_CMS_Msk;
	tim->CR1 |= (static_cast<uint32_t>(mode) << TIM_CR1_CMS_Pos);

	return true;
}
bool TimerF446::setMode(ITimer::Timer timer, ITimer::ModeEncoder mode)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;

	tim->CCMR1 &= ~(TIM_CCMR1_CC1S_Msk | TIM_CCMR1_CC2S_Msk);
	tim->CCMR1 |= (1 << TIM_CCMR1_CC1S_Pos | 1 << TIM_CCMR1_CC2S_Pos);

	switch(mode.edgeDetectT1)
	{
	case ITimer::ModeEncoder::EdgeDetect::NoInvertedRising:
		tim->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);
		break;
	case ITimer::ModeEncoder::EdgeDetect::InvertedFalling:
		tim->CCER &= ~(TIM_CCER_CC1NP);
		tim->CCER |= (TIM_CCER_CC1P);
		break;
	case ITimer::ModeEncoder::EdgeDetect::NoInvertedBoth:
		tim->CCER |= (TIM_CCER_CC1NP);
		tim->CCER |= (TIM_CCER_CC1P);
		break;
	}
	switch(mode.edgeDetectT2)
	{
	case ITimer::ModeEncoder::EdgeDetect::NoInvertedRising:
		tim->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP);
		break;
	case ITimer::ModeEncoder::EdgeDetect::InvertedFalling:
		tim->CCER &= ~(TIM_CCER_CC2NP);
		tim->CCER |= (TIM_CCER_CC2P);
		break;
	case ITimer::ModeEncoder::EdgeDetect::NoInvertedBoth:
		tim->CCER |= (TIM_CCER_CC2NP);
		tim->CCER |= (TIM_CCER_CC1P);
		break;
	}

	tim->SMCR &= ~TIM_SMCR_SMS_Msk;
	tim->SMCR |= (static_cast<uint32_t>(mode.mode) <<TIM_SMCR_SMS_Pos);

	tim->SMCR &= ~(TIM_SMCR_ECE);

	return true;

}
uint32_t TimerF446::getCounterValue(ITimer::Timer timer)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return 0;

	return tim->CNT;
}
bool TimerF446::setCompareValue(ITimer::Timer timer, ITimer::Chanel chanel, uint32_t value)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;
	switch(chanel)
	{
	case ITimer::Chanel::Ch1:
		tim->CCR1 = value;
		return true;
	case ITimer::Chanel::Ch2:
		tim->CCR1 = value;
		return true;
	case ITimer::Chanel::Ch3:
		tim->CCR1 = value;
		return true;
	case ITimer::Chanel::Ch4:
		tim->CCR1 = value;
		return true;
	default:
		return false;
	}
}

bool TimerF446::setReloadValue(ITimer::Timer timer, uint32_t value)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return false;

	tim->ARR = value;
	return true;

}

uint32_t TimerF446::getReloadValue(ITimer::Timer timer)
{
	TIM_TypeDef *tim = static_cast<TIM_TypeDef*>(getTimer(timer));

	if(!tim)
		return 0;

	return tim->ARR;
}
