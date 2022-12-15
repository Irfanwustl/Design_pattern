#pragma once

#include "DisplayableComponent.h"
#include <string>

//for todolist 
class Task :public DisplayableComponent {
	std::string name,status;
	std::tm deadline;

public:
	Task(std::string name, std::tm deadline);
	virtual void display(int d = 0) override;
	void setStatusComplete();
	std::tm getDeadline();

};