#pragma once
#include <cstdint>

class PidRegulator
{
public:

	struct PidParam
	{
		float kp {1};
		float ki {0};
		float kd {0};
		bool zeroDetect {false};
		float maxIntegral {100000000};
		float maxInValue {100000000};
		float maxOutValue {100000000};
	};

	PidRegulator(const PidParam &pidParam, uint32_t diffMsTime = 1);
	PidRegulator(float kp = 1, float ki = 0, float kd = 0, bool zeroDetect = false,
			float maxIntegral = 100000000, float maxInValue = 100000000, float maxOutValue = 100000000,
			uint32_t diffMsTime = 1);
	virtual ~PidRegulator();

	float calculate(float targetValue, float actualValue);

	void setPidParam(const PidParam &pidParam);
	const PidParam & getPidParam() const;
	void setKp(float kp);
	float getKp() const;
	void setKi(float ki);
	float getKi() const;
	void setKd(float kd);
	float getKd() const;
	void setMaxInValue(float maxValue);
	float getMaxInValue() const;
	void setMaxIntegral(float maxValue);
	float getMaxIntegral() const;
	void setMaxOutValue(float maxValue);
	float getMaxOutValue() const;
	void setDiffTime(uint32_t msTimme);
	uint32_t getDiffTime() const;
	void setZeroDetect(bool OnOff);
	bool getZeroDetect() const;
	void resetIntegral();

private:
	float saturation(float value, float maxValue) const;

	PidParam m_pidPara;
	uint32_t m_diffMsTime;
	float m_errorIntegral {0};
	float m_oldValueError {0};
};
