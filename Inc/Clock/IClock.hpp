#pragma once
#include <cstdint>

class IClock
{
public:
	struct PllConfig
	{
		uint8_t M;
		uint8_t N;
		uint8_t P;
		uint8_t Q;
		uint8_t R;
	};

	enum class Sorce
	{
		HSE,
		HSI,
		PLL,
		PLLR
	};

	virtual void setSorce(Sorce sorce) = 0;
	virtual void setPLLConfig(PllConfig pllConfig) = 0;
	virtual void setAhbPrescaler(uint16_t prescaler) = 0;
	virtual void setApb1Prescaler(uint16_t prescaler) = 0;
	virtual void setApb2Prescaler(uint16_t prescaler) = 0;


};
