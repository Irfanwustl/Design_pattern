#pragma once

#include "CalendarComponent.h"

#include <string>
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableDay;
class IncrementalCalendarBuilder;


class Event : public CalendarComponent {
	friend class DisplayableDay;
	friend FullCalendarBuilder;
	friend CalendarInterface;
	friend IncrementalCalendarBuilder;

	
public:
	// 1st argument = start date/timeof the day, 2nd argument = its parent
	Event(std::tm other_tm, std::shared_ptr<DisplayableComponent> to_be_parent, std::string event_name);
	
	virtual void display(int d = 0) override;
	std::string getName();
	
private:

	std::tm my_tm;
	std::shared_ptr<DisplayableComponent> my_parent;
	std::string my_name;
	int my_recurr_every = 0;
	int my_recurr_for = 0;
	bool is_external = false;
	std::string my_cal_name = "";
};

/*
class EventList : public CalendarComponent {
	multimap <std::string, shared_ptr<Event> > emap;  /////shared?????
protected:
	virtual void display() override;
	
public:
	void addEvent(shared_ptr<Event> e);
	bool search(string);

};
*/
