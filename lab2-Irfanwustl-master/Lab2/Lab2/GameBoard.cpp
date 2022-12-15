#include "stdafx.h"
#include "GameBoard.h"
using namespace std;

int read_dimension(ifstream &is, unsigned int &row, unsigned int &col)
{
	string str;
	if(getline(is, str))
	{

	}
	else
	{
		
		return cannot_read_line;
	}
	istringstream iss(str);
	if (iss >> row && iss >> col)
	{
		return file_parsing_success;
	}
	else
	{
		
		return readline_cannot_readdimension;
	}
	
	
}

int read_gamepieces(ifstream &is, vector<game_piece> & game_pieces, unsigned int width, unsigned int height)
{
	piece_color pc;
	string str,t1,t2,t3;
	unsigned int x, y,index;
	int fl = 0;
	while (getline(is, str))
	{
		istringstream iss(str);
		if(!(iss >> t1) || !(iss >> t2) || !(iss >> t3) || !(iss >> x) || !(iss >> y))
		{
			//cout << "could not read value " << endl;
			continue;
			
		}
		
		pc = get_piece_color(t1);
		if (pc == piece_color::invalid_color)
		{
			//cout << "invalid color";
			continue;
		}
		if (x >= width || y >= height || x<0 || y<0)
		{
			//cout << "wrong dimension";
			continue;
		}
		fl = 1;

		index = width*x + y;
		game_pieces[index].colour = pc;
		game_pieces[index].name_of_piece = t2;
		game_pieces[index].how_displayed = t3;

		

		
		
	}
	if (fl == 1) 
	{
		return game_piece_read_suucess;
	}

	return failed_to_find_well_formed_piece;
}

int print_gameBoard(const vector<game_piece>& game_pieces, unsigned int width, unsigned int height)
{
	if (game_pieces.size() != width*height)
	{
		cout << "dimension mismatch, cannot print the Board" << endl;
		return dimension_mismatch_while_printingBoard;
	}

	int index;
	for (unsigned int y = height - 1;;y--)
	{
		for (unsigned int x = 0;x < width;x++)
		{
			index = width*x + y;
			cout<<game_pieces[index].how_displayed;
		}
		cout << endl;
		if (y == 0)break;
	}

	return print_gameBoard_success;
}

int print_adjacency(const vector<game_piece>& game_pieces, unsigned int width, unsigned int height)
{
	int index;
	const int helper_array_x[8] = { 1,1,-1,-1,0,0,1,-1 }, helper_array_y[8] = {1,-1,1,-1,1,-1,0,0};
	for (unsigned int y = 0; y<height;y++)
	{
		for (unsigned int x = 0;x < width;x++)
		{
			index = width*x + y;
			if (game_pieces[index].colour != piece_color::no_color && game_pieces[index].colour != piece_color::invalid_color)
			{
				cout <<x<<","<<y<<" "<< lowercase_color_name(game_pieces[index].colour)<<" "<< game_pieces[index].name_of_piece<<": ";
				int count = 0;
				for (int adj = 0;adj < 8;adj++)
				{
					int adj_x = x + helper_array_x[adj];
					int adj_y = y + helper_array_y[adj];
					if (adj_x<0 || adj_y<0 || (unsigned)adj_x>=width || (unsigned)adj_y>=height)
					{
						continue;
					}
					int adj_index = width*adj_x + adj_y;
					if (game_pieces[adj_index].colour ==piece_color::no_color || game_pieces[adj_index].colour == piece_color::invalid_color)continue;
					if (count > 0)cout << "; ";
					cout << adj_x << "," << adj_y << " " << lowercase_color_name(game_pieces[adj_index].colour) << " " << game_pieces[adj_index].name_of_piece;
					count++;
					
				}
				cout << endl;
				
			}
			
		}
		
		
	}

	return print_adjacent_piece_successs;
}