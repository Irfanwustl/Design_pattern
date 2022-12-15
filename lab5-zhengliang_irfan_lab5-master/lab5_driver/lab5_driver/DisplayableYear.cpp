#include "stdafx.h"
#include "DisplayableYear.h"
#include <iostream>
#include "DisplayableMonth.h"

using namespace std;

DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l) {
	for (size_t i = 0; i < CalendarComponent::MONTHS; ++i) {
		children.push_back(nullptr);
	}
}

void DisplayableYear::display(int d) {
	///irf
	if(d==0)
	{ 
		cout << "Year " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
		auto md = dateInfo.tm_mon;
		for (size_t i = 0; i < children.size(); ++i) { 
			cout <<"\t"<<i << " " << CalendarComponent::months[md + i] << endl;
		
				if (children[i] != nullptr) { // forward request to all children
					//children[i]->display('m');
					children[i]->display(d+1);
				}
				else
				{
					
				}
		}
	}
	else if (d == 1)
	{
		cout << "\tYear " << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
		for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
			if (children[i] != nullptr) {
				children[i]->display(d+1);
			}
		}
	}

}

shared_ptr<DisplayableComponent> DisplayableYear::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableMonth
	DisplayableMonth * m = dynamic_cast<DisplayableMonth *>(comp.get());
	if (m == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	// otherwise, add the month to the correct location
	int monthOfYear = m->dateInfo.tm_mon;
	if (children[monthOfYear] == nullptr) { // month does not already exist
		children[monthOfYear] = comp;
		return comp;
	}
	else {  // month already exist, return existing month
		return children[monthOfYear];
	}
}
