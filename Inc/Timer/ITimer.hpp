#pragma once
#include <cstdint>

class ITimer
{
public:
	enum class Timer : uint32_t
	{
		Tim1 = 1,
		Tim2 = 2,
		Tim3 = 3,
		Tim4 = 4,
		Tim5 = 5,
		Tim6 = 6,
		Tim7 = 7,
		Tim8 = 8,
		Tim9 = 9,
		Tim10 = 10,
		Tim11 = 11,
		Tim12 = 12,
		Tim13 = 13,
		Tim14 = 14
	};

	struct SourceModeInternal
	{

	};

	struct SourceModeExternal1
	{

		enum class EdgeDetect : uint32_t
		{
			NoInvertedRising	= 0,
			InvertedFalling		= 1,
			NoInvertedBoth		= 3
		};
		uint32_t inputFilter;
		EdgeDetect edgeDetect;

	};

	struct SourceModeExternal2
	{

		enum class EdgeDetect : uint32_t
		{
			HighOrising		= 0,
			LowOrFalling	= 1,
		};
		uint32_t inputFilter;
		EdgeDetect edgeDetect;
		uint32_t presacaler;

	};

	struct ModePwm
	{

	};

	struct ModeEncoder
	{

	};

	virtual bool setEnable(Timer timer, bool OnOff) = 0;
	virtual bool setSourceMode(Timer timer, SourceModeInternal sourceMode) = 0;
	virtual bool setSourceMode(Timer timer, SourceModeExternal1 sourceMode) = 0;
	virtual bool setSourceMode(Timer timer, SourceModeExternal2 sourceMode) = 0;
	virtual bool setMode(Timer timer, ModePwm mode) = 0;
	virtual bool setMode(Timer timer, ModeEncoder mode) = 0;

};
