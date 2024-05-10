#include "Task.hpp"

void Task::setPeriod(uint32_t period)
{
	m_period = period;
}
uint32_t Task::getPeriod() const
{
	return m_period;
}
void Task::setPriority(uint32_t priority)
{
	m_priority = priority;
}
uint32_t Task::getPriority() const
{
	return m_priority;
}
