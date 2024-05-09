#include "TaskMenager.hpp"
#include <algorithm>

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
	if(std::find(m_tasks.begin(), m_tasks.end(), &task) == m_tasks.end())
		m_tasks.push_back(&task);
}
void TaskMenager::removeTask(Task &task)
{
    auto it = std::find(m_tasks.begin(), m_tasks.end(), &task);

    if(it != m_tasks.end())
    	m_tasks.erase(it);
}
void TaskMenager::run()
{
	static uint32_t oldMsTime = 0;

	uint32_t msTime = m_sysTick.getTime();

	if (oldMsTime == msTime)
		return;
	oldMsTime = msTime;

	for(auto task : m_tasks)
	{
		if ((msTime % task->getPeriod()) == 0)
		{
			task->loop();
		}
	}
}

