#include "Run.hpp"
#include <Config/Config.hpp>
#include <cmath>
#include <functional>

Run::Run()
{
	Config::Configure();

	IGpio::Gpio gpio;
	gpio.port  = IGpio::Port::C;
	gpio.pin = 8;
	m_irDetectorSel.setInSignal(gpio);
	m_irDetectorSel.setPeriod(100);
	m_irDetectorSel.setPriority(1);

	gpio.port  = IGpio::Port::C;
	gpio.pin = 9;
	m_irDetectorCol.setInSignal(gpio);
	m_irDetectorCol.setPeriod(100);
	m_irDetectorCol.setPriority(1);


	ColorDetector::Config colorConfig;

	gpio.port  = IGpio::Port::C;
	gpio.pin = 6;
	colorConfig.s0 =gpio;

	gpio.port  = IGpio::Port::C;
	gpio.pin = 5;
	colorConfig.s1 =gpio;

	gpio.port  = IGpio::Port::C;
	gpio.pin = 10;
	colorConfig.s2 =gpio;

	gpio.port  = IGpio::Port::C;
	gpio.pin = 11;
	colorConfig.s3 =gpio;

	gpio.port  = IGpio::Port::C;
	gpio.pin = 12;
	colorConfig.led =gpio;

	colorConfig.timInput = ITimer::Timer::Tim3;

	m_colorDetector.setConfig(colorConfig);
	m_irDetectorCol.setPeriod(100);
	m_irDetectorCol.setPriority(1);


	Motor::Config motorConfig;

	PidRegulator::PidParam pidParam;

	pidParam.kp = 300;
	pidParam.ki = 10000;
	pidParam.kd = 0;
	pidParam.zeroDetect = false;
	pidParam.maxIntegral = 10000000;
	pidParam.maxInValue = 15.5;
	pidParam.maxOutValue = 2000;
	motorConfig.speedPid = pidParam;

	pidParam.kp = 0;
	pidParam.ki = 0;
	pidParam.kd = 0;
	pidParam.zeroDetect = true;
	pidParam.maxIntegral = 0;
	pidParam.maxInValue = 0;
	pidParam.maxOutValue = 0;
	motorConfig.positionPid = pidParam;

	Motor::Config::Out out;

	out.timer = ITimer::Timer::Tim4;
	out.chanel = ITimer::Chanel::Ch3;
	motorConfig.out1 = out;

	out.timer = ITimer::Timer::Tim4;
	out.chanel = ITimer::Chanel::Ch4;
	motorConfig.out2 = out;

	motorConfig.encoder = ITimer::Timer::Tim1;

	m_motorDirv.setConfig(motorConfig);
	m_motorDirv.setPeriod(100);
	m_motorDirv.setPriority(1);


	pidParam.kp = 300;
	pidParam.ki = 10000;
	pidParam.kd = 0;
	pidParam.zeroDetect = false;
	pidParam.maxIntegral = 10000000;
	pidParam.maxInValue = 15.5;
	pidParam.maxOutValue = 2000;
	motorConfig.speedPid = pidParam;

	pidParam.kp = 20;
	pidParam.ki = 10000;
	pidParam.kd = 0;
	pidParam.zeroDetect = true;
	pidParam.maxIntegral = 10000000;
	pidParam.maxInValue = 2*M_PI;;
	pidParam.maxOutValue = 15.5;
	motorConfig.positionPid = pidParam;


	out.timer = ITimer::Timer::Tim4;
	out.chanel = ITimer::Chanel::Ch1;
	motorConfig.out1 = out;

	out.timer = ITimer::Timer::Tim14;
	out.chanel = ITimer::Chanel::Ch1;
	motorConfig.out2 = out;

	motorConfig.encoder = ITimer::Timer::Tim2;

	m_motorSel.setConfig(motorConfig);
	m_motorSel.setPeriod(100);
	m_motorSel.setPriority(1);

	TaskMenager::getInstance().addTask(m_irDetectorSel);
	TaskMenager::getInstance().addTask(m_irDetectorCol);
	TaskMenager::getInstance().addTask(m_colorDetector);
	TaskMenager::getInstance().addTask(m_motorDirv);
	TaskMenager::getInstance().addTask(m_motorSel);

	m_irDetectorCol.setRisingEdgeState(std::bind(&Run::slotIrDetectorColRisingEdgeState ,this));
	m_irDetectorSel.setRisingEdgeState(std::bind(&Run::slotIrDetectorSelRisingEdgeState ,this));
	m_colorDetector.setColorReady(std::bind(&Run::slotColorReady, this, std::placeholders::_1));

	m_motorDirv.setTargetSpeed(0.5);
}

Run::~Run()
{
	TaskMenager::getInstance().removeTask(m_irDetectorSel);
	TaskMenager::getInstance().removeTask(m_irDetectorCol);
	TaskMenager::getInstance().removeTask(m_colorDetector);
	TaskMenager::getInstance().removeTask(m_motorDirv);
	TaskMenager::getInstance().removeTask(m_motorSel);
}

int Run::exec()
{
	while(true)
		TaskMenager::getInstance().run();
	return 0;
}

void Run::slotIrDetectorColRisingEdgeState()
{
	m_colorDetector.measurementColor();
}
void Run::slotIrDetectorSelRisingEdgeState()
{
	m_beginColorLine++;
	setPositionOfColor();
}
void Run::slotColorReady(const ColorDetector::Color &color)
{
	m_colorLine[m_backColorLine] = color;
	m_backColorLine++;
}

void Run::setPositionOfColor()
{
	ColorDetector::Color color = m_colorLine[m_beginColorLine];
	if(color.blue < color.green && color.blue < color.red)
		m_motorSel.setTargetPosition(1);
	else if(color.blue > color.green && color.blue > color.red)
		m_motorSel.setTargetPosition(2);
	else if(color.green > color.blue && color.green > color.red)
		m_motorSel.setTargetPosition(3);
	else if(color.red > color.blue && color.red > color.green)
		m_motorSel.setTargetPosition(4);

}

