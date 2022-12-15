#include "stdafx.h"
#include "Newfile.h"
#include<iostream>
#include <sstream>
using namespace std;

int addable::calculate(int a, int b)
{
	return a + b;
}

int subtractable::calculate(int a, int b)
{
	return a - b;
}

int multipliable::calculate(int a, int b)
{
	return a * b;
}

int dividable::calculate(int a, int b)
{
	if (b == 0) {
		cout << "divide by 0" << endl;
		return 0;
	}
	return a / b;
}

void calculator::addOperation(char op, calculatable *ob_p)
{
	cal_obj_map.insert(std::pair<char, calculatable*>(op, ob_p));
}

int calculator::calculate(char c, int a, int b)
{
	std::map<char, calculatable*>::iterator itr=cal_obj_map.find(c);
	if (itr == cal_obj_map.end())
	{
		return -1;
	}

	return itr->second->calculate(a, b);

	
}

int calculator::calculate(string str)
{
	std::istringstream iss(str);
	int a;
	char op;
	result_so_far = 0;
	
	iss >> a;
	op = '+';
	do {
		result_so_far = calculate(op, result_so_far, a);

	} while (iss>>op && iss>>a);
	return result_so_far;
}

int mod::calculate(int a, int b)
{
	return a%b;
}
