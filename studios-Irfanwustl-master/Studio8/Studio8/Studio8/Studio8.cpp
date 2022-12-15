// Studio8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include "newfile.h"

using namespace std;


mystruct vv(mystruct ob) {
	return ob;
}

mystruct & rr(mystruct & ob) {
	return ob;
}

int main()
{
	

	
	
	/////q 4
	/*
	mystruct obj;
	const mystruct obj2;
	cout <<"From non const object a=" <<obj.get_a() << " b=" << obj.get_b() << endl;

	cout<< "From const object a=" << obj2.get_a() << " b=" << obj2.get_b() << endl;

	obj.set_a(5);
	obj.set_b(6);

	/*
	obj2.set_a(8);
	obj2.set_b(9);
	*/

	//cout << "From non const object after setting values a=" << obj.get_a() << " b=" << obj.get_b() << endl;
	

	///q5

	/*
	mystruct m; // default construction 
	cout << "m.a =" << m.get_a() << " and m.b = "<< m.get_b() << endl;
	m.set_a(7).set_b(3); // chained use of mutator functions 
	cout << "m.a = " << m.get_a() << " and m.b = " << m.get_b() << endl;
	mystruct n(m); // copy construction 
	cout << "n.x = " << n.get_a() <<" and n.b = " << n.get_b() << endl;
	*/

	//q6
	mystruct m,p,q;
	p=vv(m);
	q=rr(m);
	



    return 0;
}

