// Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Lab1.h"




int file_parser(vector<string> & tokens, char *file_name)
{
	ifstream input_file;
	input_file.open(file_name);
	if (!input_file)  
	{
		return file_cannot_open;
	}

	string str;
	while (input_file>>str)
	{
		tokens.push_back(str);
	}
	return file_parsing_success;
}

int usage_message(char *program_name)
{
	
	cout << "usage: " << program_name << " <filename.txt> " <<endl;
	return wrong_number_of_argument;
}

int main(int argc, char *argv[])
{
	if (argc != commandLine_arg_num)
	{
		return usage_message(argv[programe_index]);
	}
	vector<string> tokens;
	
	int file_perser_response = file_parser(tokens, argv[input_file_index]);
	
	if ( file_perser_response!= file_parsing_success)
	{
		return file_perser_response;
	}

	vector<int> numbers;
	vector<string>::iterator str_itr;
	int value;

	for (str_itr = tokens.begin();str_itr != tokens.end();str_itr++)
	{
		int flag = 0;
		for (size_t i = 0;i < (*str_itr).length();i++)
		{
			if (!isdigit((*str_itr)[i]))
			{
				flag = 1;
				break;
			}
		}

		if (flag == 0)
		{
			istringstream string_stream (*str_itr);
			string_stream>>value;
			numbers.push_back(value);
		}
		else
		{
			cout << *str_itr<<endl;
		}
		
		
	}

	
	for (size_t i = 0;i < numbers.size();i++)
	{
		cout << numbers[i] << endl;
	}
	
    return main_success;
}

