// create_des_pattern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"Newfile.h"
#include<string>
#include <sstream>
#include<iostream>


using namespace std;

int main()
{
	//1to4
	/*
	while(1){
	builder_concrete bc;
	bc.buildCalculator();

	string parstype;
	cout << "Parsing type:";
	cin >> parstype;
	bc.buildParser(parstype);
	cout << "Enter list of operations(dint put space, press q to quit):";
	

	char opc;
	while(1) {
		cin >> opc;
		if (opc == 'q')break;
		cout << "opt=" << opc << endl;
		bc.buildOperation(opc);
	} 
	calculator *calobj = bc.getResult();

	string str,vua;
	cout << parstype<<" input:";
	getline(cin, vua);
	getline(cin, str);
	cout << parstype<<" result=" << calobj->calculate(str) << endl;

	}
	*/
	builder_concrete bc;
	int build_result;
	build_result=bc.buildCalculator();
	cout << "1st build_result=" << build_result << endl;
	build_result = bc.buildCalculator();
	cout << "2nd build_result=" << build_result << endl;

	while(1){
	string parstype;
	cout << "Parsing type:";
	cin >> parstype;
	bc.buildParser(parstype);
	cout << "Enter list of operations(dint put space, press q to quit):";


	char opc;
	while (1) {
		cin >> opc;
		if (opc == 'q')break;
		cout << "opt=" << opc << endl;
		bc.buildOperation(opc);
	}
	calculator *calobj = bc.getResult();

	string str, vua;
	cout << parstype << " input:";
	getline(cin, vua);
	getline(cin, str);
	cout << parstype << " result=" << calobj->calculate(str) << endl;
	cout << parstype << " input:";
	//getline(cin, vua);
	getline(cin, str);
	cout << parstype << " result=" << calobj->calculate(str) << endl;

	bc.deleteCalculator();

	build_result = bc.buildCalculator();
	cout << "Again build_result=" << build_result << endl;
	}


	
	


    return 0;
}

