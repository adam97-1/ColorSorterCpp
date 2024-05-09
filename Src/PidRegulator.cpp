
#include "PidRegulator.hpp"
#include "Function.hpp"

PidRegulator::PidRegulator(float kp, float ki, float kd, bool zeroDetect,
		float maxIntegral, float maxInValue, float maxOutValue , uint32_t diffMsTime)
		: m_Kp{kp}, m_Ki{ki}, m_Kd{kd}, m_zeroDetect{zeroDetect},
		  m_maxIntegral{maxIntegral}, m_maxInValue{maxInValue}, m_maxOutValue{maxOutValue},
		  m_diffMsTime{diffMsTime}
{

}

PidRegulator::~PidRegulator()
{

}

float PidRegulator::calculate(float targetValue, float actualValue)
{


	targetValue = saturation(targetValue, m_maxInValue);

	float errorValue = 0;

	if(m_zeroDetect)
		errorValue = Function::minRadiusDiastance(actualValue, targetValue);
	else
		errorValue = targetValue - actualValue;

	m_errorIntegral += errorValue * (m_diffMsTime * 0.001f);
	m_errorIntegral = saturation(m_errorIntegral, m_maxIntegral);

	float errorDiffValue = (m_oldValueError - errorValue) / (m_diffMsTime * 0.001f);
	m_oldValueError = errorValue;

	float out = (m_Kp * errorValue + m_Ki * m_errorIntegral	+ m_Kd * errorDiffValue);
	out = saturation(out, m_maxOutValue);

	if (out >= m_maxOutValue || out <= -m_maxOutValue)
		m_errorIntegral -= errorValue * (m_diffMsTime * 0.001f);

	return out;
}

void PidRegulator::setKp(float kp)
{
	m_Kp = kp;
}
float PidRegulator::getKp()
{
	return m_Kp;
}
void PidRegulator::setKi(float ki)
{
	m_Ki = ki;
}
float PidRegulator::getKi()
{
	return m_Ki;
}
void PidRegulator::setKd(float kd)
{
	m_Kd = kd;
}
float PidRegulator::getKd()
{
	return m_Kd;
}
void PidRegulator::setMaxInValue(float maxValue)
{
	m_maxInValue = maxValue;
}
float PidRegulator::getMaxInValue()
{
	return m_maxInValue;
}
void PidRegulator::setMaxIntegral(float maxValue)
{
	m_maxIntegral = maxValue;
}
float PidRegulator::getMaxIntegral()
{
	return m_maxIntegral;
}
void PidRegulator::setMaxOutValue(float maxValue)
{
	m_maxOutValue = maxValue;
}
float PidRegulator::getMaxOutValue()
{
	return m_maxOutValue;
}
void PidRegulator::setDiffTime(uint32_t msTimme)
{
	m_diffMsTime  =msTimme;
}
uint32_t PidRegulator::getDiffTime()
{
	return m_diffMsTime;
}
void PidRegulator::setZeroDetect(bool OnOff)
{
		m_zeroDetect = OnOff;
}
bool PidRegulator::getZeroDetect()
{
	return m_zeroDetect;
}
void PidRegulator::resetIntegral()
{
	m_errorIntegral = 0;
}

float PidRegulator::saturation(float value, float maxValue)
{
	if (value > maxValue)
		value = maxValue;
	else if (value < -maxValue)
		value = -maxValue;
	return value;
}

void PidRegulator::setPidParam(Pid pid)
{
	m_Kp = pid.kp;
	m_Ki = pid.ki;
	m_Kd = pid.kd;
	m_maxInValue = pid.maxInValue;
	m_maxIntegral = pid.maxIntegral;
	m_maxOutValue = pid.maxOutValue;
	m_zeroDetect = pid.zeroDetect;
}

