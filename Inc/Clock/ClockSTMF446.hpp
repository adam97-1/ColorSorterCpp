#pragma once
#include "Clock.hpp"

class ClockSTMF446 : public IClock
{
public:
	ClockSTMF446();
	virtual ~ClockSTMF446();

	bool setSource(Source source) override;
	bool setPLLConfig(PllConfig pllConfig) override;
	bool setAhbPrescaler(uint32_t prescaler) override;
	bool setApb1Prescaler(uint32_t prescaler) override;
	bool setApb2Prescaler(uint32_t prescaler) override;
	bool setEnable(Peripheral peripheral, bool OnOff) override;

};

