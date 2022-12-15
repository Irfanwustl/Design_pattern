#include "stdafx.h"
#include "Common.h"
using namespace std;


int usage_message(char *program_name)
{

	cout << "usage: " << program_name << " <filename.txt> " << endl;
	return  wrong_number_of_argument;
}

void  make_lowercase(string &str)
{
	int capital_start = 'A', capital_end='Z', lower_start='a';
	for (string::iterator str_itr = str.begin();str_itr != str.end();str_itr++)
	{
		if (*str_itr <= capital_end && *str_itr>=capital_start)
		{
			*str_itr = *str_itr + lower_start - capital_start;
		}
	}
}