#pragma once

#include "TaskMenager.hpp"
#include "IrDetector.hpp"
#include "ColorDetector.hpp"
#include "Motor.hpp"

class Run : public ColorDetectorOnserver, IrDetectorOnserver
{
public:
	Run();
	virtual ~Run();

	int exec();

private:
	void setPositionOfColor();
	void onRisingEdgeState(IrDetector* irDetector) override;
	void onFallingEdgeState(IrDetector* irDetector) override;
	void onColorReady(ColorDetector* colorDetector, ColorDetector::Color &color) override;

	IrDetector m_irDetectorSel;
	IrDetector m_irDetectorCol;
	ColorDetector m_colorDetector;
	Motor m_motorDirv;
	Motor m_motorSel;

	uint8_t m_backColorLine = 0;
	uint8_t m_beginColorLine = 0;
	ColorDetector::Color m_colorLine[255];
};

