#include "stdafx.h"

#include "newfile.h"

#include<iostream>
using namespace std;

myclass::myclass()
{
	cout << "myclass myclass()" << endl;
}

myclass::~myclass()
{
	cout << "myclass ~myclass()" << endl;
}

void myclass::same()
{
	cout << "myclass void same()" << endl;
}

Derived::Derived()
{
	cout << "Derived  Derived()" << endl;
}

Derived::~Derived()
{
	cout << "Derived ~Derived()" << endl;
}

void Derived::same()
{
	cout << "Derived void same()" << endl;
}
