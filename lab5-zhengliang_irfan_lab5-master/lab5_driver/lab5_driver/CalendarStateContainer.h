#pragma once
#include <map>
#include "Event.h"
#include "Calendar.h"


class CalendarStateContainer {
	std::multimap <std::string, std::shared_ptr<Event> > emap;
	std::shared_ptr<Calendar>cal;
};