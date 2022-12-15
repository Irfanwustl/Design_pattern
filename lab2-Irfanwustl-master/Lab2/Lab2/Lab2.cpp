// Lab2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "Common.h"
#include "GamePieces.h"
#include "GameBoard.h"

using namespace std;



int main(int argc, char *argv[])
{
	
	if (argc != commandLine_arg_num)
	{
		return usage_message(argv[programe_index]);
	}

	ifstream input_file;
	input_file.open(argv[input_file_index]);
	if (!input_file)
	{
		cout << "File can not open" << endl;
		return file_cannot_open;
	}

	unsigned int r, c;
	while (1)
	{
		int k = read_dimension(input_file, r, c);
		if ( k== readline_cannot_readdimension)continue;
		if (k == cannot_read_line)
		{
			cout << "cannot read the dimension" << endl;
			return never_read_dimensoiions;
		}
		break;
	}

	
	vector<game_piece>game_pieces;
	struct game_piece empty_piece;
	empty_piece.colour = get_piece_color(" ");
	empty_piece.name_of_piece = "";
	empty_piece.how_displayed = " ";
	for (unsigned int i = 0;i < r*c;i++)
	{
		game_pieces.push_back(empty_piece);
	}

	if (read_gamepieces(input_file, game_pieces, r, c)== failed_to_find_well_formed_piece)
	{
		cout <<" failed_to_find_well_formed_piece" << endl;
		return failed_to_find_well_formed_piece;
	}

	int result=print_gameBoard(game_pieces, r, c);

	/////for extra credit
	print_adjacency(game_pieces, r, c);
	return result;

	

}