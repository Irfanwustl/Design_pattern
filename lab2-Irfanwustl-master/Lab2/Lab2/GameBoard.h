#pragma once
#include "Common.h"
#include "GamePieces.h"


///read the dimension of the board from the input file
int read_dimension(ifstream &is, unsigned int &row, unsigned int &col);

///read game pieces from the input file
int read_gamepieces(ifstream &,vector<game_piece> &, unsigned int, unsigned int);

///print the board
int print_gameBoard(const vector<game_piece>& game_pieces, unsigned int width, unsigned int height);

///print adjacenct pieces for every piece
int print_adjacency(const vector<game_piece>& game_pieces, unsigned int width, unsigned int height);
