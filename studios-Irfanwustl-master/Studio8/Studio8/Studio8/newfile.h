#pragma once


///q 2,3
/*
struct mystruct {
private:
	int a, b;
	mystruct();
};
*/

/*
class mystruct {
public:
	int a, b;
	mystruct();
};
*/

//q4-7

class mystruct {

	int a, b;
public:
	mystruct();
	mystruct(mystruct & const);
	int get_a() const;
	int get_b() const;
	mystruct & set_a(int n);
	mystruct & set_b(int n);
};


//q8
/*
class mystruct {

	int a, b;
	mystruct();
public:
	
	mystruct(mystruct & const);
	int get_a() const;
	int get_b() const;
	mystruct & set_a(int n);
	mystruct & set_b(int n);
};
*/
