#pragma once

#include <map>

#include "CalendarComponent.h"
#include "Event.h"

// forward declarations needed to avoid circular includes, used to declare friends only
class FullCalendarBuilder;
class IncrementalCalendarBuilder;
class CalendarInterface;



class Calendar : public CalendarComponent {
	//store events for this calendar
	std::multimap <std::string, std::shared_ptr< Event> >emap;

	//what is builder type
	std::string builder_type;

	// friends
	friend FullCalendarBuilder;
	friend IncrementalCalendarBuilder;
	friend CalendarInterface;
protected:
	std::string name;
	size_t yearsToHold;
	std::tm currentDate; // current date and time
						 // dateInfo is the start date and time

						 // Calendar contains years, so override accordingly
	virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;

	
public:
	// arguments: name of the calendar, length of the calendar in years
	Calendar(std::string n, size_t y);
	// inherited methods
	virtual void display(int d=0) override;

	//add event to the calendar
	void addEvent(std::shared_ptr< Event> e);
	
	std::multimap <std::string, std::shared_ptr< Event> >getEventlist();
	

};