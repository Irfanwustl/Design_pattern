#pragma once

#include "GamePieces.h"
#include "Common.h"

//enum for exclusively class Tic_Tac_Toe
enum class Tic_enaum
{
	 X_turn,Y_turn, bad_input, user_quit, prompt_success, turn_success,
};


//Implements Tic_Tac_Toe. It takes input and run the whole game. 
class Tic_Tac_Toe {
	const unsigned int width = 5, height = 5,total_move=9;
	unsigned int num_moves;
	Tic_enaum whoseturn;
	string winner;
	vector<vector<int>>xMoves, yMoves;

	vector<vector<game_piece>> fullboard; // outer is empty piece
	const string empty_display = " ";
	const string playerXdisplay = "X";
	const string playerYdisplay = "O";

	friend ostream &operator <<(ostream &out, const Tic_Tac_Toe &t);
public:
	Tic_Tac_Toe(); 
	bool done();
	bool draw();
	Tic_enaum prompt(unsigned int &x, unsigned int &y);
	Tic_enaum turn(); 
	int play(); 
	
};

///friend to class Tic_Tac_Toe
ostream &operator <<(ostream &out, const Tic_Tac_Toe &t);