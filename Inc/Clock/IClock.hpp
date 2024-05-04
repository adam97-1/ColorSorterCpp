#pragma once
#include <cstdint>

class IClock
{
public:
	struct PllConfig
	{
		enum class P : uint32_t
		{
			P2 = 2,
			P4 = 4,
			P6 = 6,
			P8 = 8
		};
		enum class Source : uint32_t
		{
			Hsi = 0,
			Hse = 1
		};

		uint32_t m;
		uint32_t n;
		P p;
		uint32_t q;
		uint32_t r;
		Source source;
	};

	enum class Source
	{
		Hse,
		Hsi,
		Pll,
		Pllr
	};

	enum class Peripheral
	{
		Hse,
		Hsi,
		Pll,
		GpioA,
		GpioB,
		GpioC,
		GpioD,
		Tim1,
		Tim2,
		Tim3,
		Tim4,
		Tim14,
		Usart2,
		Pwr
	};


	virtual bool setSource(Source source) = 0;
	virtual bool setPLLConfig(PllConfig pllConfig) = 0;
	virtual bool setAhbPrescaler(uint32_t prescaler) = 0;
	virtual bool setApb1Prescaler(uint32_t prescaler) = 0;
	virtual bool setApb2Prescaler(uint32_t prescaler) = 0;
	virtual bool setEnable(Peripheral peripheral, bool OnOff) = 0;

};
