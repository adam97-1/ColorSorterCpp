#pragma once
#include <cstdint>

class PidRegulator
{
public:

	struct Pid
	{
		float kp {1};
		float ki {0};
		float kd {0};
		bool zeroDetect {false};
		float maxIntegral {100000000};
		float maxInValue {100000000};
		float maxOutValue {100000000};
	};

	PidRegulator(float kp = 1, float ki = 0, float kd = 0, bool zeroDetect = false,
			float maxIntegral = 100000000, float maxInValue = 100000000, float maxOutValue = 100000000,
			uint32_t diffMsTime = 1);
	virtual ~PidRegulator();

	float calculate(float targetValue, float actualValue);

	void setPidParam(Pid pid);
	void setKp(float kp);
	float getKp();
	void setKi(float ki);
	float getKi();
	void setKd(float kd);
	float getKd();
	void setMaxInValue(float maxValue);
	float getMaxInValue();
	void setMaxIntegral(float maxValue);
	float getMaxIntegral();
	void setMaxOutValue(float maxValue);
	float getMaxOutValue();
	void setDiffTime(uint32_t msTimme);
	uint32_t getDiffTime();
	void setZeroDetect(bool OnOff);
	bool getZeroDetect();
	void resetIntegral();

private:
	float saturation(float value, float maxValue);

	float m_Kp;
	float m_Ki;
	float m_Kd;
	float m_maxIntegral;
	float m_maxInValue;
	float m_maxOutValue;
	uint32_t m_diffMsTime;
	float m_errorIntegral {0};
	float m_oldValueError {0};
	bool m_zeroDetect;
};
