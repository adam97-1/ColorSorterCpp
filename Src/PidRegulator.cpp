
#include "PidRegulator.hpp"
#include "Function.hpp"

PidRegulator::PidRegulator(const PidRegulator::PidParam &pidParam, uint32_t diffMsTime)
: m_pidPara{pidParam}, m_diffMsTime{diffMsTime}
{

}

PidRegulator::PidRegulator(float kp, float ki, float kd, bool zeroDetect,
		float maxIntegral, float maxInValue, float maxOutValue , uint32_t diffMsTime)
		: m_pidPara{.kp = kp , .ki = ki, .kd = kd, .zeroDetect = zeroDetect,
		  .maxIntegral = maxIntegral, .maxInValue = maxInValue, .maxOutValue = maxOutValue},
		  m_diffMsTime{diffMsTime}
{

}

PidRegulator::~PidRegulator()
{

}

float PidRegulator::calculate(float targetValue, float actualValue)
{


	targetValue = saturation(targetValue, m_pidPara.maxInValue);

	float errorValue = 0;

	if(m_pidPara.zeroDetect)
		errorValue = Function::minRadiusDiastance(actualValue, targetValue);
	else
		errorValue = targetValue - actualValue;

	m_errorIntegral += errorValue * (m_diffMsTime * 0.001f);
	m_errorIntegral = saturation(m_errorIntegral, m_pidPara.maxIntegral);

	float errorDiffValue = (m_oldValueError - errorValue) / (m_diffMsTime * 0.001f);
	m_oldValueError = errorValue;

	float out = (m_pidPara.kp * errorValue + m_pidPara.ki * m_errorIntegral	+ m_pidPara.kd * errorDiffValue);
	out = saturation(out, m_pidPara.maxOutValue);

	if (out >= m_pidPara.maxOutValue || out <= -m_pidPara.maxOutValue)
		m_errorIntegral -= errorValue * (m_diffMsTime * 0.001f);

	return out;
}

void PidRegulator::setKp(float kp)
{
	m_pidPara.kp = kp;
}
float PidRegulator::getKp() const
{
	return m_pidPara.kp;
}
void PidRegulator::setKi(float ki)
{
	m_pidPara.ki = ki;
}
float PidRegulator::getKi() const
{
	return m_pidPara.ki;
}
void PidRegulator::setKd(float kd)
{
	m_pidPara.kd = kd;
}
float PidRegulator::getKd() const
{
	return m_pidPara.kd;
}
void PidRegulator::setMaxInValue(float maxValue)
{
	m_pidPara.maxInValue = maxValue;
}
float PidRegulator::getMaxInValue() const
{
	return m_pidPara.maxInValue;
}
void PidRegulator::setMaxIntegral(float maxValue)
{
	m_pidPara.maxIntegral = maxValue;
}
float PidRegulator::getMaxIntegral() const
{
	return m_pidPara.maxIntegral;
}
void PidRegulator::setMaxOutValue(float maxValue)
{
	m_pidPara.maxOutValue = maxValue;
}
float PidRegulator::getMaxOutValue() const
{
	return m_pidPara.maxOutValue;
}
void PidRegulator::setDiffTime(uint32_t msTimme)
{
	m_diffMsTime  = msTimme;
}
uint32_t PidRegulator::getDiffTime() const
{
	return m_diffMsTime;
}
void PidRegulator::setZeroDetect(bool OnOff)
{
	m_pidPara.zeroDetect = OnOff;
}
bool PidRegulator::getZeroDetect() const
{
	return m_pidPara.zeroDetect;
}
void PidRegulator::resetIntegral()
{
	m_errorIntegral = 0;
}

float PidRegulator::saturation(float value, float maxValue) const
{
	if (value > maxValue)
		value = maxValue;
	else if (value < -maxValue)
		value = -maxValue;
	return value;
}

void PidRegulator::setPidParam(const PidRegulator::PidParam &pidParam)
{
	m_pidPara = pidParam;
}

const PidRegulator::PidParam & PidRegulator::getPidParam() const
{
	return m_pidPara;
}

