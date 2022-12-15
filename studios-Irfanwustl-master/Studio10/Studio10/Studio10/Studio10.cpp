// Studio10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<iterator>
#include <fstream>

using namespace std;



int main(int argc, char *argv[])
{
	multiset<string> ms;
	set<string>s;
	map<string,int>m;

	//2.1
	copy(argv, argv + argc, inserter(ms,ms.begin()));


	ostream_iterator<string> o(cout," ");

	//copy(ms.begin(), ms.end(), o);

	///2.2
	copy(ms.begin(), ms.end(), inserter(s,s.begin()));
	//cout<<"\nset size:"<<s.size()<<endl;
	//copy(s.begin(), s.end(), o);

	///q3
	//cout << endl<<"...............q3............\n";
	for (auto itr = s.begin();itr != s.end();itr++)
	{
		int num = count(ms.begin(), ms.end(), *itr);
		m[*itr] = num;
		//cout << *itr<<"="<<num << endl;
	}

	
	for (auto itr = m.begin();itr != m.end();itr++)
	{
		cout << itr->first << ":" << itr->second << endl;
	}

	ofstream output_file("out.txt");
	for (auto itr = m.begin();itr != m.end();itr++)
	{
		output_file << itr->first << ":" << itr->second << endl;
	}

	cout << "done\n";
	cout << output_file.is_open() << endl;
	output_file.close();
	cout << output_file.is_open() << endl;

	


    return 0;
}

