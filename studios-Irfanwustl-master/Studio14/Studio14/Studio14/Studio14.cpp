// Studio14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "newfile.h"
#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
	cout << " main start" << endl;
	wrapper w_obj;
	wrapper w_2 = w_obj;
	cout << "really? main end" << endl;
    return 0;
}

