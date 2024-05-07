#pragma once

#include "Task.hpp"
#include "Gpio/IGpio.hpp"
#include <functional>

class IrDetector : public Task
{
public:
	IrDetector(IGpio::Gpio inSignal, uint32_t period, uint32_t priority);
	virtual ~IrDetector();

	void loop() override;

	IGpio::State getState();
    template<void (*Function)(void)>
    void setRisingEdgeState();

    template<class C, void (C::*Function)(void)>
    void setRisingEdgeState(C *instance);

    template<void (*Function)(void)>
    void setFallingEdgeState();

    template<class C, void (C::*Function)(void)>
    void setFallingEdgeState(C *instance);
private:
	IGpio::Gpio m_inSignal;
	std::function<void(void)> m_risingEdgeState;
	std::function<void(void)> m_fallingEdgeState;
};
