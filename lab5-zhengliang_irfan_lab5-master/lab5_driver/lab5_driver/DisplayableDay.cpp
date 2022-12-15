#include "stdafx.h"
#include "DisplayableDay.h"
#include <iostream>
#include "Event.h"
#include <string>
#include <algorithm>
#include <memory>
#include <vector>
# include <iomanip >

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }

bool DisplayableDay::compare_event_time(std::shared_ptr<DisplayableComponent> e1, std::shared_ptr<DisplayableComponent> e2)
{
	Event* first = dynamic_cast<Event *>(e1.get());
	Event* second = dynamic_cast<Event *>(e2.get());
	if (first->dateInfo.tm_year != second->dateInfo.tm_year)
	{
		return (first->dateInfo.tm_year < second->dateInfo.tm_year);
	}
	if (first->dateInfo.tm_mon != second->dateInfo.tm_mon)
	{
		return (first->dateInfo.tm_mon < second->dateInfo.tm_mon);
	}
	if (first->dateInfo.tm_mday != second->dateInfo.tm_mday)
	{
		return (first->dateInfo.tm_mday < second->dateInfo.tm_mday);
	}

	return (first->dateInfo.tm_hour < second->dateInfo.tm_hour);
}



void DisplayableDay::display(int d)
{
	if (d == 0)
	{
		cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
		cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
		for (size_t i = 0; i < children.size(); ++i)
		{
			if (children[i] != nullptr) {
				children[i]->display(d+1);
			}
		}
	}
	else if (d == 1)
	{
		size_t wd = 0;
		if (dateInfo.tm_mday == 1 && dateInfo.tm_wday != 0)
		{
			for (int spa = 0;spa < dateInfo.tm_wday;spa++)
			{
				cout << std::left<<setw(11)<<" ";
			}
			
		}

		bool hasChild = false;
		for (size_t i = 0; i < children.size(); ++i)
		{
			if (children[i] != nullptr) {
				hasChild = true;
			}
		}
		
		
		string s="";
		for (size_t i = 0; i < children.size(); ++i)
		{
			if (children[i] != nullptr) {
				//children[i]->display(d + 1);
				s = s + "*";
			}
		}
		string str_to_display = std::to_string(dateInfo.tm_mday) + s;
		cout << std::left << setw(11) <<str_to_display;
		if (dateInfo.tm_wday == 6)
		{
			cout << endl;
		}
	}
	else 
	{
		for (size_t i = 0; i < children.size(); ++i)
		{
			if (children[i] != nullptr) {
				children[i]->display(d+1);
			}
		}
	}
	
}

std::shared_ptr<DisplayableComponent> DisplayableDay::removeComponent(unsigned int index)
{
	if (index < children.size()) { // leaf objects will have size of 0
		shared_ptr<DisplayableComponent> removed = children[index];
		children[index] = nullptr;
		children.erase(children.begin() + index);

		
		return removed; // pointer to the removed component if successful
	}
	return nullptr; // nullptr is remove fails
}

shared_ptr<DisplayableComponent> DisplayableDay::addComponent(shared_ptr<DisplayableComponent> comp) {
	Event* d = dynamic_cast<Event *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (d == nullptr) { // the cast failed
		return nullptr;
	}
	else
	{
		children.push_back(comp);
		sort(children.begin(), children.end(), DisplayableDay::compare_event_time);
		return comp;
	}
}

bool DisplayableDay::name_exist(std::string name_to_search)
{
	for (size_t i = 0; i < children.size(); ++i)
	{
		Event* d = dynamic_cast<Event *>(children[i].get());
		
		if (d->my_name == name_to_search)
		{
			return false;
		}
	}
	return true;
}

