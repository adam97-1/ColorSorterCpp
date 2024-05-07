#pragma once

#include "Task.hpp"
#include "Gpio/IGpio.hpp"
#include "Timer/ITimer.hpp"
#include <cstdint>
#include <functional>

class ColorDetector : public Task
{
public:
	struct Config
	{
		IGpio::Gpio s0;
		IGpio::Gpio s1;
		IGpio::Gpio s2;
		IGpio::Gpio s3;
		IGpio::Gpio led;
		ITimer::Timer timInput;
	};

	struct Color
	{
		uint32_t none;
		uint32_t red;
		uint32_t green;
		uint32_t blue;
	};

	ColorDetector(Config config, uint32_t period, uint32_t priority);
	virtual ~ColorDetector();

    template<void (*Function)(Color)>
    void setColorReady();

    template<class C, void (C::*Function)(Color)>
    void setColorReady(C *instance);

	void loop() override;
	void measurementColor();

private:
	enum class Filter
	{
		None,
		Red,
		Green,
		Blue
	};

	enum class Prescaler
	{
		_0,
		_2,
		_80,
		_100
	};

	void setColorPrescaler(Prescaler prescaler);
	void setColorFilter(Filter filter);
	void setStateLed(bool OnOff);

	Config m_config;
	std::function<void(Color)> m_colorReady;
	bool m_isColorMeasurment {false};
	Color m_color;

};
