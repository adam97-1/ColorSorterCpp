#include "IrDetector.hpp"
#include "Gpio/Gpio.hpp"

IrDetector::IrDetector()
{

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
			for(uint32_t i = 0; i < m_endObserverList; i++)
				m_observers[i]->onRisingEdgeState(this);
		}
		else if (state == IGpio::State::Low)
		{
			for(uint32_t i = 0; i < m_endObserverList; i++)
				m_observers[i]->onFallingEdgeState(this);
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
void IrDetector::addOnserver(IrDetectorOnserver* observer)
{
	m_observers[m_endObserverList] = observer;
	m_endObserverList++;
}

