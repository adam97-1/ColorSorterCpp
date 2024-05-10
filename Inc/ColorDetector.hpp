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
		uint32_t none	{0};
		uint32_t red	{0};
		uint32_t green	{0};
		uint32_t blue	{0};
	};

	ColorDetector();
	ColorDetector(const Config &config, uint32_t period = 1, uint32_t priority = 1);
	virtual ~ColorDetector();

	template<typename C>
	void setColorReady(C &&funcMetod)
	{
		m_colorReady = funcMetod;
	}

	void loop() override;
	const Config &getConfig() const;
	void setConfig(const Config &config);
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
	std::function<void(const Color&)> m_colorReady;
	bool m_isColorMeasurment {false};
	Color m_color;

};
