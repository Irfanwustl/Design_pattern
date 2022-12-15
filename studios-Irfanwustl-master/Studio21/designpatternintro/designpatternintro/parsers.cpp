#include "stdafx.h"
#include "parsers.h"
#include<iostream>

using namespace std;

// Parser definitions
string inFixParser::parse(string exp) {
	string parsed = "";
	istringstream iss(exp);
	ostringstream oss;
	int operand;
	char oper;
	iss >> operand;
	oss << operand;
	while (iss >> oper >> operand) {
		oss << " " << oper << " " << operand;
	}
	parsed = oss.str();
	cout << parsed << endl;
	return parsed;
}

string preFixParser::parse(string exp) {
	string parsed = "";
	istringstream iss(exp);
	ostringstream oss;
	parseHelper(iss, oss);
	parsed = oss.str();
	cout << parsed << endl;
	return parsed;
}

void preFixParser::parseHelper(istringstream & iss, ostringstream &oss) {
	string value;
	if (iss >> value) {
		if (value == "+" || value == "-" || value == "/" || value == "*") {
			parseHelper(iss, oss);
			oss << " " << value;
			parseHelper(iss, oss);
		}
		else {
			istringstream iss2(value);
			int op;
			iss2 >> op;
			oss << " " << op;
		}
	}
}