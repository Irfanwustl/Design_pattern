// Studio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<memory>
#include<vector>
#include "newfile.h"
using namespace std;


shared_ptr<detector> test(shared_ptr<detector> obp)
{
	cout << "start test" << endl;

	
	cout << "end test" << endl;
	return obp;

}



int main(int argc, char *argv[])
{
	cout << "start main" << endl;
	/*
	detector *d = new detector;

	//shared_ptr<detector>sp(d);
	shared_ptr<detector>sp1 = make_shared<detector>(*d);
	
	shared_ptr<detector>sp2 = make_shared<detector>();
	shared_ptr<detector>sp3 = make_shared<detector>();

	vector<shared_ptr<detector>>sp_vec;
	sp_vec.push_back(sp1);
	sp_vec.push_back(sp2);
	sp_vec.push_back(sp3);
	
	


	//cout << "d=== " << d << endl;
	cout << "Real Addresses: " << sp1 << " " <<  sp2 << " " << sp3 << endl;
	cout << "Adress in the vector: " << sp_vec[0] << " " << sp_vec[1] << " " << sp_vec[2] << endl;
	
	*/

	detector *p1, *p2, *p3;
	p1 = new detector;
	p2 = new detector;
	p3 = new detector;
	vector<detector *>p_vec;
	p_vec.push_back(p1);
	p_vec.push_back(p2);
	p_vec.push_back(p3);

	//cout << p1<<endl;
	//cout<<p_vec[0]<<endl;
	/*
	delete p1;
	delete p2;
	delete p3;
	*/
	
	cout << "end main" << endl;
    return 0;
	
}

