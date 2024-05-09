#include "Motor.hpp"]
#include "Timer/Timer.hpp"

Motor::Motor(Config config, uint32_t period, uint32_t priority) : m_config{config}
{
	setPeriod(period);
	setPriority(priority);
	m_endocer = new Encoder(config.endoder, period, priority);
}

Motor::~Motor()
{
	delete m_endocer;
}

void Motor::setTargetSpeed(float speed)
{
	m_targetSpeed = speed;
}

float Motor::getTargetSpeed()
{
	return m_endocer->getSpeed();
}

void Motor::setTargetPosition(float position)
{
	m_targetPosition = position;
}
float Motor::getTargetPosition()
{
	return m_endocer->getPosition();
}

void Motor::setControlMode(ControlMode controlMode)
{
	m_controlMode = controlMode;
}
Motor::ControlMode Motor::getControlMode()
{
	return m_controlMode;
}

void Motor::loop()
{
	float speedOut = 0;
	float out = 0;

	switch(m_controlMode)
	{
//	case ControlMode::Position:
//		speedOut = MotorSelPositionRegulator_Calculate(m_position, m_endocer->getPosition());
//		out = MotorSelSpeedRegulator_Calculate(speedOut, m_endocer->getSpeed());
//		break;
//	case ControlMode::Speed:
//		out = MotorSelSpeedRegulator_Calculate(m_targetSpeed, m_endocer->getSpeed());
//		break;
	}

	if (out > 0)
	{
		Timer::getInstance().setCompareValue(m_config.out1.timer, m_config.out1.chanel, 0);
		Timer::getInstance().setCompareValue(m_config.out2.timer, m_config.out2.chanel, static_cast<uint32_t>(out));
	}
	else
	{
		Timer::getInstance().setCompareValue(m_config.out1.timer, m_config.out1.chanel, static_cast<uint32_t>(-out));
		Timer::getInstance().setCompareValue(m_config.out2.timer, m_config.out2.chanel, 0);
	}
}

