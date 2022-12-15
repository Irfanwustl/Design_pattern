#pragma once
#include "Task.h"

//the todo list 
class ToDoList :public DisplayableComponent {
	static ToDoList* instance;
	ToDoList();
	
	static bool compare_event_time(std::shared_ptr<DisplayableComponent> e1, std::shared_ptr<DisplayableComponent> e2);
public:
	//implementation of singleton pattern
	static ToDoList* getInstance();
	std::shared_ptr<DisplayableComponent> create_and_addTask(std::string name, std::tm deadline) ;
	virtual void display(int d = 0) override;
	~ToDoList();
};
