#pragma once

#include "Task.hpp"
#include "Gpio/IGpio.hpp"

class  IrDetectorOnserver;
class IrDetector : public Task
{
public:
	IrDetector();
	IrDetector(const IGpio::Gpio &inSignal, uint32_t period = 1, uint32_t priority = 1);
	virtual ~IrDetector();

	void loop() override;

	void addOnserver(IrDetectorOnserver* observer);
	IGpio::State getState() const;
    void setInSignal(const IGpio::Gpio &inSignal);
    const IGpio::Gpio & getInGignal() const;
private:
	IGpio::Gpio m_inSignal;
	IGpio::State  m_oldState {IGpio::State::Unknow};
	IrDetectorOnserver* m_observers[20];
	uint8_t m_endObserverList {0};

};

class IrDetectorOnserver
{
public:
	virtual void onRisingEdgeState(IrDetector* irDetector){};
	virtual void onFallingEdgeState(IrDetector* irDetector){};
};
