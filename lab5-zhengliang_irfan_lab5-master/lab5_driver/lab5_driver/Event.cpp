#include "stdafx.h"
#include "Event.h"
#include <iostream>
#include <string>
# include <iomanip >

using namespace std;

Event::Event(std::tm other_tm, std::shared_ptr<DisplayableComponent> to_be_parent, std::string event_name):CalendarComponent(other_tm, to_be_parent)
{
	my_name = event_name;
	my_parent = to_be_parent;
}



void Event::display(int d)
{
	if (d == 0)
	{
		cout << "event display" << dateInfo.tm_year << endl;
		cout << "\t"<<CalendarComponent::daysoftheweek[ dateInfo.tm_wday] << " " << dateInfo.tm_mon+1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year+CalendarComponent::BASEYEAR << endl;
		if (is_external == false)
		{
			cout << "\t" << dateInfo.tm_hour << ":00" << " " << my_name << endl;
		}
		else
		{
			cout << "\t" << dateInfo.tm_hour << ":00" << " " << my_cal_name << "::" << my_name << endl;
		}
		
	}
	else if (d == 1)
	{
		if (is_external == false)
		{
			cout << "\t\t\t" << dateInfo.tm_hour << ":00" << " " << my_name << endl;
		}
		else
		{
			cout << "\t\t\t" << dateInfo.tm_hour << ":00" << " " << my_cal_name << "::" << my_name << endl;
		}
	}
	
	else if(d==3)
	{
		if (is_external == false)
		{
			cout << "\t\t" << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << " " << my_name << endl;
		}
		else
		{
			cout << "\t\t" << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << " " << my_cal_name << "::" << my_name << endl;
		}
	}
	
}

std::string Event::getName()
{
	return my_name;
}

/*
void EventList::display()
{
	cout << "not implemented\n";
}

void EventList::addEvent(shared_ptr<Event> e)
{
	
	emap.insert(pair <string, shared_ptr<Event>>(e->getName(), e));
}

bool EventList::search(string str_name)
{
	std::pair <multimap <std::string, shared_ptr<Event> >::iterator, std::multimap <std::string, shared_ptr<Event> >::iterator> ret;
	ret = emap.equal_range(str_name);
	for (std::multimap <std::string, shared_ptr<Event> >::iterator it = ret.first; it != ret.second; ++it)
		std::cout << ' ' << it->second;
	std::cout << '\n';
	return false;
}
*/


