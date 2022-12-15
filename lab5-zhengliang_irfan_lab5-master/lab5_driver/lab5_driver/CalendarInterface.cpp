#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "IncrementalCalendarBuilder.h"
#include <iostream>
#include <ctime>
#include "DisplayableDay.h"
#include "DisplayableMonth.h"
#include "DisplayableYear.h"
#include <memory>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>

using namespace std;

/*
Constructor for the CalendarInterface
*/
CalendarInterface::CalendarInterface(std::string builderType, std::string calendarName, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) {
	// initialize different builders based on user input
	if (builderType == "full") {
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		cal->builder_type = builderType;
		my_current_builder_type = builderType;
		my_current_cal_name = calendarName;
		currentDisplay = cal;
	}
	if (builderType == "inc")
	{
		builder = make_shared<IncrementalCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		cal->builder_type = builderType;
		my_current_builder_type = builderType;
		my_current_cal_name = calendarName;
		currentDisplay = cal;
	}
	// Initialize To-Do List
	shared_ptr<ToDoList> t (ToDoList::getInstance());
	tlist =t;
}

/*
Function that handles user inputs and interactions
*/
void CalendarInterface::run() {

	// run until the user quits
	// flags to record which view is displaying. The names should be self-evident
	bool isEventDisplay = false;
	bool isCaldisplay = true;
	bool isTodoDisplay = false;
	// counter to enumerate the saved calendars as part of the file name so that every time a calendar is saved it gets a different name
	int saved_calendars_enumerate = 0;
	// record the previous display
	shared_ptr<DisplayableComponent>prev_diplay = currentDisplay;
	while (1) {
		// store a big string as the menu
		string from_start_input;
		// check if it is at the event level
		Event* maybe_event = dynamic_cast<Event *>(currentDisplay.get());
		if (maybe_event != nullptr)
		{
			isEventDisplay = true;
		}
		else
		{
			isEventDisplay = false;
		}
		// display the current display of the calendar based on builder type
		if (my_current_builder_type == "full")
		{
			currentDisplay->display(0);
		}
		// if is IncrementalCalendarBuilder
		else
		{
				// The current display can be of any of the following types. Check what the type is and display accordingly
			    // For example, maybe_calendar != nullptr indicates that the current display is at the calendar level
				Calendar* maybe_calendar = dynamic_cast<Calendar *>(currentDisplay.get());
				DisplayableYear* maybe_year = dynamic_cast<DisplayableYear *>(currentDisplay.get());
				DisplayableMonth* maybe_month = dynamic_cast<DisplayableMonth *>(currentDisplay.get());
				DisplayableDay* maybe_day = dynamic_cast<DisplayableDay *>(currentDisplay.get());
				Event* maybe_event = dynamic_cast<Event *>(currentDisplay.get());
				
				if (maybe_calendar != nullptr)
				{
					// print out the required display at the calendar level
					cout << "Calendar: " << maybe_calendar->name << endl;
					auto yd = maybe_calendar->dateInfo.tm_year;
					for (size_t i = 0; i < maybe_calendar->children.size(); ++i)
					{
						cout << i << " ";
						cout << "\tYear " << maybe_calendar->dateInfo.tm_year + i + CalendarComponent::BASEYEAR << endl;
					}
				}
				else if (maybe_year != nullptr)
				{
					// retrieve the event map
					std::multimap <std::string, std::shared_ptr<Event>> current_cal_eventmap = cal->getEventlist();
					// store current iteration's key, that is, the event name
					string temp_event_name;
					// store the current iteration's pointer to the event being processed
					shared_ptr<Event> temp_event_ptr;
					// store the pointers to events that are relevant to this year
					std::vector<std::shared_ptr<DisplayableComponent> > temp_children;
					// go through each event in the map, populate temp_children
					for (std::multimap <std::string, std::shared_ptr<Event>>::iterator iter = current_cal_eventmap.begin(); iter != current_cal_eventmap.end(); ++iter)
					{
						temp_event_name = iter->first;
						temp_event_ptr = iter->second;
						if (maybe_year->dateInfo.tm_year == temp_event_ptr->dateInfo.tm_year)
						{
							temp_children.push_back(temp_event_ptr);
							sort(temp_children.begin(), temp_children.end(), DisplayableDay::compare_event_time);
						}
					}
					// print according to the requirements at the year level
					cout << "Year " << maybe_year->dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
					auto md = maybe_year->dateInfo.tm_mon;
					for (size_t i = 0; i < maybe_year->children.size(); ++i) {
						// print each month
						cout << "\t" << i << " " << CalendarComponent::months[md + i] << endl;
						for (size_t j = 0; j < temp_children.size(); ++j)
						{
							Event* curr_event = dynamic_cast<Event *>(temp_children[j].get());
							// print each event under its month
							if (curr_event->dateInfo.tm_mon == i)
							{
								cout << "\t\t" << " " << curr_event->dateInfo.tm_mon + 1 << "/" << curr_event->dateInfo.tm_mday << "/" << curr_event->dateInfo.tm_year + CalendarComponent::BASEYEAR;
								// check if this event is merged from outside calendar and print accordingly
								if (curr_event->is_external == false)
								{
									cout << " " << curr_event->dateInfo.tm_hour << ":00" << " " << curr_event->my_name << endl;
								}
								else
								{
									string external_cal_name;
									auto it = eventname_calname_map.find(curr_event->my_name);
									if (it != eventname_calname_map.end())
									{
										external_cal_name = it->second;
									}
									cout << " " << curr_event->dateInfo.tm_hour << ":00" << " " << external_cal_name << "::" << curr_event->my_name << endl;
								}
							}
						}
					}
				}
				else if (maybe_month != nullptr)
				{
					// print the weekday labels
					for (size_t wd = 0; wd < CalendarComponent::DAYSINAWEEK; wd++)
					{
						cout << std::left << setw(11) << CalendarComponent::daysoftheweek[wd];
					}
					// print each day as a number
					cout << endl;
					for (size_t i = 0; i < maybe_month->children.size(); ++i)
					{
						size_t wd = 0;
						if (maybe_month->children_tm_vector[i].tm_mday == 1 && maybe_month->children_tm_vector[i].tm_wday != 0)
						{
							for (int spa = 0; spa < maybe_month->children_tm_vector[i].tm_wday; spa++)
							{
								cout << std::left << setw(11) << " ";
							}

						}
						std::multimap <std::string, std::shared_ptr<Event>> current_cal_eventmap = cal->getEventlist();
						// store current iteration's key, that is, the event name
						string temp_event_name;
						// store the current iteration's event ptr being processed
						shared_ptr<Event> temp_event_ptr;
						// store relevant event children for each day
						std::vector<std::shared_ptr<DisplayableComponent> > temp_children; 
						// go through each event in the map, populate temp_children
						for (std::multimap <std::string, std::shared_ptr<Event>>::iterator iter = current_cal_eventmap.begin(); iter != current_cal_eventmap.end(); ++iter)
						{
							temp_event_name = iter->first;
							temp_event_ptr = iter->second;
							if (maybe_month->children_tm_vector[i].tm_year == temp_event_ptr->dateInfo.tm_year
								&& maybe_month->children_tm_vector[i].tm_mon == temp_event_ptr->dateInfo.tm_mon
								&& maybe_month->children_tm_vector[i].tm_mday == temp_event_ptr->dateInfo.tm_mday)
							{
								temp_children.push_back(temp_event_ptr);
								sort(temp_children.begin(), temp_children.end(), DisplayableDay::compare_event_time);
							}
						}
						// determine if this day has children or not
						bool hasChild = false;
						for (size_t i = 0; i < temp_children.size(); ++i)
						{
							if (temp_children[i] != nullptr) {
								hasChild = true;
							}
						}
						// print the appropriate number of * after each day based on event number
						string s = "";
						for (size_t i = 0; i < temp_children.size(); ++i)
						{
							if (temp_children[i] != nullptr) {
								s = s + "*";
							}
						}
						string str_to_display = std::to_string(maybe_month->children_tm_vector[i].tm_mday) + s;
						cout << std::left << setw(11) << str_to_display;
						if (maybe_month->children_tm_vector[i].tm_wday == 6)
						{
							cout << endl;
						}

					}
					cout << endl;
				}
				else if (maybe_day != nullptr)
				{
					// print the date of this day
					cout << "\t\t\t" << CalendarComponent::daysoftheweek[maybe_day->dateInfo.tm_wday] << " ";
					cout << maybe_day->dateInfo.tm_mon + 1 << "/" << maybe_day->dateInfo.tm_mday << "/" << maybe_day->dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
					
					std::multimap <std::string, std::shared_ptr<Event>> current_cal_eventmap = cal->getEventlist();
					// store current iteration's key, that is, the event name
					string temp_event_name;
					// store the current itr's ptr to event being processed
					shared_ptr<Event> temp_event_ptr;
					// find this day's events and store them in this vector
					std::vector<std::shared_ptr<DisplayableComponent> > temp_children;
					// go through each event in the map, populate temp_children
					for (std::multimap <std::string, std::shared_ptr<Event>>::iterator iter = current_cal_eventmap.begin(); iter != current_cal_eventmap.end(); ++iter)
					{
						temp_event_name = iter->first;
						temp_event_ptr = iter->second;
						if (maybe_day->dateInfo.tm_year == temp_event_ptr->dateInfo.tm_year
							&& maybe_day->dateInfo.tm_mon == temp_event_ptr->dateInfo.tm_mon
							&& maybe_day->dateInfo.tm_mday == temp_event_ptr->dateInfo.tm_mday)
						{
							temp_children.push_back(temp_event_ptr);
							sort(temp_children.begin(), temp_children.end(), DisplayableDay::compare_event_time);
						}
					}
					// print each event
					for (size_t i = 0; i < temp_children.size(); ++i)
					{
						Event* curr_event = dynamic_cast<Event *>(temp_children[i].get());
						// check if this event is merged from outside and print accordingly
						if (curr_event->is_external == false)
						{
							cout << "\t\t\t" << curr_event->dateInfo.tm_hour << ":00" << " " << curr_event->my_name << endl;
						}
						else
						{
							string external_cal_name;
							auto it = eventname_calname_map.find(curr_event->my_name);
							if (it != eventname_calname_map.end())
							{
								external_cal_name = it->second;
							}
							cout << "\t\t\t" << curr_event->dateInfo.tm_hour << ":00" << " " << external_cal_name << "::"<< curr_event->my_name << endl;

						}
						
					}
				}
				else if (maybe_event != nullptr)
				{
					std::multimap <std::string, std::shared_ptr<Event>> current_cal_eventmap = cal->getEventlist();
					// store current iteration's key, that is, the event name
					string temp_event_name;
					// store the current iteration's ptr to the current event being processed
					shared_ptr<Event> temp_event_ptr;
					// just a temporary holder. It is a vector but we expect it to hold only on  ptr that is to the currentdisplay
					std::vector<std::shared_ptr<DisplayableComponent> > temp_children;
					// go through each event in the map, find the event that matches the current display
					for (std::multimap <std::string, std::shared_ptr<Event>>::iterator iter = current_cal_eventmap.begin(); iter != current_cal_eventmap.end(); ++iter)
					{
						temp_event_name = iter->first;
						temp_event_ptr = iter->second;
						if (maybe_event->dateInfo.tm_year == temp_event_ptr->dateInfo.tm_year
							&& maybe_event->dateInfo.tm_mon == temp_event_ptr->dateInfo.tm_mon
							&& maybe_event->dateInfo.tm_mday == temp_event_ptr->dateInfo.tm_mday)
						{
							temp_children.push_back(temp_event_ptr);
							sort(temp_children.begin(), temp_children.end(), DisplayableDay::compare_event_time);
						}
					}
					// display this current event (temp_children should just have 1 element)
					for (size_t i = 0; i < temp_children.size(); ++i)
					{
						Event* curr_event = dynamic_cast<Event *>(temp_children[i].get());
						if (curr_event->dateInfo.tm_hour == maybe_event->dateInfo.tm_hour)
						{
							cout << "\t" << CalendarComponent::daysoftheweek[maybe_event->dateInfo.tm_wday] << " " << maybe_event->dateInfo.tm_mon + 1 << "/"
								<< maybe_event->dateInfo.tm_mday << "/" << maybe_event->dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
							// display differently if the event is merged from outside
							if (curr_event->is_external == false)
							{
								cout << "\t" << maybe_event->dateInfo.tm_hour << ":00" << " " << curr_event->my_name << endl;
							}
							else
							{
								string external_cal_name;
								auto it = eventname_calname_map.find(curr_event->my_name);
								if (it != eventname_calname_map.end())
								{
									external_cal_name = it->second;
								}
								cout << "\t" << maybe_event->dateInfo.tm_hour << ":00" << " " << external_cal_name << "::" << curr_event->my_name << endl;
							}
						}
					}
				}
		}
		// display options to the user and respond to user input accordingly
		vector<string> valid_options;
		if (isCaldisplay) {
			// record if To-Do list is displaying
			isTodoDisplay = false;
			// populate the vector that holds all the valid options 
			valid_options.push_back("in");
			valid_options.push_back("out");
			valid_options.push_back("q");
			valid_options.push_back("add");
			valid_options.push_back("search");
			valid_options.push_back("jump");
			valid_options.push_back("save");
			valid_options.push_back("restore");
			valid_options.push_back("todo");
			valid_options.push_back("merge");
			// display local options if appropriate when an event is the current display
			if (isEventDisplay)
			{
				valid_options.push_back("edit");
				valid_options.push_back("delete");
			}
			// generate the menu string
			from_start_input = "zoom out: out, zoom in: in, quit: q, add event: add, search event: search, jump to date: jump, save calendar: save, restore calendar: restore, Switch to Todo List view: todo, merge calendar: merge";
			if (isEventDisplay)
			{
				from_start_input = from_start_input + ", Edit Event: edit, Delete Event: delete";
			}
		}
		// add options if a To-Do List is displaying
		else if (isTodoDisplay)
		{
			valid_options.push_back("add_task");
			valid_options.push_back("mark_task");
			valid_options.push_back("cview");
			from_start_input = "Add task: add_task, mark task: mark_task, Switch to Calender view : cview";
			isCaldisplay = false;
		}
		else{
			cout << "something wrong" << endl;
			break;
		}
		// show users the menu and take inputs as options
		cout << from_start_input << endl;
		string in;
		cin >> in;

		// check if the input is among the valid options or not
		while (true)
		{
			if (cin.fail() || 
			find(valid_options.begin(), valid_options.end(), in) == valid_options.end())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << from_start_input << endl;
				cin >> in;
			}
			else {
				break;
			}
		}
		// if the user wants to zoom in
		if (in == "in") {
			// check if it has children to be zoomed in
			if (currentDisplay->children.size() > 0) {
				cout << "index? (0-" << currentDisplay->children.size() - 1 << ")" << endl;
				int index = 0;
				cin >> index;
				// behave differently according to builder type
				if (my_current_builder_type == "full")
				{
					// check if an event is the current display
					Event* maybe_event = dynamic_cast<Event *>(currentDisplay.get());
					if (maybe_event != nullptr)
					{
						isEventDisplay = true;
					}
					else
					{
						isEventDisplay = false;
					}
					zoomIn(index);
				}
				// build objects and add them along the way if it is incremental
				if (my_current_builder_type == "inc")
				{
					// check if the desired child to be zoomed in is constructed or not, if not construct it and then zoom in
					if (currentDisplay->getChild(index) == nullptr)
					{
						// check what the current display is. E.g., maybe_event != nullptr means that current display is an event.
						Calendar* maybe_calendar = dynamic_cast<Calendar *>(currentDisplay.get());
						DisplayableYear* maybe_year = dynamic_cast<DisplayableYear *>(currentDisplay.get());
						DisplayableMonth* maybe_month = dynamic_cast<DisplayableMonth *>(currentDisplay.get());
						DisplayableDay* maybe_day = dynamic_cast<DisplayableDay *>(currentDisplay.get());
						Event* maybe_event = dynamic_cast<Event *>(currentDisplay.get());
						
						// check if the current display is an event so as to add options
						if (maybe_event != nullptr)
						{
							isEventDisplay = true;
						}
						else
						{
							isEventDisplay = false;
						}
						// build objects of the currentdisplay's next level according to what the current display level is
						if (maybe_calendar != nullptr)
						{
							currentDisplay->addComponent(builder->buildYear(maybe_calendar->children_tm_vector[index], currentDisplay));
							zoomIn(index);
						}
						else if (maybe_year != nullptr)
						{
							currentDisplay->addComponent(builder->buildMonth(maybe_year->children_tm_vector[index], currentDisplay));
							zoomIn(index);
						}
						else if (maybe_month != nullptr)
						{
							currentDisplay->addComponent(builder->buildDay(maybe_month->children_tm_vector[index], currentDisplay));
							zoomIn(index);
						}
						else if (maybe_day != nullptr)
						{
							// consult the event map
							std::multimap <std::string, std::shared_ptr<Event>> current_cal_eventmap = cal->getEventlist();
							// store current iteration's key, that is, the event name
							string temp_event_name;
							// holder for each iteration's event ptr
							shared_ptr<Event> temp_event_ptr;
							// store the events of this day, temporarily, only to find which child to be constructed and added to the calendar
							std::vector<std::shared_ptr<DisplayableComponent> > temp_children;
							// go through each event in the map
							for (std::multimap <std::string, std::shared_ptr<Event>>::iterator iter = current_cal_eventmap.begin(); iter != current_cal_eventmap.end(); ++iter)
							{
								temp_event_name = iter->first;
								temp_event_ptr = iter->second;
								if (maybe_day->dateInfo.tm_year == temp_event_ptr->dateInfo.tm_year
									&& maybe_day->dateInfo.tm_mon == temp_event_ptr->dateInfo.tm_mon
									&& maybe_day->dateInfo.tm_mday == temp_event_ptr->dateInfo.tm_mday)
								{
									temp_children.push_back(temp_event_ptr);
									sort(temp_children.begin(), temp_children.end(), DisplayableDay::compare_event_time);
								}
							}
							// find the event to be added to the calendar based on index, build it and zoom in
							Event* to_add_event = dynamic_cast<Event *>(temp_children[index].get());
							maybe_day->addComponent(builder->buildEvent(currentDisplay, to_add_event->my_name,to_add_event->dateInfo,
								to_add_event->my_recurr_every, to_add_event->my_recurr_for));
							zoomIn(index);
						}
						else if (maybe_event != nullptr)
						{
							zoomIn(index);
						}
					}
					else
					{
						zoomIn(index);
					}

				}
				
			}
			else {
				cout << "Nothing to zoom in on" << endl;
			}
		}
		// zooming out one level
		else if (in == "out") {
			zoomOut();
		}
		else if (in == "q") {
			break;
		}
		else if (in == "add")
		{
			// variables to hold user inputs
			string input_event_name;
			unsigned int input_year = 0;
			unsigned int input_month = 0;
			int input_day = 0;
			int input_hour = 0;
			std::tm input_tm = { 0 };
			int input_recurr_every = 0;
			int input_recurr_for = 0;

			// all the following code is for one purpose: get the inputs, respectively and check 
			// for valid inputs
			cout << "enter a new event's name: " << endl;
			cin >> input_event_name;

			cout << "enter a new event's year, e.g.," << cal->dateInfo.tm_year + cal->BASEYEAR << " to " 
				<< cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold - 1 << endl;
			cin >> input_year;

			while (true)
			{
				if (cin.fail() || input_year > cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold - 1 
					|| input_year < cal->dateInfo.tm_year + cal->BASEYEAR)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "enter a new event's year, e.g.," << cal->dateInfo.tm_year + cal->BASEYEAR << " to "
						<< cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold - 1 << endl;
					cin >> input_year;
				}
				else
				{
					break;
				}
			}


			cout << "enter a new event's month, e.g., 1-12: " << endl;
			cin >> input_month;

			while (true)
			{
				if (cin.fail() || input_month > 12 || input_month <1)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "enter a new event's month, e.g., 1-12: " << endl;
					cin >> input_month;
				}
				else
				{
					input_month -= 1;
					break;
				}
			}


			cout << "enter a new event's day, e.g., 1-31: " << endl;
			cin >> input_day;

			while (true)
			{
				if (cin.fail() || input_day > 31 || input_day <1
					|| input_day > CalendarComponent::days[input_month])
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "enter a new event's day, e.g., 1-31 according to month: " << endl;
					cin >> input_day;
				}
				else{
					break;
				}
			}




			cout << "enter a new event's hour, e.g., 0-24: " << endl;
			cin >> input_hour;


			while (true)
			{
				if (cin.fail() || input_hour > 24 || input_hour <0)
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "enter a new event's hour, e.g., 0-24: " << endl;
					cin >> input_hour;
				}
				else {
					break;
				}
			}



			cout << "enter a new event's recurring every as an integer: " << endl;
			cin >> input_recurr_every;


			while (true)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "enter a new event's recurring every as an integer: " << endl;
					cin >> input_recurr_every;
				}
				else {
					break;
				}
			}

			cout << "enter a new event's recurring for as an integer: " << endl;
			cin >> input_recurr_for;

			while (true)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "enter a new event's recurring for as an integer: " << endl;
					cin >> input_recurr_for;
				}
				else {
					break;
				}
			}



			// record all the inputs by user into the holding tm struct
			input_tm.tm_year = input_year - cal->BASEYEAR;
			input_tm.tm_mon = input_month;
			input_tm.tm_mday = input_day;
			input_tm.tm_hour = input_hour;	
			int input_year_index = input_year - cal->BASEYEAR - cal->dateInfo.tm_year;
			int input_month_index = input_month;
			int input_day_index = input_day - 1;


			// tm to be used to assign to events during the following loop algorithm for each iteration
			tm temp_tm = { 0 };
			temp_tm.tm_year = input_year - cal->BASEYEAR;
			temp_tm.tm_mon = input_month;
			temp_tm.tm_mday = input_day;
			temp_tm.tm_hour = input_hour;

			
			// temporary variables used for tracing the indices at each level for the following loop algorithm
			int curr_day = input_day;
			unsigned int curr_month = input_month;
			unsigned int curr_year = input_year;
			int curr_day_index = input_day_index;
			int curr_month_index = input_month_index;
			int curr_year_index = input_year_index;
			int curr_month_length = CalendarComponent::days[curr_month_index];

			// temporary variables on the path to the event that is to be added
			shared_ptr<DisplayableYear> the_year_to_add;
			shared_ptr<DisplayableMonth> the_month_to_add;
			shared_ptr<DisplayableDay> the_day_to_add;
			shared_ptr<Event> new_event;
			// algorithm to calculate the recurring events' dates. Build each one during each iteration
			for (int i = 0; i < input_recurr_for+1; ++i)
			{
				int addon_days = i*input_recurr_every;
				curr_day = curr_day + addon_days;
				curr_day_index = curr_day - 1;
				// keep adding months
				while (curr_day > curr_month_length)
			   {
					curr_day = curr_day - curr_month_length;
					curr_day_index = curr_day - 1;
					curr_month = curr_month + 1;
					// a new year
					if (curr_month > CalendarComponent::MONTHS - 1)
					{
						curr_month = curr_month - (CalendarComponent::MONTHS - 1) - 1;
						curr_month_index = curr_month;
						curr_month_length = CalendarComponent::days[curr_month_index];
						curr_year = curr_year + 1;
						curr_year_index = curr_year - cal->BASEYEAR - cal->dateInfo.tm_year;
					}
					else
					{
						curr_month_index = curr_month;
						curr_month_length = CalendarComponent::days[curr_month_index];
					}
				}
				// check if within calendar; e.g., years more than upper limit are excluded
				if (curr_year <= cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold - 1)
				{
					// go through the path to the date that the vent should be added. During the process
					// if one component is missing, for the IncrementalCalendarBuilder, the missing component is constructed.
					shared_ptr<DisplayableYear> the_year_to_add = dynamic_pointer_cast<DisplayableYear>(cal->getChild(curr_year - cal->BASEYEAR - cal->dateInfo.tm_year));
					if (my_current_builder_type == "inc" && the_year_to_add == nullptr)
					{
						cal->addComponent(builder->buildYear(cal->children_tm_vector[curr_year - cal->BASEYEAR - cal->dateInfo.tm_year], cal));
						the_year_to_add = dynamic_pointer_cast<DisplayableYear>(cal->getChild(curr_year - cal->BASEYEAR - cal->dateInfo.tm_year));
					}
					shared_ptr<DisplayableMonth> the_month_to_add = dynamic_pointer_cast<DisplayableMonth>(the_year_to_add->getChild(curr_month));
					if (my_current_builder_type == "inc" && the_month_to_add == nullptr)
					{
						the_year_to_add->addComponent(builder->buildMonth(the_year_to_add->children_tm_vector[curr_month], the_year_to_add));
						the_month_to_add = dynamic_pointer_cast<DisplayableMonth>(the_year_to_add->getChild(curr_month));
					}
					shared_ptr<DisplayableDay> the_day_to_add = dynamic_pointer_cast<DisplayableDay>(the_month_to_add->getChild(curr_day - 1));
					if (my_current_builder_type == "inc" && the_day_to_add == nullptr)
					{
						the_month_to_add->addComponent(builder->buildDay(the_month_to_add->children_tm_vector[curr_day - 1], the_month_to_add));
						the_day_to_add = dynamic_pointer_cast<DisplayableDay>(the_month_to_add->getChild(curr_day - 1));
					}

					// set the tm's fields correctly for each event
					temp_tm = { 0 };
					temp_tm.tm_year = curr_year - cal->BASEYEAR;
					temp_tm.tm_mon = curr_month;
					temp_tm.tm_mday = curr_day;
					temp_tm.tm_hour = input_hour;

					//deep copy of the dateinfo
					temp_tm.tm_isdst = the_day_to_add->dateInfo.tm_isdst;
					temp_tm.tm_min = the_day_to_add->dateInfo.tm_min;
					temp_tm.tm_sec = the_day_to_add->dateInfo.tm_sec;
					temp_tm.tm_wday = the_day_to_add->dateInfo.tm_wday;
					temp_tm.tm_yday = the_day_to_add->dateInfo.tm_yday;

					// build the event and add it to its parent and to the event map
					new_event = builder->buildEvent(the_day_to_add, input_event_name, temp_tm, input_recurr_every, input_recurr_for);
					the_day_to_add->addComponent(new_event);
					cal->addEvent(new_event);
				}
				//reset the tm used for each iteration's assignment
				temp_tm = { 0 };
				temp_tm.tm_year = input_year - cal->BASEYEAR;
				temp_tm.tm_mon = input_month;
				temp_tm.tm_mday = input_day;
				temp_tm.tm_hour = input_hour;


				curr_day = input_day;
				curr_month = input_month;
				curr_year = input_year;

				curr_day_index = input_day_index;
				curr_month_index = input_month_index;
				curr_year_index = input_year_index;
				curr_month_length = CalendarComponent::days[curr_month_index];
			}




		}

		else if (in == "edit")
		{
			// edit event
			edit_event();
		}

		else if (in == "delete")
		{
			// find the event to be deleted and delete it from the calendar and the event map
			shared_ptr<Event>eddelete(dynamic_pointer_cast<Event>(currentDisplay));	
			delete_event(eddelete);
			std::multimap <std::string, std::shared_ptr< Event> >::iterator itr;
			for ( itr=cal->emap.begin(); itr != cal->emap.end(); ++itr)
			{
				if (itr->second.get() == eddelete.get())
				{
					break;
				}
			}
			cal->emap.erase(itr);
		}

		else if (in == "search")
		{
			string ename;
			cout << "enter event's name: " << endl;
			cin >> ename;
			search(ename,isEventDisplay);
		}
		else if (in == "jump")
		{
			// kill the garbade line and read in the granularity
			string date,granularity,garbage;
			cout << "Enter a date (formate: August 10th, 2019): ";
			getline(cin, garbage);
			getline(cin, date);
			cout << "Enter granularity (day/month/year):";
			cin >> granularity;
			jump(date,granularity);
		}
		else if (in == "merge")
		{
			cout << "Enter a file name to merge calendar with (in the form of calendarX, where X is a number: " << endl;
			// hold the calendar file to merged. I copy-pasted code from restore and I don't want to change it.
			string name_of_calendar_file_to_be_restored;
			cin >> name_of_calendar_file_to_be_restored;
			ifstream read_calendar_ifstream(name_of_calendar_file_to_be_restored);
			// store the first line which contains general info of the calendar
			string first_line;
			// other lines tore info about events that calendar has
			string other_line;
			// the buildertype of the calendar to be read
			string new_buildertype;
			// the name of the calendar to be read
			string new_cal_name;
			// the start year of the calendar to be read
			int new_tm_start_year;
			// store the number of  years the calendar to be read covers
			int new_number_of_years;
			// the day since sunday for the calendar to be read
			int new_tm_wday;




			// open file, check if able to be openned
			if (read_calendar_ifstream.is_open())
			{
				// get the first line about calendar general info
				getline(read_calendar_ifstream, first_line);
				// convert first_line into a vector
				stringstream ss(first_line);
				istream_iterator<string> begin(ss);
				istream_iterator<string> end;
				vector<string> vector_first_line(begin, end);
				// retrieve the information about the calendar to be merged
				new_buildertype = vector_first_line[read_calendar_field_index::BUILDERTYPE];
				new_cal_name = vector_first_line[read_calendar_field_index::CAL_NAME];
				new_tm_start_year = stoi(vector_first_line[read_calendar_field_index::START_YEAR]);
				new_number_of_years = stoi(vector_first_line[read_calendar_field_index::NUM_YEARS_HOLD]);
				new_tm_wday = stoi(vector_first_line[read_calendar_field_index::WDAY]);

				// record information for the current line (other than the 1st line), which is one event to be processed per itr
				string curr_line_event_name;
				unsigned int curr_line_event_year;
				unsigned int curr_line_event_month;
				int curr_line_event_day;
				int curr_line_event_hour;
				int curr_line_event_recurr_every;
				int curr_line_event_recurr_for;


				//intermediate variables to build the event
				shared_ptr<DisplayableYear> the_year_to_add;
				shared_ptr<DisplayableMonth> the_month_to_add;
				shared_ptr<DisplayableDay> the_day_to_add;
				shared_ptr<Event> new_event;
				tm temp_tm;

				// read the following lines once thre first line is extracted, these represent a list of event info
				while (getline(read_calendar_ifstream, other_line))
				{
					// convert each line to a vector and retrieve the infos about this line, which is an event
					stringstream ss_every_event(other_line);
					istream_iterator<string> begin_every_event(ss_every_event);
					istream_iterator<string> end_every_event;
					vector<string> vector_other_line(begin_every_event, end_every_event);
					curr_line_event_name = vector_other_line[read_events_field_index::EVENT_NAME];
					curr_line_event_year = stoi(vector_other_line[read_events_field_index::EVENT_YEAR]);
					curr_line_event_month = stoi(vector_other_line[read_events_field_index::EVENT_MONTH]);
					curr_line_event_day = stoi(vector_other_line[read_events_field_index::EVENT_DAY]);
					curr_line_event_hour = stoi(vector_other_line[read_events_field_index::EVENT_HOUR]);
					curr_line_event_recurr_every = stoi(vector_other_line[read_events_field_index::RECURR_EVERY]);
					curr_line_event_recurr_for = stoi(vector_other_line[read_events_field_index::RECURR_FOR]);
					
					if (my_current_builder_type == "full")
					{
						the_year_to_add = dynamic_pointer_cast<DisplayableYear>(cal->getChild(curr_line_event_year - cal->dateInfo.tm_year));
						the_month_to_add = dynamic_pointer_cast<DisplayableMonth>(the_year_to_add->getChild(curr_line_event_month));
						the_day_to_add = dynamic_pointer_cast<DisplayableDay>(the_month_to_add->getChild(curr_line_event_day - 1));

						temp_tm = { 0 };
						temp_tm.tm_year = curr_line_event_year;
						temp_tm.tm_mon = curr_line_event_month;
						temp_tm.tm_mday = curr_line_event_day;
						temp_tm.tm_hour = curr_line_event_hour;

						//deep copy of the dateinfo
						temp_tm.tm_isdst = the_day_to_add->dateInfo.tm_isdst;
						temp_tm.tm_min = the_day_to_add->dateInfo.tm_min;
						temp_tm.tm_sec = the_day_to_add->dateInfo.tm_sec;
						temp_tm.tm_wday = the_day_to_add->dateInfo.tm_wday;
						temp_tm.tm_yday = the_day_to_add->dateInfo.tm_yday;

						
						// construct the event and set if it is from external calendar (and that cal's name)
						new_event = builder->buildEvent(the_day_to_add, curr_line_event_name, temp_tm, curr_line_event_recurr_every, curr_line_event_recurr_for);
						new_event->is_external = true;
						new_event->my_cal_name = new_cal_name;
						the_day_to_add->addComponent(new_event);
						eventname_calname_map.insert(pair <string,string>(new_event->my_name, new_cal_name));
					}
					// if builder type is "inc", incremental, then only add the event to the map
					else
					{
						// construct the event and set if it is from external calendar (and that cal's name)
						new_event = builder->buildEvent(the_day_to_add, curr_line_event_name, temp_tm, curr_line_event_recurr_every, curr_line_event_recurr_for);
						new_event->is_external = true;
						new_event->my_cal_name = new_cal_name;
						eventname_calname_map.insert(pair <string, string>(new_event->my_name, new_cal_name));
					}
					// add event to the map
					cal->addEvent(new_event);
				}
			}
			else
			{
				cout << "Unable to open file: " << name_of_calendar_file_to_be_restored << endl;
			}
			read_calendar_ifstream.close();
		}
		else if (in == "save")
		{

			// ofstream to open file to save a calendarsave
			ofstream save_calendar_ofstream;
			// build the name for the file to save a calendar
			string save_file_name = "calendar" + to_string(saved_calendars_enumerate);

			save_calendar_ofstream.open(save_file_name);
			// write/store the general infor about the calendar being stored
			save_calendar_ofstream << 
				cal->builder_type << " " 
				<< cal->name << " " 
				<< cal->dateInfo.tm_year << " " 
				<< cal->yearsToHold << " "
				<< cal->dateInfo.tm_wday <<
				"\n";

			// loop invariants iterating the multimap
			std::multimap <std::string, std::shared_ptr<Event>> current_cal_eventmap = cal->getEventlist();
			// store current iteration's key, that is, the event name
			string temp_event_name;
			shared_ptr<Event> temp_event_ptr;
			// go through each event in the map and write the info out
			for (std::multimap <std::string,std::shared_ptr<Event>>::iterator iter = current_cal_eventmap.begin(); iter != current_cal_eventmap.end(); ++iter)
			{
				temp_event_name = iter->first;
				temp_event_ptr = iter->second;
				save_calendar_ofstream << temp_event_name << " " << temp_event_ptr->dateInfo.tm_year << " " << temp_event_ptr->dateInfo.tm_mon
					<< " " << temp_event_ptr->dateInfo.tm_mday << " " << temp_event_ptr->dateInfo.tm_hour << " " << temp_event_ptr->my_recurr_every 
					<< " " << temp_event_ptr->my_recurr_for << "\n";
			}
			cout << "Your calendar is stored to file name: " << save_file_name << endl;
			save_calendar_ofstream.close();
			++saved_calendars_enumerate;
		}

		else if (in == "restore")
		{
			cout << "Enter a file name to restore calendar from (in the form of calendarX, where X is a number: " << endl;
			string name_of_calendar_file_to_be_restored;
			cin >> name_of_calendar_file_to_be_restored;
			ifstream read_calendar_ifstream(name_of_calendar_file_to_be_restored);
			// store the first line which contains general info of the calendar
			string first_line;
			// other lines tore info about events that calendar has
			string other_line;
			// the buildertype of the calendar to be read
			string new_buildertype;
			// the name of the calendar to be read
			string new_cal_name;
			// the start year of the calendar to be read
			int new_tm_start_year;
			// store the number of  years the calendar to be read covers
			int new_number_of_years;
			// the day since sunday for the calendar to be read
			int new_tm_wday;
			



			// open file, check if able to be openned
			if (read_calendar_ifstream.is_open())
			{
				// get the first line about calendar general info
				getline(read_calendar_ifstream, first_line);
				// convert first_line into a vector
				stringstream ss(first_line);
				istream_iterator<string> begin(ss);
				istream_iterator<string> end;
				vector<string> vector_first_line(begin, end);
				// retrieve the info about the calendar
				new_buildertype = vector_first_line[read_calendar_field_index::BUILDERTYPE];
				new_cal_name = vector_first_line[read_calendar_field_index::CAL_NAME];
				new_tm_start_year = stoi(vector_first_line[read_calendar_field_index::START_YEAR]);
				new_number_of_years = stoi(vector_first_line[read_calendar_field_index::NUM_YEARS_HOLD]);
				new_tm_wday = stoi(vector_first_line[read_calendar_field_index::WDAY]);
				// build different new builders accordingly
				if (new_buildertype == "full") {
					builder = make_shared<FullCalendarBuilder>();
					cal = builder->buildCalendar_from_restore(new_cal_name, new_number_of_years,new_tm_start_year,new_tm_wday);
					cal->builder_type = new_buildertype;
					cal->dateInfo.tm_year = new_tm_start_year;
					cal->dateInfo.tm_wday = new_tm_wday;
					my_current_builder_type = new_buildertype;
					my_current_cal_name = new_cal_name;
					currentDisplay = cal;
					prev_diplay = currentDisplay;
				}
				if (new_buildertype == "inc") {
					builder = make_shared<IncrementalCalendarBuilder>();
					cal = builder->buildCalendar_from_restore(new_cal_name, new_number_of_years, new_tm_start_year, new_tm_wday);
					cal->builder_type = new_buildertype;
					cal->dateInfo.tm_year = new_tm_start_year;
					cal->dateInfo.tm_wday = new_tm_wday;
					my_current_builder_type = new_buildertype;
					my_current_cal_name = new_cal_name;
					currentDisplay = cal;
					prev_diplay = currentDisplay;
				}
				// record information for the current line (other than the 1st line), which is one event to be processed
				string curr_line_event_name;
				unsigned int curr_line_event_year;
				unsigned int curr_line_event_month;
				int curr_line_event_day;
				int curr_line_event_hour;
				int curr_line_event_recurr_every;
				int curr_line_event_recurr_for;
				

				//intermediate variables to build the event
				shared_ptr<DisplayableYear> the_year_to_add;
				shared_ptr<DisplayableMonth> the_month_to_add;
				shared_ptr<DisplayableDay> the_day_to_add;
				shared_ptr<Event> new_event;
				tm temp_tm;

				// read the following lines once thre first line is extracted, these represent a list of event info
				while (getline(read_calendar_ifstream, other_line))
				{
					// convert current line to vector, retireve info for this line, which represents an event
					stringstream ss_every_event(other_line);
					istream_iterator<string> begin_every_event(ss_every_event);
					istream_iterator<string> end_every_event;
					vector<string> vector_other_line(begin_every_event, end_every_event);
					curr_line_event_name = vector_other_line[read_events_field_index::EVENT_NAME];
					curr_line_event_year = stoi(vector_other_line[read_events_field_index::EVENT_YEAR]);
					curr_line_event_month = stoi(vector_other_line[read_events_field_index::EVENT_MONTH]);
					curr_line_event_day = stoi(vector_other_line[read_events_field_index::EVENT_DAY]);
					curr_line_event_hour = stoi(vector_other_line[read_events_field_index::EVENT_HOUR]);
					curr_line_event_recurr_every = stoi(vector_other_line[read_events_field_index::RECURR_EVERY]);
					curr_line_event_recurr_for = stoi(vector_other_line[read_events_field_index::RECURR_FOR]);

					if (my_current_builder_type == "full")
					{
						the_year_to_add = dynamic_pointer_cast<DisplayableYear>(cal->getChild(curr_line_event_year - cal->dateInfo.tm_year));
						the_month_to_add = dynamic_pointer_cast<DisplayableMonth>(the_year_to_add->getChild(curr_line_event_month));
						the_day_to_add = dynamic_pointer_cast<DisplayableDay>(the_month_to_add->getChild(curr_line_event_day - 1));

						temp_tm = { 0 };
						temp_tm.tm_year = curr_line_event_year;
						temp_tm.tm_mon = curr_line_event_month;
						temp_tm.tm_mday = curr_line_event_day;
						temp_tm.tm_hour = curr_line_event_hour;

						//deep copy of the dateinfo
						temp_tm.tm_isdst = the_day_to_add->dateInfo.tm_isdst;
						temp_tm.tm_min = the_day_to_add->dateInfo.tm_min;
						temp_tm.tm_sec = the_day_to_add->dateInfo.tm_sec;
						temp_tm.tm_wday = the_day_to_add->dateInfo.tm_wday;
						temp_tm.tm_yday = the_day_to_add->dateInfo.tm_yday;

						new_event = builder->buildEvent(the_day_to_add, curr_line_event_name, temp_tm, curr_line_event_recurr_every, curr_line_event_recurr_for);
						the_day_to_add->addComponent(new_event);
					}
					// if builder type is "inc", incremental, then only add the event to the map
					else
					{
						new_event = builder->buildEvent(the_day_to_add, curr_line_event_name, temp_tm, curr_line_event_recurr_every, curr_line_event_recurr_for);
					}
					// add event to the map
					cal->addEvent(new_event);
				}
			}
			else
			{
				cout << "Unable to open file: " << name_of_calendar_file_to_be_restored << endl;
			}
			read_calendar_ifstream.close();
		}

		else if (in == "todo")
		{
			// start the To-Do List view and book-keeping of flags
			cout << "in todo" << endl;
			prev_diplay = currentDisplay;
			isTodoDisplay = true;
			isCaldisplay = false;
			currentDisplay = tlist;
		}
		else if (in == "add_task")
		{
			todo_add_task();
			
		}
		else if (in == "mark_task")
		{
			todo_mark_task();
		}
		// if change the current view to calendar
		else if (in == "cview")
		{
			isTodoDisplay = false;
			isCaldisplay = true;
			currentDisplay = prev_diplay;
		}
	}
}

