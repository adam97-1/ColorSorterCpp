#include "Encoder.hpp"
#include "Timer/Timer.hpp"
#include "Function.hpp"

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
	static float oldPosition = 0;

		m_position = Timer::getInstance().getCounterValue(m_timer);

		float diffPosition = Function::minRadiusDiastance(oldPosition, m_position);

		m_speed = diffPosition / (getPeriod() * 0.001f);

		oldPosition = m_position;
}
float Encoder::getSpeed()
{
	return m_speed;
}
float Encoder::getPosition()
{
	return m_position;
}
void Encoder::setMaxValue(uint32_t value)
{
	m_maxValue = value;
}
uint32_t Encoder::getMaxValue()
{
	return m_maxValue;
}

