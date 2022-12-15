// Studio9.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<vector>

#include <forward_list>
#include<list>
#include<deque>
#include<algorithm>



using namespace std;

int main()
{
	vector <int>vec;
	forward_list<int>fl;
	list<int>l;
	deque<int>dq;

	int a[3] = { 3,1,2 };

	for (int i = 0;i < 3;i++)
	{
		vec.push_back(a[i]);
		
		l.push_back(a[i]);
		dq.push_back(a[i]);
	}

	for (int i = 2;i >=0;i--) {
		fl.push_front(a[i]);
	}
	
	////q1
	
	cout << "Elements in vector: ";
	for (int i = 0;i < 3;i++)
	{
		cout << vec[i] << " ";

	}
	cout << endl;

	cout << "Elements in forward_list: ";
	for (auto it =fl.begin();it!=fl.end() ;it++)
	{
		cout << *it << " ";

	}
	cout << endl;

	cout << "Elements in list: ";
	for (auto it = l.begin();it!=l.end();it++)
	{
		cout << *it << " ";

	}
	cout << endl;

	cout << "Elements in deque: ";
	for (int i = 0;i < 3;i++)
	{
		cout << dq[i] << " ";

	}
	cout << endl;
	

	/*
	sort(vec.begin(),vec.end());

	cout << "Elements in sorted vector: ";
	for (int i = 0;i < 3;i++)
	{
		cout << vec[i] << " ";

	}
	cout << endl;

	sort(dq.begin(), dq.end());

	cout << "Elements in sorted deque: ";
	for (int i = 0;i < 3;i++)
	{
		cout << dq[i] << " ";

	}
	cout << endl;
	*/

	

	reverse(vec.begin(), vec.end());

	cout << "Elements in reversed vector: ";
	for (int i = 0;i < 3;i++)
	{
		cout << vec[i] << " ";

	}
	cout << endl;

	reverse(dq.begin(), dq.end());
	cout << "Elements in reversed deque: ";
	for (int i = 0;i < 3;i++)
	{
		cout << dq[i] << " ";

	}
	cout << endl;

	reverse(l.begin(), l.end());

	cout << "Elements in reversed list: ";
	for (auto it = l.begin();it != l.end();it++)
	{
		cout << *it << " ";

	}
	cout << endl;





    return 0;
}

