#pragma once

#include "IClock.hpp"

class Clock
{
public:
	Clock();
	Clock(IClock *clock);
	virtual ~Clock();

	void setClock(IClock *clock);

private:
	IClock *m_clock {nullptr};
};