void CalendarInterface::search(std::string ename, bool &isEventDisplay)
{
	// search the event from a map
	multimap <std::string, std::shared_ptr< Event> >emap = cal->getEventlist();
	if (emap.size() == 0)
	{
		cout << "No event found"<<endl;
		return;
	}
	// algorithm to retrieve all the relevant events
	//reference:http://www.cplusplus.com/reference/map/multimap/equal_range/
	std::pair <std::multimap<std::string, std::shared_ptr< Event>>::iterator, std::multimap<std::string, std::shared_ptr< Event>>::iterator> ret;
	ret = emap.equal_range(ename);
	int count = 1;
	bool found = false;
	for (std::multimap<std::string, std::shared_ptr< Event>>::iterator it = ret.first; it != ret.second; ++it, count++)
	{
		found = true;
	}
	int total_event = count - 1;
	if (found == false)
	{
		cout << "No matching event found"<<endl;
		return;
	}
	std::cout << '\n';

	if (total_event == 1)
	{
		currentDisplay= ret.first->second;
	}
	// ask users to choose and event to go on to
	else {
		int icount = 1;
		for (std::multimap<std::string, std::shared_ptr< Event>>::iterator it = ret.first; it != ret.second; ++it, icount++)
		{
			cout << icount << ".";
			it->second->display();
		}
		int enumber;
		
		do{
		cout << " Choose an event (1-" << total_event << "): ";
		cin >> enumber;
		} while (enumber<1 || enumber > total_event);
		
		int chosen = 1;
		std::multimap<std::string, std::shared_ptr< Event>>::iterator itchosen;
		// loop to the right place
		for (itchosen = ret.first; chosen<enumber; ++itchosen, chosen++)
		{

		}
		currentDisplay = itchosen->second;
	}
	isEventDisplay = true;
}

