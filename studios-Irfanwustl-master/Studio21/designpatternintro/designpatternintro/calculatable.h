#pragma once
#include<map>
#include<string>
#include<sstream>


// strategy pattern, declares what it means to be able to calculate something given two ints
class calculatable {
public:
	virtual int calculate(int one, int two) = 0;
};

// concrete strategies for calculating, used by the SimpleCalculator and PrecedenceCalculator(indirectly)
class addable : public calculatable {
public:
	virtual int calculate(int one, int two);
};
class multiplyable : public calculatable {
public:
	virtual int calculate(int one, int two);
};
class dividable : public calculatable {
public:
	virtual int calculate(int one, int two);
};
class subtractable : public calculatable {
public:
	virtual int calculate(int one, int two);
};



class CalculatorBase; // forward declaration for friendship below

					  // Handler class in the Chain of Responsibility pattern, declares the interface for handling requests and maintaining a successor
class ChainedCalculatable {
	friend CalculatorBase;
public:
	ChainedCalculatable();
	~ChainedCalculatable();

	// compute over the string expression, handling only operators this object is responsible for
	virtual std::string calculate(std::string);

	// mutators
	void setSuccessor(ChainedCalculatable * s);
	void setOperation(char, calculatable *);

	// accessors
	ChainedCalculatable * getSucc();
	char getSymbol();
protected:
	ChainedCalculatable * successor; // object to forward requests to in the chain
	calculatable * operation; // what operator is this object responsible for
	char sym; // symbol representing that operator
};
