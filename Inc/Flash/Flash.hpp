#pragma once

#include "../Flash/IFlash.hpp"

class Flash
{
private:
	Flash();
	virtual ~Flash();
public:
	static Flash& getInstance();
	void setFlash(IFlash &flash);
	bool setLatency(IFlash::Latency latency);
	bool setParametr(IFlash::Parametr parametr, bool OnOff);

private:
	IFlash *m_flash {nullptr};
};

