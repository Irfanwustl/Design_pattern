#pragma once
#include<map>
#include<string>
#include <sstream>

class calculatable
{
public:
	virtual int calculate(int, int) = 0;



};


class addable :public  calculatable {
	virtual int calculate(int a, int b);
};

class subtractable :public  calculatable {
	virtual int calculate(int a, int b);
};

class multipliable :public  calculatable {
	virtual int calculate(int a, int b);
};


class dividable :public  calculatable {
	virtual int calculate(int a, int b);
};

class mod :public  calculatable {
	virtual int calculate(int a, int b);
};




class parseStrategy {
public:
	virtual std::string parse(std::string) = 0;
};
class infixparseStrategy :public parseStrategy {
public:
	virtual std::string parse(std::string);
};

class prefixparseStrategy :public parseStrategy {
	void parseHelper(std::istringstream &, std::ostringstream &);
public:
	
	virtual std::string parse(std::string);
};

class calculator {
	parseStrategy *ps;
	int result_so_far;
	std::map<char, calculatable*>cal_obj_map;
	calculator();
	~calculator();
	friend class builder_class;
	friend class builder_concrete;
public:
	void addOperation(char, calculatable *);
	int calculate(char, int, int);
	int calculate(std::string);
	void setParser(parseStrategy*);

};


class builder_class {
protected:
	calculator *calp;
public:
	virtual int buildCalculator() = 0;
	virtual calculator * getResult() = 0;
	virtual void buildParser(std::string type) = 0;
	virtual void buildOperation(char o) = 0;
	void deleteCalculator();


};

class builder_concrete :public builder_class {
public:
	virtual int buildCalculator();
	virtual calculator * getResult();
	virtual void buildParser(std::string type);
	virtual void buildOperation(char o);
};