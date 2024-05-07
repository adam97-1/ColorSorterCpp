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


void IrDetector::setRisingEdgeState(std::function<void()> func)
{
    m_risingEdgeState = func;
}

template<class C, void (C::*Function)(void)>
void IrDetector::setFallingEdgeState(C *instance)
{
	m_risingEdgeState = std::bind(Function, instance);
}

void IrDetector::setFallingEdgeState(std::function<void()> func)
{
	m_fallingEdgeState = func;
}

template<class C, void (C::*Function)(void)>
void IrDetector::setRisingEdgeState(C *instance)
{
	m_fallingEdgeState = std::bind(Function, instance);
}
void IrDetector::loop()
{
	IGpio::State state = Gpio::getInstance().getState(m_inSignal);
	if ((state != m_oldState) && (m_oldState != IGpio::State::Unknow)) {
		if (state == IGpio::State::High)
		{
			m_risingEdgeState();
		}
		else if (state == IGpio::State::Low)
		{
			m_fallingEdgeState();
		}

	}
	m_oldState = state;
}
IGpio::State IrDetector::getState()
{
	return Gpio::getInstance().getState(m_inSignal);
}