void CalendarInterface::jump(string date,string granularity)
{
	// hold the final place to jump to
	std::vector<std::string> result;
	std::istringstream iss(date);
	for (std::string s; iss >> s; )
		result.push_back(s);
	// check if the format is wrong
	if (result.size() != 3)
	{
		cout << "Wrong format" << endl;
		return;
	}
	// the date info variables hold to be referenced for the jump
	string j_month;
	j_month=result[0];
	
	int j_day;
	istringstream iss1(result[1]);
	iss1 >> j_day;

	int j_year;
	istringstream iss2(result[2]);
	iss2 >> j_year;

	int j_input_month;

	bool mf = false;
	for (unsigned int i = 0;i < CalendarComponent::MONTHS;i++)
	{
		if (j_month == CalendarComponent::months[i])
		{
			mf = true;
			j_input_month = i;
			
		}
	}
	if (mf == false)
	{
		cout << "Wrong month" << endl;
		return;
	}

	// calculate the indices
	int j_input_year_index = j_year - cal->BASEYEAR - cal->dateInfo.tm_year;
	int j_input_month_index = j_input_month;
	int j_input_day_index = j_day - 1;

	if ((unsigned)j_input_year_index > cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold - 1 || j_input_year_index < 0)
	{
		cout << "Wrong year" << endl;
		return;
	}
	if (j_input_day_index >= CalendarComponent::days[j_input_month_index] || j_input_day_index < 0) {
		cout << "wrong day" << endl;
		return;
	}
	// do the jumps and update current display
	if (granularity == "year")
	{
		currentDisplay = cal->getChild(j_input_year_index);
	}
	else if (granularity == "month")
	{
		currentDisplay = cal->getChild(j_input_year_index)->getChild(j_input_month_index);
	}
	else if (granularity == "day")
	{
		currentDisplay = cal->getChild(j_input_year_index)->getChild(j_input_month_index)->getChild(j_input_day_index);
	}
	else
	{
		cout << "wrong granularity" << endl;
	}

}

