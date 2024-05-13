#include "Encoder.hpp"
#include "Timer/Timer.hpp"
#include "Function.hpp"
#include <cmath>

Encoder::Encoder(ITimer::Timer timer, uint32_t period, uint32_t priority) : m_timer{timer}
{
	setPeriod(period);
	setPriority(priority);
}

Encoder::~Encoder()
{

}

void Encoder::loop()
{
		m_position = Timer::getInstance().getCounterValue(m_timer)* 2 * M_PI / m_maxValue;


		float diffPosition = Function::minRadiusDiastance(m_oldPosition, m_position);

		m_speed = (m_speed*100 + diffPosition / (getPeriod() * 0.001f))/101;

		m_oldPosition = m_position;
}
float Encoder::getSpeed() const
{
	return m_speed;
}
float Encoder::getPosition() const
{
	return m_position;
}
void Encoder::setMaxValue(uint32_t value)
{
	m_maxValue = value;
}
uint32_t Encoder::getMaxValue() const
{
	return m_maxValue;
}
void Encoder::setTimer(ITimer::Timer timer)
{
	m_timer = timer;
}
ITimer::Timer Encoder::getTimer() const
{
	return m_timer;
}

