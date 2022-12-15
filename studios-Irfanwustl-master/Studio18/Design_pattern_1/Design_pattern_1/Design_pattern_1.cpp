// Design_pattern_1.cpp : Defines the entry point for the console application.
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
		
		mo.addOperation('+', &ad);
		mo.addOperation('-', &sub);
		mo.addOperation('*', &mult);
		mo.addOperation('/', &div);
		

		infixparseStrategy inp;
		prefixparseStrategy prep;
		
		mo.setParser(&inp);
		string str;
		cout << "infix input:";
		getline(cin, str);
		cout << "infix result=" << mo.calculate(str) << endl;
		mo.setParser(&prep);
		cout << "prefix input:";
		getline(cin, str);
		
		cout << "prefix result=" << mo.calculate(str) << endl;
	}
	return 0;
}

