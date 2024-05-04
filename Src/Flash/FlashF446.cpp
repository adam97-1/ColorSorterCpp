#include "Flash/FlashF446.hpp"
#include <stm32f446xx.h>

FlashF446::FlashF446()
{

}

FlashF446::~FlashF446()
{

}
bool FlashF446::setLatency(IFlash::Latency latency)
{
	switch(latency)
	{
	case IFlash::Latency::WS0:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_0WS;
		return true;
	case IFlash::Latency::WS1:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_1WS;
		return true;
	case IFlash::Latency::WS2:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_2WS;
		return true;
	case IFlash::Latency::WS3:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
		return true;
	case IFlash::Latency::WS4:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_4WS;
		return true;
	case IFlash::Latency::WS5:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
		return true;
	case IFlash::Latency::WS6:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_6WS;
		return true;
	case IFlash::Latency::WS7:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_7WS;
		return true;
	case IFlash::Latency::WS8:
		FLASH->ACR &= FLASH_ACR_LATENCY_Msk;
		FLASH->ACR |= FLASH_ACR_LATENCY_8WS;
		return true;
	}
	return false;
}
bool FlashF446::setParametr(IFlash::Parametr parametr, bool OnOff)
{
	switch(parametr)
	{
	case IFlash::Parametr::DC:
		(OnOff) ? FLASH->ACR|= FLASH_ACR_DCEN : FLASH->ACR &= ~FLASH_ACR_DCEN;
		return true;
	case IFlash::Parametr::IC:
		(OnOff) ? FLASH->ACR|= FLASH_ACR_ICEN : FLASH->ACR &= ~FLASH_ACR_ICEN;
		return true;
	case IFlash::Parametr::PREFT:
		(OnOff) ? FLASH->ACR|= FLASH_ACR_PRFTEN : FLASH->ACR &= ~FLASH_ACR_PRFTEN;
		return true;
	}
	return false;
}

