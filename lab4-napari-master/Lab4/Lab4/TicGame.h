//header for TicTacToe and Gomoku




#pragma once

#include "GamePieces.h"
#include "Common.h"

//enum for exclusively class Tic_Tac_Toe and Gomoku
enum class Tic_enaum
{
	 X_turn,Y_turn, bad_input, user_quit, prompt_success, turn_success,B_turn,W_turn,
};



class GameBase {
protected:
	
	const unsigned int width, height;
	unsigned int num_moves;
	size_t highest_displayed_string_length;
	
	string winner;
	
	vector<vector<game_piece>> fullboard; // outer is empty piece

	Tic_enaum whoseturn;
	
	

public:
	GameBase(unsigned int width, unsigned int height);
	virtual void print() = 0;
	virtual bool done()=0;
	virtual bool draw()=0;
	virtual Tic_enaum prompt(unsigned int &x, unsigned int &y);
	virtual Tic_enaum turn()=0;
	int play();
	static GameBase* gameObjectSelector(int argc, char *argv[]); //step 17
};


//Implements Tic_Tac_Toe. It takes input and run the whole game. 
class Tic_Tac_Toe : public GameBase {
	const string empty_display, playerXdisplay, playerYdisplay;
	const unsigned int total_move;
	vector<vector<int>>xMoves, yMoves;
	

	

	friend ostream &operator <<(ostream &out, const Tic_Tac_Toe &t);
public:
	Tic_Tac_Toe();
	virtual bool done();
	virtual bool draw();
	
	virtual Tic_enaum turn(); 
	
	virtual void print();
	
};

///friend to class Tic_Tac_Toe
ostream &operator <<(ostream &out, const Tic_Tac_Toe &t);



class GomokuGame :public GameBase {
	const string empty_display, playerBdisplay, playerWdisplay;
	vector<vector<int>>BMoves, WMoves;
	int needed_to_win;

	//takes care of common initialization
	void initialize_independentpart();

	//check if any win possible?
	bool horizontal_win_impossible();
	bool vertical_win_impossible();
	bool lr_diagwin_impossible();
	bool rl_diagwin_impossible();
	

	friend ostream &operator <<(ostream &out, const GomokuGame &g);
public:
	//default constructor
	GomokuGame();
	//constructor for extra credit
	GomokuGame(unsigned int weidth,unsigned int height,int needed_to_win);
	virtual bool done();
	virtual bool draw();

	virtual Tic_enaum turn();

	virtual void print();
};

///friend to class Gomoku
ostream &operator <<(ostream &out, const GomokuGame &t);
