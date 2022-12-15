// Studio3soln.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;


int main(int argc, char * argv[])
{
	//Answer to Question 2:
	cout << argv[0] << endl;


	//Answer to Question 3:
	//const char *p= &argv[0][0];
	const char *p = *argv;

	for ( ;*p!=0;p++)
	{
		cout <<*p ;
	}

	cout << endl;

	
	//Answer to Question 4:
	/*
	char &r = argv[0][0];
	cout << r << endl;

	&r=&r+3;

	cout << r << endl;
	*/
	
	//Answer to Question 5:
	auto ap= *argv;
	//cout << typeid(ap).name()<<endl;
	for (;*ap != 0;*ap++)
	{
		cout << *ap;
	}

	cout << endl;

	

	//Answer to Question 6: 
	

	const char *str;
	
	 for (int s = 0;s < argc;s++)
	 {
		 str = *(argv+s);
		 for (;*str != 0;str ++)
		 {
			 cout << *str;
		 }
		 cout << endl;
	 }

	 //Answer to Question 7 part 1:
	 decltype(*argv) dp= *argv;
	 for (;*dp != 0;dp++)
	 {
		 
		 cout << *dp;
	 }

	 cout << endl;

	 //Answer to Question 7 part 2:
	 /*decltype(*argv) dp;
	 dp=*argv;
	 for (;*dp != 0;dp++)
	 {

		 cout << *dp;
	 }

	 cout << endl;
	 */

	 
	
	
	
    return 0;
}

