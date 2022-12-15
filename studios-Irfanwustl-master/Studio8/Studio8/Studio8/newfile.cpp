
#include "stdafx.h"
#include "newfile.h"
#include<iostream>
using namespace std;

mystruct::mystruct():a(0), b(0) {
	cout << "contructor:" << " a=" << a << " b=" << b << " address of a=" << &a << " address of b=" << &b << endl;
}


mystruct::mystruct(mystruct & const obj):a(obj.get_a()),b(obj.get_b())
{
	
	cout << "copy contructor:"<<" a="<<a<<" b="<<b<<" address of a="<<&a<<" address of b="<< &b << endl;
}

int mystruct::get_a() const
{
	return a;
}

int mystruct::get_b() const
{
	return b;
}

mystruct & mystruct::set_a(int n)
{
	this->a = n;
	return *this;
	// TODO: insert return statement here
}

mystruct & mystruct::set_b(int n)
{
	this->b = n;
	return *this;
	// TODO: insert return statement here
}
