#include "stdafx.h"
#include "calculators.h"


using namespace std;

// Below: CalculatorBase definitions

CalculatorBase::CalculatorBase() : parser(nullptr) {
}

// template method definition
int CalculatorBase::calculate(string express) {
	string parsed;
	parsed = parser->parse(express);
	return compute(parsed); // primitive operation, defined by derived classes
}

CalculatorBase::~CalculatorBase() {
	delete parser;
}

void CalculatorBase::setParser(ParsingStrategy * p) {
	parser = p;
}


// Below: SimpleCalculator definitions

void SimpleCalculator::addOperation(char c) {
	calculatable * o = nullptr;
	if (c == '+') {
		o = new addable();
	}
	else if (c == '-') {
		o = new subtractable();
	}
	else if (c == '/') {
		o = new dividable();
	}
	else if (c == '*') {
		o = new multiplyable();
	}
	operations.insert(make_pair(c, o));
}

SimpleCalculator::SimpleCalculator() : memory(0) {
}

SimpleCalculator::~SimpleCalculator() {
	auto it = operations.begin();
	while (it != operations.end()) {
		delete it->second;
	}
}

int SimpleCalculator::calculate(char operation, int one, int two) {
	auto it = operations.find(operation);
	if (it == operations.end()) {
		return -1;
	}
	else {
		return it->second->calculate(one, two);
	}
}

int SimpleCalculator::compute(string expression) {
	memory = 0;
	istringstream iss(expression);
	int operand;
	char oper;
	iss >> memory;
	while (iss >> oper >> operand) {
		memory = calculate(oper, memory, operand);
	}
	return memory;
}



// Below: PrecedenceCalculator definitions

PrecedenceCalculator::PrecedenceCalculator() : compUnit(nullptr) {}

PrecedenceCalculator::~PrecedenceCalculator() {
	delete compUnit;
}

// TODO: define this
void PrecedenceCalculator::addOperation(char c) {
	ChainedCalculatable *cc = new ChainedCalculatable();

	calculatable * o = nullptr;
	if (c == '+') {
		o = new addable();
	}
	else if (c == '-') {
		o = new subtractable();
	}
	else if (c == '/') {
		o = new dividable();
	}
	else if (c == '*') {
		o = new multiplyable();
	}
	cc->setOperation(c,o);
	if (compUnit == nullptr)
	{
		compUnit = cc;
	}
	else {

		
		ChainedCalculatable *temp= compUnit;
		while (temp->getSucc() != nullptr)
		{
			
			temp = temp->getSucc();
		}
		temp->setSuccessor(cc);

	}
}

// TODO: Define this
int PrecedenceCalculator::compute(string parsedExpression) {
	string out=compUnit->calculate(parsedExpression);
	int result = stoi(out);
	return result;
}