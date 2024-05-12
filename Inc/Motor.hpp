#pragma once
#include "Task.hpp"
#include "Timer/ITimer.hpp"
#include "Encoder.hpp"
#include "PidRegulator.hpp"

class Motor : public Task
{
public:
	struct Config
	{
		struct Out
		{
			ITimer::Timer timer {ITimer::Timer::Tim1};
			ITimer::Chanel chanel {ITimer::Chanel::Ch1};
		};

		Out out1;
		Out out2;
		ITimer::Timer encoder {ITimer::Timer::Tim1};
		PidRegulator::PidParam speedPid;
		PidRegulator::PidParam positionPid;
	};

	enum class ControlMode
	{
		Position,
		Speed
	};
	Motor();
	Motor(const Config &config, uint32_t period = 1, uint32_t priority = 1);
	virtual ~Motor();

	void loop() override;
	void setTargetSpeed(float speed);
	float getTargetSpeed() const;
	float getSpeed() const;
	void setTargetPosition(float position);
	float getTargetPosition() const;
	float getPosition() const ;
	void setControlMode(ControlMode controlMode);
	ControlMode getControlMode() const;
	void setConfig(const Config &config);
	const Config &getConfig() const;
	void setPeriod(uint32_t period);
	void setPriority(uint32_t priority);




private:
	Config m_config;
	Encoder m_encoder;
	float m_targetSpeed {0};
	float m_targetPosition {0};
	ControlMode m_controlMode {ControlMode::Position};
	PidRegulator m_speedPid;
	PidRegulator m_positionPid;

};


