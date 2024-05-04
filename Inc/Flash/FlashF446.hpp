#pragma once

#include "Flash/Flash.hpp"

class FlashF446 : public IFlash
{
public:
	FlashF446();
	virtual ~FlashF446();

	bool setLatency(IFlash::Latency latency) override;
	bool setParametr(IFlash::Parametr parametr, bool OnOff) override;
};

