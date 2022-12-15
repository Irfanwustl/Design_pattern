#pragma once

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include <sstream>

using namespace std;

enum program_response
{
	file_parsing_success = 0,
	main_success=0,
	file_cannot_open = 1,
	wrong_number_of_argument = 2,
};

enum array_indices
{
	programe_index = 0,
	input_file_index = 1,
	commandLine_arg_num = 2,
};

///parse the supplied file and store the words of the file in the supplied vector
int file_parser(vector<string> & tokens, char *file_name);

///If the number of input is not correct, it will be called to help the user with the input format
int usage_message(char *program_name);