void CalendarInterface::edit_event()
{
	unsigned int input_year, input_month;
	int input_day;
	cout << "enter a year, e.g., " << cal->dateInfo.tm_year + CalendarComponent::BASEYEAR << "-" << cal->dateInfo.tm_year + CalendarComponent::BASEYEAR + cal->yearsToHold - 1 << ":" << endl;
	cin >> input_year;

	// all the following while loops are checking inputs
	while (true)
	{
		if (cin.fail() || input_year > input_year < cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold -1
			|| input_year < cal->dateInfo.tm_year + cal->BASEYEAR)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a year, e.g., "<<cal->dateInfo.tm_year+ CalendarComponent::BASEYEAR <<" - "<< cal->dateInfo.tm_year + CalendarComponent::BASEYEAR + cal->yearsToHold - 1 <<":"<< endl;
			cin >> input_year;
		}
		else
		{
			break;
		}
	}


	cout << "enter a month, e.g., 1-12: " << endl;
	cin >> input_month;

	while (true)
	{
		if (cin.fail() || input_month > 12 || input_month <1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a month, e.g., 1-12: " << endl;
			cin >> input_month;
		}
		else
		{
			input_month -= 1;
			break;
		}
	}


	cout << "enter a day, e.g., 1-31: " << endl;
	cin >> input_day;

	while (true)
	{
		if (cin.fail() || input_day > 31 || input_day <1
			|| input_day > CalendarComponent::days[input_month])
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a day, e.g., 1-31 according to month: " << endl;
			cin >> input_day;
		}
		else {
			break;
		}
	}

	// compute the indices to get to the correct days
	int input_year_index = input_year - cal->BASEYEAR - cal->dateInfo.tm_year;
	int input_month_index = input_month;
	int input_day_index = input_day - 1;
	int curr_day = input_day;
	unsigned int curr_month = input_month;
	unsigned int curr_year = input_year;

	// each iteration changes a day's event condition. These are temp variables for each itr
	int curr_day_index = input_day_index;
	int curr_month_index = input_month_index;
	int curr_year_index = input_year_index;
	int curr_month_length = CalendarComponent::days[curr_month_index];

	// temp variables to for the path to the target day
	shared_ptr<DisplayableYear> the_year_to_add;
	shared_ptr<DisplayableMonth> the_month_to_add;
	shared_ptr<DisplayableDay> the_day_to_add;
    // algorithm to change the event's assignement to days
	curr_day = curr_day;
	curr_day_index = curr_day - 1;
	while (curr_day > curr_month_length)
	{
		curr_day = curr_day - curr_month_length;
		curr_day_index = curr_day - 1;
		curr_month = curr_month + 1;
		if (curr_month > CalendarComponent::MONTHS - 1)
		{
			curr_month = curr_month - (CalendarComponent::MONTHS - 1) - 1;
			curr_month_index = curr_month;
			curr_month_length = CalendarComponent::days[curr_month_index];
			curr_year = curr_year + 1;
			curr_year_index = curr_year - cal->BASEYEAR - cal->dateInfo.tm_year;
		}
		else
		{
			curr_month_index = curr_month;
			curr_month_length = CalendarComponent::days[curr_month_index];
		}
	}

	// go to the new date and put the event there and delete the old one
	if (curr_year <= cal->dateInfo.tm_year + cal->BASEYEAR + cal->yearsToHold - 1)
	{
		the_year_to_add = dynamic_pointer_cast<DisplayableYear>(cal->getChild(curr_year - cal->BASEYEAR - cal->dateInfo.tm_year));
		the_month_to_add = dynamic_pointer_cast<DisplayableMonth>(the_year_to_add->getChild(curr_month));
		the_day_to_add = dynamic_pointer_cast<DisplayableDay>(the_month_to_add->getChild(curr_day - 1));
		currentDisplay->getParent() = the_day_to_add;
		shared_ptr<Event>ed(dynamic_pointer_cast<Event>(currentDisplay));
		
		ed->dateInfo.tm_mday = the_day_to_add->dateInfo.tm_mday;
		ed->dateInfo.tm_mon = the_day_to_add->dateInfo.tm_mon;
		ed->dateInfo.tm_year = the_day_to_add->dateInfo.tm_year;
		ed->dateInfo.tm_wday = the_day_to_add->dateInfo.tm_wday;
		ed->dateInfo.tm_yday = the_day_to_add->dateInfo.tm_yday;
		ed->dateInfo.tm_isdst = the_day_to_add->dateInfo.tm_isdst;

		the_day_to_add->addComponent(shared_ptr<DisplayableComponent>(ed));
		delete_event(ed);		
	}

	else {
		cout << "Wrong year" << endl;

	}


}

