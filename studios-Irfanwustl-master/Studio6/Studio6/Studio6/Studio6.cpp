// Studio6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<vector>
#include<iostream>
using namespace std;


int squareElement(vector<int> input_vec, unsigned int index)
{
		cout << "entering squareElement" << endl;
	
		if (index >= input_vec.size() || index<0) {
			throw out_of_range("vector out of range");
		}

		cout << "leaving squareElement" << endl;
		return input_vec[index] * input_vec[index];
	
}

float divideSquaredElements(vector<int> input_vec, unsigned int index1, unsigned int index2)
{
	cout << "enetering divideSquaredElements" << endl;
	int a = squareElement(input_vec,index1);
	int b = squareElement(input_vec, index2);

	if (b == 0)
	{
		throw logic_error("divive by zero");
	}
	cout << "leaving divideSquaredElements" << endl;
	return (float)a / b;
}

int main(int argc, char *argv[])
{

	vector<int>testvec;
	testvec.push_back(1);

	testvec.push_back(2);

	testvec.push_back(0);

	testvec.push_back(8);


	/*for (unsigned int i = 0;i < testvec.size();i++)
	{
		cout << squareElement(testvec, i)<<endl;
	}*/
	////// q2
	/*try {
		cout << squareElement(testvec, 4) << endl;
	}
	catch (out_of_range e)
	{
		cout << e.what() << endl;
	}*/

	//q3 q4
	try {
		float f= divideSquaredElements(testvec, 3, 5);
	}
	
	catch (out_of_range e)
	{
		//cout << "in range catch, error:"<<e.what() << endl;
		
	}
	
	catch (logic_error e)
	{
		//cout << "in logic catch, error:"<< e.what()<<endl;
		

	}
	


    return 0;
}

