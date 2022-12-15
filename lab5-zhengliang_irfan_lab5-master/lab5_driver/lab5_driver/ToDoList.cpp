#include "stdafx.h"
#include "ToDoList.h"
#include <memory>
#include<iostream>
#include<algorithm>

using namespace std;

ToDoList * ToDoList::instance = 0;

bool ToDoList::compare_event_time(std::shared_ptr<DisplayableComponent> e1, std::shared_ptr<DisplayableComponent> e2)
{
	Task* first = dynamic_cast<Task *>(e1.get());
	Task* second = dynamic_cast<Task *>(e2.get());
	if (first->getDeadline().tm_year != second->getDeadline().tm_year)
	{
		return (first->getDeadline().tm_year < second->getDeadline().tm_year);
	}
	else if(first->getDeadline().tm_mon != second->getDeadline().tm_mon)
	{
		return (first->getDeadline().tm_mon < second->getDeadline().tm_mon);
	}
	else if (first->getDeadline().tm_mday != second->getDeadline().tm_mday)
	{
		return (first->getDeadline().tm_mday < second->getDeadline().tm_mday);
	}
	else if (first->getDeadline().tm_hour != second->getDeadline().tm_hour)
	{
		return (first->getDeadline().tm_hour < second->getDeadline().tm_hour);
	}
	else {
		return (first->getDeadline().tm_min < second->getDeadline().tm_min);
	}
	
}

ToDoList::ToDoList():DisplayableComponent(nullptr)
{
}

ToDoList::~ToDoList()
{
}

ToDoList * ToDoList::getInstance()
{
	if (instance == 0)
	{
		
		instance= new ToDoList;
	}
	return instance;
}

std::shared_ptr<DisplayableComponent> ToDoList::create_and_addTask(string name, tm deadline)
{
	shared_ptr<DisplayableComponent>comp (new Task(name,deadline));
	

	children.push_back(comp);
	sort(children.begin(), children.end(), ToDoList::compare_event_time);
	return comp;
	
}

void ToDoList::display(int d)
{
	cout << "TODO List:" << endl;
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) { // forward request to all children
			cout << i << ".";
			children[i]->display(d + 1);
		}
	}

}
