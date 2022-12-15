#include "stdafx.h"
#include "newfile.h"
#include<iostream>
using namespace std;



unsigned int detector::y = 0;

detector::detector()
{
	x = y;
	y++;
	cout << "detector() address=" << this << " x=" << x<<endl;
}

detector::~detector()
{
	cout << "~detector() address=" << this << " x=" << x << endl;
}

unsigned int detector::get_x()
{
	return x;
}
