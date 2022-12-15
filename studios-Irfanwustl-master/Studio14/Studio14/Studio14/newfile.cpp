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


wrapper::wrapper() : detec_obj(0)//,flag(true)
{
	detec_obj = new detector();
}

wrapper::~wrapper()
{
	//if (flag) {
		delete detec_obj;
	//}
	
}


wrapper::wrapper(const wrapper & obj)
{
	//flag = false;
	detec_obj = new detector;
	detec_obj->x = obj.detec_obj->get_x();
}

