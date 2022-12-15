#pragma once


#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include <sstream>

using namespace std;


const string tic_game_name = "TicTacToe";
const string gomoku_name = "Gomoku";
enum  program_response
{
	file_parsing_success = 0,
	main_success = 0,
	play_success = 0, play_draw, play_unknownerror, user_quit,
	file_cannot_open = 1,
	wrong_argument = 2,
	memory_exception,
	cannot_read_line, readline_cannot_readdimension,
	failed_to_find_well_formed_piece, never_read_dimensoiions,
	game_piece_read_suucess, print_gameBoard_success, dimension_mismatch_while_printingBoard,
	print_adjacent_piece_successs,
};

enum  array_indices
{
	programe_index = 0,
	input_file_index = 1,
	commandLine_arg_num = 2,
};


///If the number of input is not correct, it will be called to help the user with the input format
int usage_message(char *program_name);

///convert uppercase char to lowercase
void make_lowercase(string &str);
