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

	enum class Chanel : uint32_t
	{
		Ch1 = 1,
		Ch2 = 2,
		Ch3 = 3,
		Ch4 = 4
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
			HighOrRising	= 0,
			LowOrFalling	= 1,
		};
		uint32_t inputFilter;
		EdgeDetect edgeDetect;
		uint32_t presacaler;

	};

	enum class PwmMode : uint32_t
	{
		EdgeAligned 	= 0,
		CenterAligned1 	= 1,
		CenterAligned2 	= 2,
		CenterAligned3 	= 3
	};

	struct ModeEncoder
	{
		enum class EdgeDetect : uint32_t
		{
			NoInvertedRising	= 0,
			InvertedFalling		= 1,
			NoInvertedBoth		= 3
		};

		enum class Mode : uint32_t
		{
			Ti2DependingTi1 	= 1,
			Ti1DependingTi2 	= 2,
			BothDependingTi		= 3
		};

		uint32_t inputFilter;
		EdgeDetect edgeDetectT1;
		EdgeDetect edgeDetectT2;
		Mode mode;
	};

	enum class CompareMode : uint32_t
	{
		Frozen			= 0,
		SetActiveLevel	= 1,
		SetInactiveLeve = 2,
		Togle			= 3,
		ForceInactive	= 4,
		ForceActive		= 5,
		Pwm1			= 6,
		Pwm2			= 7
	};

	virtual bool setEnable(Timer timer, bool OnOff) = 0;
	virtual bool setSourceMode(Timer timer, SourceModeInternal sourceMode) = 0;
	virtual bool setSourceMode(Timer timer, SourceModeExternal1 sourceMode) = 0;
	virtual bool setSourceMode(Timer timer, SourceModeExternal2 sourceMode) = 0;
	virtual bool setMode(Timer timer, PwmMode mode) = 0;
	virtual bool setMode(Timer timer, ModeEncoder mode) = 0;
	virtual bool setCounterValue(Timer timer, uint32_t value) = 0;
	virtual uint32_t getCounterValue(Timer timer) = 0;
	virtual bool setReloadValue(Timer timer, uint32_t value) = 0;
	virtual uint32_t getReloadValue(Timer timer) = 0;
	virtual bool setCompareValue(Timer timer, Chanel chanel, uint32_t value) = 0;
	virtual bool setEnableOutput(Timer timer, Chanel chanel, bool OnOff) = 0;
	virtual bool setEnableCompare(Timer timer, Chanel chanel, bool OnOff) = 0;
	virtual bool setCompareMode(Timer timer, Chanel chanel, CompareMode mode) = 0;

};
