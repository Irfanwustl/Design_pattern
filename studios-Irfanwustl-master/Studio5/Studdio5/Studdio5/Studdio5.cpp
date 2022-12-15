// Studdio5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

void mySwap(int &x, int &y)
{
	cout << "swapq3" << endl;
	int t = x;
	x = y;
	y = t;

}


void mySwap(int* &x, int* &y)
{
	cout << "swapq4" << endl;

	int* t = x;
	x = y;
	y = t;
}

void mySwap(int* const &x, int* const &y)
{
	cout << "swapq5" << endl;

	int t = *x;
	*x = *y;
	*y = t;
}


///q6
bool reduce(int &a, int &b)
{
	cout << a << " " << b << endl;
	
	int min, max;
	if (a >= b)
	{
		max = a;
		min = b;
	}
	else {
		max = b;
		min = a;
	}
	
	for (int i = min;i >=2;i--)
	{
		if (max%i == 0 && min%i == 0)
		{
			cout << " i==" << i << endl;
			a = a/i;
			b = b/i;
			return true;
		}
	}

	

	return false;


}



int main(int argc, char *argv[])
{
	
	/*
	//q2
	int a = 5, b = 6;
	int * p =& a,  *q = &b;

	//q3
	//mySwap(a, b);

	//q4
	//mySwap(p, q);

	//q5.1
	mySwap(p, q);
	cout << "a=" << a << " b=" << b << endl;

	cout << " pointer a=" << *p << " pointer b=" << *q << endl;

	//q5.2
	int * const w = &a, * const r = &b;

	mySwap(w, r);
	cout << "a=" << a << " b=" << b << endl;

	cout << " w=" << *w << " r=" << *r << endl;
	*/

	///q6

	int x, y;
	cin >> x >> y;
	bool b = reduce(x, y);

	cout << "changed?=" << b << " x=" << x << " y="<<y << endl;

	


    return 0;
}

