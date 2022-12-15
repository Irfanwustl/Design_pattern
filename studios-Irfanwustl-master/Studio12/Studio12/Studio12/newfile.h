#pragma once

class myclass {
public:
	myclass();
	virtual ~myclass();
	virtual void same();
};

class Derived :public myclass {
public:
	Derived();
	virtual ~Derived();
	virtual void same();
};