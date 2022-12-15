#include "stdafx.h"
#include "Task.h"
#include <iostream>
#include "CalendarComponent.h"
using namespace std;

Task::Task(std::string name, std::tm deadline):DisplayableComponent(nullptr),name(name),deadline(deadline)
{
	status = "TODO";
}

void Task::display(int d)
{
	cout<<"\t"<<name<<"\t"<< deadline.tm_mon+1 << "/"<< deadline.tm_mday<<"/"<<deadline.tm_year+ CalendarComponent::BASEYEAR << "\t" << deadline.tm_hour<<":"<<deadline.tm_min <<"\t"<<status<< endl;
}

void Task::setStatusComplete()
{
	status = "COMPLETE";
}

std::tm Task::getDeadline()
{
	return deadline;
}
