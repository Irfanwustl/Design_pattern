// Studio15.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include "newfile.h"
using namespace std;



int main(int argc, char *argv[])
{
	int x = 3, y = 5;
	int &a = x, &b = y;
	int &&r1 = x + 1,&&r2 = y + 1;
	/*
	cout << "r1=" << r1 << " r2=" << r2 << endl;

	x = a;
	y = r1;
	cout << "y=" << y << endl;

	r2 = a;
	cout << "r2=" << r2 << endl;
	b = r1;
	cout << " b=" << b << endl;
	*/

	/*
	int &&as = std::move(x);
	int &&bs = move(y);
	cout << "as=" << as << " bs=" << bs << endl;
	cout << "x=" << x << " y=" << y << endl;
	int k = x;
	int p;
	p = x;
	cout << "k=" << k<< " p="<<p << endl;

	int j = k;
	cout << "j=" << j << endl;
	*/
	cout << " main start" << endl;
	wrapper w_obj,o2,o3;
	
	//cout << "start copy cons " << endl;
	//wrapper o9= wrapper( w_obj);
	//cout << "end copy cons " << endl;
	

	//cout << "start move" << endl;
	//wrapper mo = move(w_obj);
	//cout << "end move" << endl;


	/*
	cout << "\n\n\n\n start assign" << endl;

	o2 = w_obj;

	cout << "end assigne" << endl;
	*/
	

	//cout << "\n\n\n\n" << endl;
	o2 = w_obj;

	//cout << "\n\n move?" << endl;
	o3 = move(o3);
	//cout << "end main" << endl;
	
    return 0;
}

