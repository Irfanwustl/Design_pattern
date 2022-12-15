// designpatternintro.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"calculators.h"
#include<iostream>

using namespace std;

int main()
{
	/*
	CalculatorBase *c = new SimpleCalculator();
	inFixParser p;
	c->setParser(&p);
	c->addOperation('*');
	c->addOperation('/');
	c->addOperation('+');
	c->addOperation('-');
	cout << "result: " << c->calculate("10 + 100 * 2 / 50") << endl;
	return 0;
	*/

	CalculatorBase *c = new PrecedenceCalculator();
	inFixParser p;
	c->setParser(&p);
	
	c->addOperation('*');
	c->addOperation('/');
	c->addOperation('+');
	c->addOperation('-');
	cout << "result: " << c->calculate("10 + 100 * 2 / 50") << endl;
	return 0;
}
