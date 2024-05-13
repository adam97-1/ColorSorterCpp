#include "Motor.hpp"
#include "Timer/Timer.hpp"
#include "TaskMenager.hpp"

Motor::Motor()
 {
	setPeriod(1);
	setPriority(1);
	TaskMenager::getInstance().addTask(m_encoder);

 }
Motor::Motor(const Config &config, uint32_t period, uint32_t priority) : m_config{config}
{
	setPeriod(period);
	setPriority(priority);

	m_encoder.setTimer(m_config.encoder);
	m_encoder.setMaxValue(2472);

	m_speedPid.setPidParam(config.speedPid);
	m_speedPid.setDiffTime(period);

	m_positionPid.setPidParam(config.positionPid);
	m_positionPid.setDiffTime(period);

	TaskMenager::getInstance().addTask(m_encoder);
}

Motor::~Motor()
{

}

void Motor::setTargetSpeed(float speed)
{
	m_targetSpeed = speed;
}

float Motor::getSpeed() const
{
	return m_encoder.getSpeed();
}

float Motor::getTargetSpeed() const
{
	return m_targetSpeed;
}


void Motor::setTargetPosition(float position)
{
	m_targetPosition = position;
}

float Motor::getTargetPosition() const
{
	return m_targetPosition;
}

float Motor::getPosition() const
{
	return m_encoder.getPosition();
}

void Motor::setControlMode(ControlMode controlMode)
{
	m_controlMode = controlMode;
}
Motor::ControlMode Motor::getControlMode() const
{
	return m_controlMode;
}

void Motor::loop()
{
	float speedOut = 0;
	float out = 0;

	switch(m_controlMode)
	{
	case ControlMode::Position:
		speedOut = m_positionPid.calculate(m_targetPosition, m_encoder.getPosition());
		out = m_speedPid.calculate(speedOut, m_encoder.getSpeed());
		break;
	case ControlMode::Speed:
		m_positionPid.resetIntegral();
		out = m_speedPid.calculate(m_targetSpeed, m_encoder.getSpeed());
		break;
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
void Motor::setConfig(const Motor::Config &config)
{
	m_config = config;
	m_encoder.setTimer(m_config.encoder);
	m_encoder.setPeriod(getPeriod());
	m_encoder.setPriority(getPriority());
	m_encoder.setMaxValue(2472);

	m_speedPid.setPidParam(config.speedPid);
	m_speedPid.setDiffTime(getPeriod());

	m_positionPid.setPidParam(config.positionPid);
	m_positionPid.setDiffTime(getPeriod());
}
const Motor::Config &Motor::getConfig() const
{
	return m_config;
}
void Motor::setPeriod(uint32_t period)
{
	m_encoder.setPeriod(period);
	Task::setPeriod(period);
}
void Motor::setPriority(uint32_t priority)
{
	m_encoder.setPriority(priority);
	Task::setPriority(priority);
}
