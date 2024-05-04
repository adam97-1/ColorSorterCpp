#pragma once

#include <cstdint>

class IFlash
{
public:
	enum class Latency : uint32_t
	{
		WS0 = 0,
		WS1 = 1,
		WS2 = 2,
		WS3 = 3,
		WS4 = 4,
		WS5 = 5,
		WS6 = 6,
		WS7 = 7,
		WS8 = 8
	};

	enum class Parametr : uint32_t
	{
		PREFT,
		IC,
		DC
	};

	virtual bool setLatency(Latency latency) = 0;
	virtual bool setParametr(Parametr parametr, bool OnOff) = 0;


};
