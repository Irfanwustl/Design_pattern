#pragma once
#include "CalendarBuilder.h"
#include "Event.h"
#include <map> 
// Concrete builder class
// builds an incremental builder that builds parts on demand
class CalendarInterface;
class IncrementalCalendarBuilder : public CalendarBuilder {
	friend CalendarInterface;
public:

	virtual std::shared_ptr<Event> buildEvent(std::shared_ptr<DisplayableComponent>, std::string name, std::tm when, int recurrEvery, int recurrFor) override;
	virtual std::shared_ptr<DisplayableComponent> getComponentByDate(std::shared_ptr<DisplayableComponent> cal, std::tm d, std::string granularity) override;
	virtual std::shared_ptr<Calendar> buildCalendar(std::string name, size_t years) override;
	virtual std::shared_ptr<Calendar> buildCalendar_from_restore(std::string name, size_t years, int tm_start_year, int tm_wday) override;
protected:
	virtual std::shared_ptr<DisplayableComponent> buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
	virtual std::shared_ptr<DisplayableComponent> buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) override;
};
