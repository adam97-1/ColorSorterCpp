#include "Run.hpp"
#include <Config/Config.hpp>
#include <cmath>
#include <functional>

Run::Run()
{
	IGpio::Gpio gpio;
	gpio.port  = IGpio::Port::C;
	gpio.pin = 8;
	m_irDetectorSel.setInSignal(gpio);
	m_irDetectorSel.setPeriod(10);
	m_irDetectorSel.setPriority(1);

	gpio.port  = IGpio::Port::C;
	gpio.pin = 9;
	m_irDetectorCol.setInSignal(gpio);
	m_irDetectorCol.setPeriod(10);
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
	m_colorDetector.setPeriod(100);
	m_colorDetector.setPriority(1);


	Motor::Config motorConfig;

	PidRegulator::PidParam pidParam;

	pidParam.kp = 300;
	pidParam.ki = 1000;
	pidParam.kd = 0;
	pidParam.zeroDetect = false;
	pidParam.maxIntegral = 10000000;
	pidParam.maxInValue = 14.5;
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
	m_motorDirv.setPeriod(1);
	m_motorDirv.setPriority(1);
	m_motorDirv.setControlMode(Motor::ControlMode::Speed);


	pidParam.kp = 300;
	pidParam.ki = 1000;
	pidParam.kd = 0;
	pidParam.zeroDetect = false;
	pidParam.maxIntegral = 10000000;
	pidParam.maxInValue = 14.5;
	pidParam.maxOutValue = 2000;
	motorConfig.speedPid = pidParam;

	pidParam.kp = 20;
	pidParam.ki = 20;
	pidParam.kd = 0;
	pidParam.zeroDetect = true;
	pidParam.maxIntegral = 10000000;
	pidParam.maxInValue = 2*M_PI;;
	pidParam.maxOutValue = 14.5;
	motorConfig.positionPid = pidParam;


	out.timer = ITimer::Timer::Tim4;
	out.chanel = ITimer::Chanel::Ch1;
	motorConfig.out1 = out;

	out.timer = ITimer::Timer::Tim14;
	out.chanel = ITimer::Chanel::Ch1;
	motorConfig.out2 = out;

	motorConfig.encoder = ITimer::Timer::Tim2;

	m_motorSel.setConfig(motorConfig);
	m_motorSel.setPeriod(1);
	m_motorSel.setPriority(1);
	m_motorSel.setControlMode(Motor::ControlMode::Position);

	TaskMenager::getInstance().addTask(m_irDetectorSel);
	TaskMenager::getInstance().addTask(m_irDetectorCol);
	TaskMenager::getInstance().addTask(m_colorDetector);
	TaskMenager::getInstance().addTask(m_motorDirv);
	TaskMenager::getInstance().addTask(m_motorSel);

	m_irDetectorCol.addOnserver(this);
	m_irDetectorSel.addOnserver(this);
	m_colorDetector.addOnserver(this);

	m_motorDirv.setTargetSpeed(0.5);
	m_motorSel.setTargetPosition(0);
}

Run::~Run()
{

}

int Run::exec()
{
	while(true)
		TaskMenager::getInstance().run();
	return 0;
}

void Run::onRisingEdgeState(IrDetector* irDetector)
{
	if(&m_irDetectorCol  == irDetector)
	{
		m_colorDetector.measurementColor();
	}
	if(&m_irDetectorSel  == irDetector)
	{
		setPositionOfColor();
		m_beginColorLine++;
	}
}
void Run::onFallingEdgeState(IrDetector* irDetector)
{

}

void Run::onColorReady(ColorDetector* colorDetector, ColorDetector::Color &color)
{
	if(&m_colorDetector == colorDetector)
	{
		m_colorLine[m_backColorLine] = color;
		m_backColorLine++;
	}
}

void Run::setPositionOfColor()
{
	ColorDetector::Color color = m_colorLine[m_beginColorLine];
	if(color.blue < color.green && color.blue < color.red)
		m_motorSel.setTargetPosition(1.05);
	else if(color.blue > color.green && color.blue > color.red)
		m_motorSel.setTargetPosition(1.05*2);
	else if(color.green > color.blue && color.green > color.red)
		m_motorSel.setTargetPosition(1.05*3);
	else if(color.red > color.blue && color.red > color.green)
		m_motorSel.setTargetPosition(1.05*4);

}

