#include "stdafx.h"
#include "newfile.h"
#include<iostream>
using namespace std;



unsigned int detector::y = 0;

detector::detector()
{
	x = y;
	y++;
	cout << "detector() address=" << this << " x=" << x<<"  real=="<<y<<endl;
}

detector::~detector()
{
	cout << "~detector() address=" << this << " x=" << x <<"  real=="<<y<< endl;
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
	cout << "....entering deep copy...." << endl;
	cout << "real detector obj=" << obj.detec_obj->y << endl;
	cout << "temp detector obj=" << obj.detec_obj->get_x() << endl;
	//flag = false;
	detec_obj = new detector;
	detec_obj->x = obj.detec_obj->get_x();
	cout << "temp detector obj=" << obj.detec_obj->get_x() << endl;
	cout << "real detector obj=" << obj.detec_obj->y << endl;
	cout << ".....leaving deep copy ...." << endl;
}

wrapper & wrapper::operator=(const wrapper & obj)
{
	cout << " copy assignment start"<<endl;
	//cout << "real detector obj=" << obj.detec_obj->y << endl;
	//cout << "temp detector obj=" << obj.detec_obj->get_x() << endl;
	if (this == &obj)
	{

	}

	else
	{
		wrapper ob2 = wrapper(obj);
		swap(ob2.detec_obj, detec_obj);
	}

	//cout << "temp detector obj=" << obj.detec_obj->get_x() << endl;
	//cout << "real detector obj=" << obj.detec_obj->y << endl;
	cout << "copy assignment end"<<endl;
	return *this;
	// TODO: insert return statement here
}


wrapper::wrapper(wrapper && obj) : detec_obj(obj.detec_obj)
{
	cout << " entering move constructor" << endl;
	obj.detec_obj = nullptr;
	cout<<"leaving move constructor" << endl;
	
}

wrapper & wrapper::operator=(wrapper && obj)
{
	cout << "Entering move assignment" << endl;
	if (&obj != this)
	{
		delete detec_obj;
		detec_obj = obj.detec_obj;
		obj.detec_obj= nullptr;
	}
	cout << "leaving move assignment" << endl;
	return *this;

	// TODO: insert return statement here
}
