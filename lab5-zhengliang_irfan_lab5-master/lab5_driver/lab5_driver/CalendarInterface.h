/*
Author: Jon Shidal
Purpose: declare the user interface for our calendar
*/
#pragma once
#include "CalendarBuilder.h"
#include "CalendarComponent.h"
#include <string>
#include <map>
#include "Event.h"
#include <memory>
#include "ToDoList.h"

enum read_calendar_field_index { BUILDERTYPE=0, CAL_NAME=1, START_YEAR=2,
	NUM_YEARS_HOLD = 3, WDAY=4};

enum read_events_field_index {
	EVENT_NAME = 0, EVENT_YEAR = 1, EVENT_MONTH = 2,
	EVENT_DAY = 3, EVENT_HOUR=4, RECURR_EVERY = 5, RECURR_FOR = 6
	
};

class CalendarInterface {
	std::shared_ptr<Calendar> cal; // the calendar
	std::shared_ptr<CalendarBuilder> builder; // builder for managing construction of the calendar
	std::shared_ptr<DisplayableComponent> currentDisplay; // which component the user is currently viewing
	std::shared_ptr<ToDoList>tlist; //the to do list
	std::string my_current_builder_type; // store the name of the current builder type
	std::string my_current_cal_name; // store the name of the current cal's name
	

	void search(std::string, bool &);//search event
	void jump(std::string, std::string);//jump to the specific date
	void edit_event();
	void delete_event(std::shared_ptr<Event >); // delete event
	void todo_add_task();
	void todo_mark_task();
	std::multimap <std::string , std::string> eventname_calname_map;

	
public:
	// constructor
	// arguments: 1 - what type of builder? 2 - how many years to hold? 
	CalendarInterface(std::string builderType, std::string calendarName, size_t years);

	// calendar traversal functions
	void zoomIn(unsigned int index); // zoom in on a child of the current_display
	void zoomOut(); // zoom out to the parent of the current_display
	void run(); // display the current view to the user and prompt for input

	
};