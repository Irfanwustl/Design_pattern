// Studio11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iterator>
#include <fstream>

using namespace std;

class Student {

	friend ifstream & operator >> (ifstream & in, Student &obj);
	friend ostream & operator<<(ostream & o, const Student  & obj);
public:
	string name;
	unsigned int id;
	Student() {};
	Student(string str,unsigned int n):name(str),id(n) {};
	/*
	bool operator <(Student obj)
	{
		if (id <= obj.id) {
			return true;
		}
		return false;
	}
	*/
};

bool operator <(Student obj1, Student obj2)
{
	if (obj1.id <= obj2.id) {
		return true;
	}
	return false;
}

ostream & operator <<(ostream & o, const Student & obj) {
	o << "name: " <<obj.name << " id:" << obj.id<<endl;
	return o;

}

ifstream & operator >> (ifstream & in, Student &obj)
{
	in >> obj.name >> obj.id;
	return in;
}







int main()
{
	///1 to 4
	/*
	Student s1("irfan",10), s2("asdd",15), s3("qwer",3);
	vector<Student>std_vec;
	std_vec.push_back(s1);
	std_vec.push_back(s2);
	std_vec.push_back(s3);


	ostream_iterator<Student> o(cout);

	*/

	Student obj;
	vector<Student>std_vec;

	ifstream input_file;
	input_file.open(("in.txt"));
	if (!input_file)
	{
		cout << "file not found";
	}
	while (input_file >> obj)
	{
		
		
		std_vec.push_back(obj);
	}

	cout << "after read\n";

	ostream_iterator<Student> o(cout);
	copy(std_vec.begin(), std_vec.end(), o);
	
	/*
	for (int i = 0;i < std_vec.size();i++)
	{
		cout << std_vec[i] << endl;
	}
	*/
	
	cout << "before sort\n";
	sort(std_vec.begin(), std_vec.end());

	cout << "sorted" << endl;
	copy(std_vec.begin(), std_vec.end(), o);

	ofstream out("out.txt");
	ostream_iterator<Student> of(out);
	copy(std_vec.begin(), std_vec.end(), of);
	//unique_copy()
	cout << "after write\n";
	
	



    return 0;
}

