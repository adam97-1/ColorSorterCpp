#pragma once
#include <list>
#include "Task.hpp"
#include "SysTickClass.hpp"

class TaskMenager
{
public:
	TaskMenager();
	virtual ~TaskMenager();
	void addTask(Task &task);
	void removeTask(Task &task);
	void run();
private:
	std::list<Task*> m_tasks;
	SysTickClass m_sysTick;
};
