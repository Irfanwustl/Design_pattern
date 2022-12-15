#pragma once
#include<map>
#include<string>

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

class calculator {
	int result_so_far;
	std::map<char, calculatable*>cal_obj_map;
	int calculate(char, int, int);
public:
	void addOperation(char , calculatable *);
	
	int calculate(std::string str);

};