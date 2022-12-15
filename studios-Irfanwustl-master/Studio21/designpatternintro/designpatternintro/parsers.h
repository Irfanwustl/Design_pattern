#pragma once
#include<string>
#include<sstream>


// Strategy pattern, interface for what it means to be able to parse a string expression
class ParsingStrategy {
public:
	virtual std::string parse(std::string expr) = 0;
};

// Concrete strategies
// inFix parses an infix expression to an infix expression to be calculated by the calculator
class inFixParser : public ParsingStrategy {
	std::string convertedExpr;
public:
	virtual std::string parse(std::string expr);

};

// preFix parses a prefix expression to an infix expression to be computed by the calculator
class preFixParser : public ParsingStrategy {
	std::string convertedExpr;
public:
	virtual std::string parse(std::string);
	void parseHelper(std::istringstream & iss, std::ostringstream & s);
};