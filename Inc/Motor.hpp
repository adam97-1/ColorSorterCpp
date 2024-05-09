#pragma once
#include "Task.hpp"
#include "Timer/ITimer.hpp"
#include "Encoder.hpp"

class Motor : public Task
{
public:
	struct Config
	{
		struct Out
		{
			ITimer::Timer timer;
			ITimer::Chanel chanel;
		};
		Out out1;
		Out out2;
		ITimer::Timer endoder;
	};

	enum class ControlMode
	{
		Position,
		Speed
	};

	Motor(Config config, uint32_t period, uint32_t priority);
	virtual ~Motor();

	void loop() override;
	void setTargetSpeed(float speed);
	float getTargetSpeed();
	void setTargetPosition(float speed);
	float getTargetPosition();
	void setControlMode(ControlMode controlMode);
	ControlMode getControlMode();


private:
	Config m_config;
	Encoder *m_endocer {nullptr};
	float m_targetSpeed {0};
	float m_targetPosition {0};
	ControlMode m_controlMode {ControlMode::Position};

};


