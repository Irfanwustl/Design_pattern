#include "stdafx.h"
#include "Newfile.h"
#include<iostream>

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

calculator::calculator(){}
calculator::~calculator()
{
	delete ps;
	for (std::map<char, calculatable *>::iterator itr = cal_obj_map.begin();itr != cal_obj_map.end();itr++)
	{
		delete itr->second;
	}
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

int calculator::calculate(string exp)
{
	string str = ps->parse(exp);

	
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

void calculator::setParser(parseStrategy *ps)
{
	this->ps = ps;
}

int mod::calculate(int a, int b)
{
	return a%b;
}



string infixparseStrategy::parse(string str) {
	return str;
}

void prefixparseStrategy::parseHelper(istringstream & iss, ostringstream &oss)
{
	
	string value;
	if (iss >> value) {
		if (value == "+" || value == "-" || value == "/" || value == "*") {   // value is an operand
			
			parseHelper(iss, oss); // parse the first operand
			oss << " " << value; // write the operator
			parseHelper(iss, oss); // parse the next operand
		}
		else { // the value is an int
			istringstream iss2(value);
			int op;
			iss2 >> op;
			
			oss << " " << op;
		}
	}

}

string prefixparseStrategy::parse(string exp)
{
	
	
	string parsed; // string to hold result of parsing
	istringstream iss(exp);
	ostringstream oss;
	parseHelper(iss, oss);
	parsed = oss.str();
	//cout << parsed << endl; // for debugging purposes
	return parsed;

}

int builder_concrete::buildCalculator()
{
	if (calp==nullptr) {
		calp = new calculator;
		return 0;
	}
	else
	{
		return 1;
	}
	
}

calculator * builder_concrete::getResult()
{
	return calp;
}

void builder_concrete::buildParser(std::string type)
{
	parseStrategy  *ps;

	if (type == "infix")
	{
		ps = new infixparseStrategy;
	}
	else if (type == "prefix")
	{
		ps = new prefixparseStrategy;
	}
	else {
		cout << "wrong parsing type" << endl;
		return;
	}
	calp->setParser(ps);
}

void builder_concrete::buildOperation(char o)
{
	calculatable *calable;
	if (o == '+') {
		calable = new addable;
	}
	else if (o == '-') {
		calable = new subtractable;
	}
	else if (o == '/') {
		calable = new dividable;
	}
	else if (o == '*') {
		calable = new multipliable;
	}
	else {
		cout << "Wrong operation" << endl;
		return;
	}
	calp->addOperation(o, calable);
}

void builder_class::deleteCalculator()
{
	delete calp;
	calp = nullptr;
}
