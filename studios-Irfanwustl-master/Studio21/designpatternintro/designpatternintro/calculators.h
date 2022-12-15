#pragma once
#include "calculatable.h"
#include "parsers.h"


class ParsingStrategy; // forward declaration

					   // abstract base class representing a calculator, acts as the AbstractClass participant in the Template Method pattern
class CalculatorBase {
public:
	// factory methods for operator construction, each concrete calculator class deriving from CalculatorBase will create its own operators
	virtual void addOperation(char c) = 0;

	// primitive operation, defined by derived classes to specify how a particular operation in the template method behaves
	virtual int compute(std::string) = 0;

	void setParser(ParsingStrategy * p);

	// the template method
	int calculate(std::string expression);
protected:
	ParsingStrategy * parser;
	CalculatorBase();
	~CalculatorBase();
};

// A simple calculator class, processes expressions as we did in previous studios
class SimpleCalculator : public CalculatorBase {
protected:
	int calculate(char operation, int one, int two);
	std::map<char, calculatable *> operations;
	int memory;
public:
	SimpleCalculator();
	~SimpleCalculator();
	// primitive operation the calculator defines for the Template Method pattern
	virtual int compute(std::string);
	// factory method for creating operators, creates calculatable objects
	virtual void addOperation(char c);
};

// A more complex calculator class which parses a string expression by obeying some operator precedence
class PrecedenceCalculator : public CalculatorBase {
protected:
	// start of the Chain of Responsibility chain
	ChainedCalculatable * compUnit;
public:
	PrecedenceCalculator();
	~PrecedenceCalculator();
	// primitive operation, defined as part of the tempate method pattern
	virtual int compute(std::string);
	// factory method, creates ChainedCalculatable objects
	virtual void addOperation(char c);
};