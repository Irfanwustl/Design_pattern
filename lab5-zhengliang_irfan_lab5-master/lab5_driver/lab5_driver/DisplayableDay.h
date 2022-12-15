#pragma once
/*
Author: Jon Shidal
Purpose: declare the DisplayableDay class. This class may be a component of a calendar. It inherits from CalendarComponent and defines pure virtual functions
declared in DisplayableComponent
*/

#include "CalendarComponent.h"
#include <string>
// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class CalendarInterface;
class DisplayableMonth;
class IncrementalCalendarBuilder;


class DisplayableDay : public CalendarComponent {
	friend class DisplayableMonth;
	friend FullCalendarBuilder;
	friend CalendarInterface;
	friend IncrementalCalendarBuilder;
public:
	// 1st argument = start date/timeof the day, 2nd argument = its parent
	DisplayableDay(std::tm, std::shared_ptr<DisplayableComponent>);
	
	virtual void display(int d=0) override;
	virtual std::shared_ptr<DisplayableComponent> removeComponent(unsigned int) override;

protected:
	int num_events_this_day = 0;
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
	bool name_exist(std::string name_to_search);
	static bool compare_event_time(std::shared_ptr<DisplayableComponent> e1, std::shared_ptr<DisplayableComponent> e2);
	
};