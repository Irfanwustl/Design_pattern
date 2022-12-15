// Studio16.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include<iostream>

using namespace std;


class Calculatable
{
public:
	virtual int calculate(int, int) = 0;



};

class addition :public Calculatable {
	virtual int calculate(int a, int b) {
		return a + b;
	}
};

class subtraction :public Calculatable {
	virtual int calculate(int a, int b) {
		return a - b;
	}
};

class multiplication :public Calculatable {
	virtual int calculate(int a, int b) {
		return a * b;
	}
};


class division :public Calculatable {
	virtual int calculate(int a, int b) {
		if (b == 0)
		{
			cout << "divide by 0" << endl;
			return 0;
		}
		return a / b;
	}
};
/*
class Calculator {
	int result_so_far;
public:
	Calculator() :result_so_far(1) {

	}

	void calculate(int n) {
		result_so_far *= n;
	}
	int getResult() {
		return result_so_far;
	}
};
*/

int main()
{
	/*
	Calculator calobj;
	calobj.calculate(5);
	cout << calobj.getResult() << endl;
	calobj.calculate(6);
	cout << calobj.getResult() << endl;
	*/

	Calculatable *obj;
	addition adobj;
	subtraction subobj;
	multiplication mulobj;
	division divobj;

	while(1){
	char ch;
	cout << "Enter a mathematical symbol:" << endl;
	cin >> ch;
	if (ch=='+')
	{
		obj = &adobj;
	}
	else if (ch == '-')
	{
		obj = &subobj;
	}
	else if (ch == '*')
	{
		obj = &mulobj;
	}
	else if (ch == '/')
	{
		obj = &divobj;
	}
	else
	{
		cout << "wrong symbol" << endl;
		continue;
	}

	cout << "Enter two  integers:" << endl;
	int a, b;
	cin >> a >> b;

	cout << obj->calculate(a,b) << endl;
	}
    return 0;
}

