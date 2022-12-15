/*
Author: Jon Shidal
Purpose: create a CalendarInterface object and call run
*/

#include "stdafx.h"
#include "CalendarInterface.h"
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {


	CalendarInterface ci("inc", "test", 5);

	ci.run();
	return 0;
}