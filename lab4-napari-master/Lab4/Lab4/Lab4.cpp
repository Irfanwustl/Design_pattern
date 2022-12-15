// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TicGame.h"

#include<memory>


int main(int argc, char *argv[])
{
	
	GameBase *obj=0;
	try {
		obj= GameBase::gameObjectSelector(argc, argv);

		
	}
	catch (exception e) {
		cout << "memory exception"<<endl;
		
	}
	

	

	if (obj == 0) {
		

		return usage_message(argv[programe_index]);
	}
	shared_ptr<GameBase> shr_ptr(obj);

	return obj->play();


}
