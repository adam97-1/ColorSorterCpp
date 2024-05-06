#pragma once

#include <cstdint>

class IGpio
{
public:
	enum class Port : uint32_t
	{
		A = 0,
		B = 1,
		C = 2,
		D = 3,
		E = 4,
		F = 5,
		G = 6,
		H = 7

	};

	struct Config
	{
		enum class Mode : uint32_t
		{
			Input 				= 0,
			Output 				= 1,
			AlternateFunction	= 2,
			Analog				= 3
		};
		enum class Typ : uint32_t
		{
			PushPull			= 0,
			OpenDrain			= 1
		};
		enum class Speed : uint32_t
		{
			Low					= 0,
			Medium				= 1,
			Fast				= 2,
			High				= 3
		};
		enum class Polarization : uint32_t
		{
			NoPullUpNoPullDown	= 0,
			PullUp				= 1,
			PullDown			= 2,

		};

		Mode mode {Mode::Input};
		Typ typ {Typ::PushPull};
		Speed speed {Speed::Low};
		Polarization polarization {Polarization::NoPullUpNoPullDown};
		uint32_t alternateFunction;
	};

	enum class State : uint32_t
	{
		Low 	= 0,
		High 	= 1,
		Unknow  = 3
	};

	virtual bool setConfig(Port port, uint32_t pin, Config config) = 0;
	virtual bool setState(Port port, uint32_t pin, State state) = 0;
	virtual State getState(Port port, uint32_t pin) = 0;
};