void CalendarInterface::delete_event(shared_ptr<Event> ed)
{
	// get to the event and delete it
	int remfl = 0;
	for (int pi = 0;pi < ed->my_parent->children.size();pi++)
	{
		if (ed->my_parent->getChild(pi).get() == ed.get())
		{
			remfl = 1;
			std::shared_ptr<DisplayableComponent>temp=ed->my_parent->removeComponent(pi);
			
		}
	}
	if (remfl == 0)
	{
		cout << "cannot remove event" << endl;
	}
	
	
	
}

void CalendarInterface::todo_add_task()
{
	// hold the user inputs 
	string task_name;
	cout << "enter a new task's name: ";
	cin >> task_name;
	unsigned int input_year = 0;
	unsigned int input_month = 0;
	int input_day = 0;
	int input_hour = 0;
	int input_min = 0;

	// all the following while loops are checking validity
	cout << "enter a new task's year, e.g.,"<<cal->dateInfo.tm_year+ CalendarComponent::BASEYEAR <<"-"<< cal->dateInfo.tm_year + CalendarComponent::BASEYEAR + cal->yearsToHold - 1 <<":"<< endl;
	cin >> input_year;

	while (true)
	{
		if (cin.fail() || input_year > 2023 || input_year < cal->dateInfo.tm_year + CalendarComponent::BASEYEAR)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a new task's year, e.g.," << cal->dateInfo.tm_year + CalendarComponent::BASEYEAR << "-" << cal->dateInfo.tm_year + CalendarComponent::BASEYEAR + cal->yearsToHold - 1 << ":" << endl;
			cin >> input_year;
		}
		else
		{
			break;
		}
	}


	cout << "enter a new task's month, e.g., 1-12: " << endl;
	cin >> input_month;

	while (true)
	{
		if (cin.fail() || input_month > 12 || input_month <1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a new task's month, e.g., 1-12: " << endl;
			cin >> input_month;
		}
		else
		{
			input_month -= 1;
			break;
		}
	}


	cout << "enter a new task's day, e.g., 1-31: " << endl;
	cin >> input_day;

	while (true)
	{
		if (cin.fail() || input_day > 31 || input_day <1
			|| input_day > CalendarComponent::days[input_month])
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a new task's day, e.g., 1-31 according to month: " << endl;
			cin >> input_day;
		}
		else {
			break;
		}
	}

	cout << "enter a new task's hour, e.g., 0-23: " << endl;
	cin >> input_hour;

	while (true)
	{
		if (cin.fail() || input_hour > 23 || input_hour <0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a new task's hour, e.g., 0-23: " << endl;
			cin >> input_hour;
		}
		else {
			break;
		}
	}

	cout << "enter a new task's minute, e.g., 0-59: " << endl;
	cin >> input_min;
	while (true)
	{
		if (cin.fail() || input_hour > 59 || input_hour <0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter a new task's hour, e.g., 0-24: " << endl;
			cin >> input_min;
		}
		else {
			break;
		}
	}
    // construct the tm for the new task and add it
	std::tm input_tm = { 0 };
	input_tm.tm_year = input_year - cal->BASEYEAR;
	input_tm.tm_mon = input_month;
	input_tm.tm_mday = input_day;
	input_tm.tm_hour = input_hour;
	input_tm.tm_min = input_min;

	tlist->create_and_addTask(task_name, input_tm);
}

void CalendarInterface::todo_mark_task()
{
	// get user input and mark the task to be completed
	if (tlist->children.size() == 0)
	{
		cout << "no task to mark" << endl;
		return;
	}
	tlist->display();

	int index;
	do {
		cout << "Which task is completed?(0-" << tlist->children.size() - 1 << ")" << endl;
		cin >> index;
	} while (index>tlist->children.size() - 1 || index<0);
	Task *t = dynamic_cast<Task*>(tlist->getChild(index).get());
	t->setStatusComplete();
}



void CalendarInterface::zoomIn(unsigned int index) {
	
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr) {
		currentDisplay = temp;
	}
}



void CalendarInterface::zoomOut() {
    // if the current display has a parent, update current display to the parent
	if (currentDisplay->getParent().lock() != nullptr) {
		// create a shared_ptr from a weak_ptr, contributing to the objects reference count
		currentDisplay = currentDisplay->getParent().lock();
	}
}

