// Studio12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "newfile.h"
#include<iostream>
using namespace std;


///q6
void call_by_value_base(myclass obj)
{
	obj.same();
}

void call_by_ref_base(myclass & obj)
{
	obj.same();
}

int main()
{
	myclass m;
	Derived d;

	/////q3
	/*
	myclass & rm1=m,& rm2 = d;
	Derived & rd1 = d;

	cout << "call using myclass object\n";
	m.same();

	cout << "call using myclass reference initialized using myclass object\n";
	rm1.same();

	cout << "call using myclass reference initialized using Derived object\n";
	rm2.same();

	cout << "call using Derived reference\n";
	rd1.same();
	*/

	//q4
	/*
	myclass * rm1 =& m, *rm2 = &d;
	Derived * rd1 = &d;

	cout << "call using myclass object\n";
	m.same();

	cout << "call using myclass pointer initialized using myclass object\n";
	rm1->same();

	cout << "call using myclass pointer initialized using Derived object\n";
	rm2->same();

	cout << "call using Derived pointer\n";
	rd1->same();
	*/

	//q5

	cout << " ........q5.......\n";
	
	myclass * rm1 =new myclass, *rm2 =new Derived;
	Derived * rd1 =new Derived ;
	
	/*
	
	delete rm1;
	delete rm2;
	delete rd1;
	*/

	///q6
	//call_by_value_base(m);
	
	//call_by_value_base(*rm2);

	//call_by_ref_base(m);
	call_by_ref_base(*rm2);
	
    return 0;
}

