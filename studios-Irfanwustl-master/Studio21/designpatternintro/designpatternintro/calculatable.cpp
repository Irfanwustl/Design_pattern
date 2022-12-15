
#include "stdafx.h"
#include "calculatable.h"
#include<utility>
#include<sstream>
#include<iostream>

using namespace std;

int addable::calculate(int one, int two) {
	return one + two;
}
int subtractable::calculate(int one, int two) {
	return one - two;
}
int multiplyable::calculate(int one, int two) {
	return one * two;
}
int dividable::calculate(int one, int two) {
	if (two != 0) {
		return one / two;
	}
	return 0;
}


ChainedCalculatable::ChainedCalculatable() : successor(nullptr) {}

ChainedCalculatable::~ChainedCalculatable() {
	if (successor != nullptr) {
		delete successor;
	}
}
void ChainedCalculatable::setSuccessor(ChainedCalculatable * suc) {
	successor = suc;
}
ChainedCalculatable * ChainedCalculatable::getSucc() {
	return successor;
}

void ChainedCalculatable::setOperation(char op, calculatable *o) {
	sym = op;
	operation = o;
}

char ChainedCalculatable::getSymbol() { return sym; }

string ChainedCalculatable::calculate(string expression) {
	cout << expression << endl;
	istringstream in(expression);
	ostringstream out;
	int operand1;
	char op;
	int operand2;
	in >> operand1;
	while (in >> op >> operand2) {
		if (op == getSymbol()) { // this object is responsible for handling this operation
			operand1 = operation->calculate(operand1, operand2);
			
		}
		else {
			out << " " << operand1 << " " << op;
			operand1 = operand2;
		}
	}
	out << " " << operand1;
	//out << operand1;
	
	if (successor != nullptr) { // Forward to next object in the chain
		
		return successor->calculate(out.str());
	}
	else {
		return out.str();
	}
}