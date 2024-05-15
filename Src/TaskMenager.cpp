#include "TaskMenager.hpp"
#include "Gpio/Gpio.hpp"

TaskMenager::TaskMenager()
{

}

TaskMenager::~TaskMenager()
{

}

TaskMenager &TaskMenager::getInstance()
{
	static TaskMenager taskMenager;

	return taskMenager;
}
void TaskMenager::addTask(Task &task)
{
	m_tasks[m_endLine] = &task;
	m_endLine++;
}

void TaskMenager::run()
{
	static uint32_t oldMsTime = 0;

	uint32_t msTime = m_sysTick.getTime();

//	if (oldMsTime == msTime)
//		return;
	oldMsTime = msTime;

	for(uint32_t i= 0; i < m_endLine ; i++)
	{
		if ((msTime % m_tasks[i]->getPeriod()) == 0 || true)
		{
			m_tasks[i]->loop();
		}
	}
}

