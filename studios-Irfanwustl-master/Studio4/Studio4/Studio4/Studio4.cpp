// Studio4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;


int main(int argc, char * argv[])
{
	///Question 2
	/*
	unsigned int arr[2][3][5] = {0};

	for (unsigned int i = 0;i < 2;i++)
	{
		for (unsigned int j = 0;j < 3;j++) {
			for (unsigned int k = 0;k < 5;k++)
			{
				arr[i][j][k] = i*j*k;
			}
		}
	}

	for (unsigned int i = 0;i < 2;i++)
	{
		for (unsigned int j = 0;j < 3;j++) {
			for (unsigned int k = 0;k < 5;k++)
			{
				cout<<"coordinates "<<i<<" "<<j<<" " <<k<<" value:"<<arr[i][j][k]<<endl;
			}
		}
	}

	//question 3
	vector <string>str_vec;

	for (int i = 0;i < argc;i++) {
		str_vec.push_back(argv[i]);
	}

	for (int i = 0;i < str_vec.size();i++)
	{
		cout << str_vec[i] << endl;
	}
	

	//question 4
	
	string bigstring;
	
	
	for (int i = 0;i < argc;i++) {
		if (i == 0) {
			bigstring = bigstring + argv[i];
		}
		else
		{
			bigstring = bigstring + " "+argv[i];
		}
		
	}
	istringstream iss(bigstring);
	string temp;
	//iss.str(bigstring);
	while (1) {
		iss >> temp;
		cout << temp << endl;
		if (iss.eof())break;
	}
	*/


	///q5
	if (argc == 3)
	{
		cout << argv[1] << endl;
		cout << argv[2] << endl;
		return 0;
	}
	else {
		cout << argv[0] << "\nplease run with 2 additional arguments" << endl;
		return 1;

	}

	
    
}

