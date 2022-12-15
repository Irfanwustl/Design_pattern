// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TicGame.h"


int main(int argc, char *argv[])
{

	if (argc != commandLine_arg_num)
	{
		return usage_message(argv[programe_index],game_name);
	}
	else if (argv[input_file_index] != game_name)
	{
		return usage_message(argv[programe_index],game_name);
	}
	Tic_Tac_Toe t;
	return t.play();
 
}

