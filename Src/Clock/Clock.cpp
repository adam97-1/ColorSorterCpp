#include "Clock/Clock.hpp"

Clock::Clock()
{
	// TODO Auto-generated constructor stub

}

Clock::Clock(IClock *clock) : m_clock{clock}
{
	// TODO Auto-generated constructor stub

}

Clock::~Clock()
{
	// TODO Auto-generated destructor stub
}


void Clock::setClock(IClock *clock)
{
	m_clock = clock;
}
