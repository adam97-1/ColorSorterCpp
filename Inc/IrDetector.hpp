#pragma once

#include "Task.hpp"
#include "Gpio/IGpio.hpp"
#include <functional>

class IrDetector : public Task
{
public:
	IrDetector();
	IrDetector(const IGpio::Gpio &inSignal, uint32_t period = 1, uint32_t priority = 1);
	virtual ~IrDetector();

	void loop() override;

	IGpio::State getState() const;

	template<typename C>
	void setRisingEdgeState(C &&funcMetod)
	{
		m_risingEdgeState = funcMetod;
	}

	template<typename C>
	void setFallingEdgeState(C &&funcMetod)
	{
		m_fallingEdgeState = funcMetod;
	}


    void setInSignal(const IGpio::Gpio &inSignal);
    const IGpio::Gpio & getInGignal() const;
private:
	IGpio::Gpio m_inSignal;
	IGpio::State  m_oldState {IGpio::State::Unknow};
	std::function<void(void)> m_risingEdgeState;
	std::function<void(void)> m_fallingEdgeState;
};
