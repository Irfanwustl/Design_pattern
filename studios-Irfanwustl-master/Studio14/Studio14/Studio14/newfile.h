#pragma once

class detector {
	

public:
	unsigned int x;
	static unsigned int y;
	detector();
	~detector();
	unsigned int get_x();
};

class wrapper {
	detector *detec_obj;
	//bool flag;
	

public:
	wrapper();
	~wrapper();
	wrapper(const wrapper &obj);
	
};
