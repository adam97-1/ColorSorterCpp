#pragma once
#include <list>
#include "Task.hpp"
#include "SysTickClass.hpp"

class TaskMenager
{

private:
	TaskMenager();
	virtual ~TaskMenager();
public:
	static TaskMenager &getInstance();
	void addTask(Task &task);
	void run();
private:
	Task* m_tasks[512];
	uint16_t m_endLine {0};
	SysTickClass m_sysTick;
};
