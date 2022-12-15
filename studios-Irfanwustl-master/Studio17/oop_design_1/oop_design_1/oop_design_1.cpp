// oop_design_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include"Newfile.h"

#include<iostream>
#include<string>
using namespace std;


int main()
{
	while (1)
	{

	
	calculator mo;
	addable ad;
	subtractable sub;
	multipliable mult;
	dividable div;
	mod m;
	mo.addOperation('+',&ad);
	mo.addOperation('-', &sub);
	mo.addOperation('*', &mult);
	mo.addOperation('/', &div);
	mo.addOperation('%', &m);
	/// 1 to 5
	/*
	int a, b;
	cin >> a >> b;
	cout << "add="<<mo.calculate('+', a, b)<<endl;
	cout << "sub=" << mo.calculate('-', a, b) << endl;
	cout << "mult=" << mo.calculate('*', a, b) << endl;
	cout << "div=" << mo.calculate('/', a, b) << endl;
	cout << "mod=" << mo.calculate('%', a, b) << endl;
	*/
	string str;
	getline(cin, str);
	cout<<"result="<<mo.calculate(str)<<endl;
	}
	return 0;
}

