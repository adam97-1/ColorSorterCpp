#include "Flash/Flash.hpp"

Flash::Flash()
{

}

Flash::~Flash()
{

}

Flash& Flash::getInstance()
{
	static Flash flash;

	return flash;
}

void Flash::setFlash(IFlash &flash)
{
	m_flash = &flash;
}

bool Flash::setLatency(IFlash::Latency latency)
{
	if(!m_flash)
		return false;
	return m_flash->setLatency(latency);
}
bool Flash::setParametr(IFlash::Parametr parametr, bool OnOff)
{
	if(!m_flash)
		return false;
	return m_flash->setParametr(parametr, OnOff);
}
