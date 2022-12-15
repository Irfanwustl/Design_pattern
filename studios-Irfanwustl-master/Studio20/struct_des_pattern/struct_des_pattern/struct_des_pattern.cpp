// struct_des_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<vector>
#include<string>
#include<iostream>
using namespace std;

class DisplayableComponent {
protected:
	std::vector<DisplayableComponent *>other_disp_comps;
public:
	virtual void display() = 0;
	virtual void addComponent() {
		return;
	}
	virtual DisplayableComponent * getChild(unsigned int index) {
		if (index < other_disp_comps.size()) {
			return other_disp_comps[index];
		}
		else
		{
			return nullptr;
		}
	}

};



class Task :public DisplayableComponent {
	std::string taskName;

public:
	Task(std::string argument) {
		taskName = argument;
	}
	virtual void display()
	{
		cout << taskName << endl;
	}
};


class DCD :public  DisplayableComponent {
protected:
	DisplayableComponent * component;

public:
	DCD(DisplayableComponent * ob) {
		component = ob;
	}
	void addComponent() {
		component->addComponent();
	}

	DisplayableComponent * getChild(unsigned int index) {
		return component->getChild(index);
	}
};

class CompleteDecorator : public  DCD {
public:
	CompleteDecorator(DisplayableComponent * ob) :DCD(ob) {

	}

	void  display() {
		component->display();
		cout << "-COMPLETE" << endl;
	}

};

class PriorityDecorator :public DCD {
public:
	PriorityDecorator(DisplayableComponent * ob) :DCD(ob) {

	}
	void  display() {
		cout << "*" << endl;
		component->display();
		cout << "*" << endl;

	}

};


class ToDoList:public  DisplayableComponent {
protected:
	std::string todolistname;
public:
	ToDoList(std::string argument) {
		todolistname = argument;
	}

	virtual void addComponent() {
		cout << "Enter the name of a Task:";
		string str;
		cin >> str;
		Task *t = new Task(str);
		other_disp_comps.push_back(t);
	}
	virtual void  display() {
		cout << todolistname << endl;
		for (size_t i = 0;i < other_disp_comps.size();i++)
		{
			other_disp_comps[i]->display();
		}
	}

	void prioritizeComponent(unsigned int index) {
		DisplayableComponent * comp = getChild(index);
		if (comp != nullptr) {
			DCD *pd=new PriorityDecorator(comp);
			other_disp_comps[index] = pd;
		}
	}
	void markComplete(unsigned int index) {

		DisplayableComponent * comp = getChild(index);
		if (comp != nullptr) {
			DCD *pd = new CompleteDecorator(comp);
			other_disp_comps[index] = pd;
		}
	}
};



int main()
{
	/*
	ToDoList tl("testtodo");

	tl.addComponent();
	tl.addComponent();
	tl.addComponent();
	tl.display();
	*/

	ToDoList tl("testtodo_decorator");
	tl.addComponent();
	tl.addComponent();
	tl.addComponent();
	tl.display();
	tl.markComplete(0);
	tl.prioritizeComponent(1);
	tl.markComplete(1);
	tl.display();




    return 0;
}

