#include <Config/Config.hpp>
#include "TaskMenager.hpp"
#include "IrDetector.hpp"
#include "ColorDetector.hpp"
#include "Motor.hpp"
#include "cmath"


void SlotColorReady(ColorDetector::Color color)
{

}

void SlotIrDetectorColRisingEdgeState()
{

}

void SlotIrDetectorSelRisingEdgeState()
{

}

void Init()
{
	IrDetector irDetectorSel(IGpio::Gpio {.port  = IGpio::Port::C, .pin = 8}, 100, 1);
	IrDetector irlDetectorCol(IGpio::Gpio {.port =  IGpio::Port::C, .pin = 9}, 100, 1);
	ColorDetector colorDetector(ColorDetector::Config{.s0 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 6},
														.s1 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 5},
														.s2 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 10},
														.s3 = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 11},
														.led = IGpio::Gpio {.port =  IGpio::Port::C, .pin = 12},
														.timInput = ITimer::Timer::Tim3}, 100, 1);
	PidRegulator::Pid speedPid;
	PidRegulator::Pid  psoitionPid;

	speedPid.kp = 300;
	speedPid.ki = 10000;
	speedPid.maxInValue = 15.5;
	speedPid.maxOutValue = 2000;

	psoitionPid.kp = 0;
	psoitionPid.ki = 0;
	psoitionPid.maxInValue = 0;
	psoitionPid.maxOutValue = 0;
	psoitionPid.zeroDetect = false;


	Motor motorDirv(Motor::Config { .out1 = Motor::Config::Out{ .timer = ITimer::Timer::Tim4, .chanel = ITimer::Chanel::Ch3},
									.out2 = Motor::Config::Out{ .timer = ITimer::Timer::Tim4, .chanel = ITimer::Chanel::Ch4},
									.encoder = ITimer::Timer::Tim1,
									.speedPid = speedPid,
									.positionPid = psoitionPid}, 1, 1);
	motorDirv.setControlMode(Motor::ControlMode::Speed);


	speedPid.kp = 300;
	speedPid.ki = 10000;
	speedPid.maxInValue = 15.5;
	speedPid.maxOutValue = 2000;

	psoitionPid.kp = 20;
	psoitionPid.ki = 20;
	psoitionPid.maxInValue = 2*M_PI;
	psoitionPid.maxOutValue = 15.5;
	psoitionPid.zeroDetect = true;


	Motor motorSel(Motor::Config {.out1 = Motor::Config::Out{ .timer = ITimer::Timer::Tim4, .chanel = ITimer::Chanel::Ch1},
									.out2= Motor::Config::Out{ .timer = ITimer::Timer::Tim14, .chanel = ITimer::Chanel::Ch1},
									.encoder = ITimer::Timer::Tim2,
									.speedPid = speedPid,
									.positionPid = psoitionPid}, 1, 1);
	motorSel.setControlMode(Motor::ControlMode::Position);


	TaskMenager::getInstance().addTask(irDetectorSel);
	TaskMenager::getInstance().addTask(irlDetectorCol);
	TaskMenager::getInstance().addTask(colorDetector);
	TaskMenager::getInstance().addTask(motorDirv);
	TaskMenager::getInstance().addTask(motorSel);
	irlDetectorCol.setRisingEdgeState(SlotIrDetectorColRisingEdgeState);
	irlDetectorCol.setRisingEdgeState(SlotIrDetectorSelRisingEdgeState);
	colorDetector.setColorReady(SlotColorReady);
}

int main(void)
{
	Config::Configure();

	while(true)
	{
		TaskMenager::getInstance().run();

	}
}
