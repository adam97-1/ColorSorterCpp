#include "IrDetector.hpp"
#include "Gpio/Gpio.hpp"

IrDetector::IrDetector()
{
	m_risingEdgeState = [](){};
	m_fallingEdgeState = [](){};
}
IrDetector::IrDetector(const IGpio::Gpio &inSignal, uint32_t period, uint32_t priority) : m_inSignal{inSignal}
{
	IrDetector();
	setPeriod(period);
	setPriority(priority);
}

IrDetector::~IrDetector() {
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
IGpio::State IrDetector::getState() const
{
	return Gpio::getInstance().getState(m_inSignal);
}

void IrDetector::setInSignal(const IGpio::Gpio &inSignal)
{
	m_inSignal = inSignal;
}
const IGpio::Gpio & IrDetector::getInGignal() const
{
	return m_inSignal;
}

