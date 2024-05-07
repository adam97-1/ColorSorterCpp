#include "IrDetector.hpp"
#include "Gpio/Gpio.hpp"


IrDetector::IrDetector(IGpio::Gpio inSignal, uint32_t period, uint32_t priority) : m_inSignal{inSignal}
{
	setPeriod(period);
	setPriority(priority);
	m_risingEdgeState = [](){};
	m_fallingEdgeState = [](){};
}

IrDetector::~IrDetector() {
}

template<void (*Function)(void)>
void IrDetector::setRisingEdgeState()
{
    m_risingEdgeState = std::bind(Function);
}

template<class C, void (C::*Function)(void)>
void IrDetector::setFallingEdgeState(C *instance)
{
    m_fallingEdgeState = std::bind(Function, instance);
}

template<void (*Function)(void)>
void IrDetector::setFallingEdgeState()
{
	m_fallingEdgeState = std::bind(Function);
}

template<class C, void (C::*Function)(void)>
void IrDetector::setRisingEdgeState(C *instance)
{
    m_risingEdgeState = std::bind(Function, instance);
}
void IrDetector::loop()
{
	static IGpio::State  oldState = IGpio::State::Unknow;

	IGpio::State state = Gpio::getInstance().getState(m_inSignal);
	if ((state != oldState) && (oldState != IGpio::State::Unknow)) {
		if (state == IGpio::State::High)
		{
			m_risingEdgeState();
		}
		else if (state == IGpio::State::Low)
		{
			m_fallingEdgeState();
		}
		oldState = state;
	}
}
IGpio::State IrDetector::getState()
{
	return Gpio::getInstance().getState(m_inSignal);
}

