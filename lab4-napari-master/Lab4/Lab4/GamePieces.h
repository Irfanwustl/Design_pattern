#pragma once
#include "Common.h"
enum class piece_color
{
	red, black, blue, white, invalid_color, no_color,
};

///lower case color label from enum value
string lowercase_color_name(piece_color color);

/// get corresponding piece_color from color name
piece_color get_piece_color(string str);

//structure for representing Game piece
//struct game_piece;
struct game_piece {
	piece_color colour;
    string name_of_piece;
	string how_displayed;
};