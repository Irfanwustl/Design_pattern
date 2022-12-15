
#include "stdafx.h"
#include "GamePieces.h"

using namespace std;

///lower case color label from enum value
string lowercase_color_name(piece_color color)
{
	string str;
	switch (color)
	{
	case piece_color::red:
		str="red";
		break;
	case piece_color::black:
		str = "black";
		break;
	case piece_color::blue:
		str = "blue";
		break;
	case piece_color::white:
		str = "white";
		break;
	case piece_color::invalid_color:
		str = "invalid_color";
		break;
	case piece_color::no_color:
		str = "no_color";
		break;
	default:
		break;
	}
	return str;
}


//check whether string contains only white spaces
bool is_only_whitespaces(string str)
{
	for (string::iterator str_itr = str.begin();str_itr != str.end();str_itr++)
	{
		if (*str_itr == ' ')
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

/// get corresponding piece_color from color name
piece_color get_piece_color(string str)
{
	piece_color pc;
	make_lowercase(str);
	if (str == "red")
	{
		pc = piece_color::red;
	}

	else if (str == "black")
	{
		pc = piece_color::black;
	}
	else if (str == "blue")
	{
		pc = piece_color::blue;
	}
	else if (str == "white")
	{
		pc = piece_color::white;
	}
	else if (is_only_whitespaces(str))
	{
		pc = piece_color::no_color;
	}
	else
	{
		pc = piece_color::invalid_color;
	}

	return pc;

}



