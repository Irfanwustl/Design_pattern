
#include "stdafx.h"
#include "TicGame.h"
#include <cmath>
#include <stdlib.h>

using namespace std;



GameBase::GameBase(const unsigned int width, const unsigned int height): width(width),height(height){}

GameBase* GameBase::gameObjectSelector(int argc, char *argv[]) {
	
	GameBase* result_pointer = 0;
	
	if (argc >= commandLine_arg_num && argv[input_file_index] == gomoku_name)
	{
		if (argc == 3)
		{
			int dim = atoi(argv[2]);
		
			try {
				if (dim >= 5) {
					result_pointer = new GomokuGame(dim, dim, 5);
				}
				else if (dim>=3){
					result_pointer = new GomokuGame(dim, dim, dim);
				}
				else {
					cout << "Please enter valid number\n";
				}
				
				
			}
			catch (exception e) {
				throw e;
			}
		}
		else if (argc == 4)
		{
			int dim = atoi(argv[2]);
			int nedtowin= atoi(argv[3]);

			
			if (dim>=3 && nedtowin>=3){
				try {
					result_pointer = new GomokuGame(dim, dim, nedtowin);
				}
				catch (exception e) {
					throw e;
				}
			}
			else {
				cout << "Please enter valid number\n";
			}
		}
		else if (argc == 2)
		{
			try {
				result_pointer = new GomokuGame();
			}
			catch (exception e) {
				throw e;
			}
		}
		else {

			return result_pointer;
		}
		
	}

	else if (argc != commandLine_arg_num)
	{


		return result_pointer;
	}
	else if (argv[input_file_index] == tic_game_name)
	{
		try {
			result_pointer = new Tic_Tac_Toe();
		}
		catch (exception e) {
			throw e;
		}
		
	}
	

	
	return result_pointer;

}




Tic_Tac_Toe::Tic_Tac_Toe() : GameBase(5,5),total_move(9), empty_display(" "), playerXdisplay("X"), playerYdisplay("O") { 
	whoseturn = Tic_enaum::X_turn;
	num_moves = 0;

	struct game_piece empty_piece;
	empty_piece.colour = piece_color::no_color;
	empty_piece.how_displayed = empty_display;
	empty_piece.name_of_piece = "";
	for (unsigned int i = 0;i < width;i++) {
		vector<game_piece>temp;
		for (unsigned int j = 0;j < height;j++) {
			
			
			temp.push_back(empty_piece);
			
			
		}
		fullboard.push_back(temp);

	}
	if (playerXdisplay.length() >= playerYdisplay.length()) {
		highest_displayed_string_length = playerXdisplay.length();
	}
	else
	{
		highest_displayed_string_length = playerYdisplay.length();
	}
}




ostream & operator<<(ostream &out, const  Tic_Tac_Toe &t) {
	
	

	size_t displayed_length = t.highest_displayed_string_length ;



	for (unsigned int y = t.height - 1;;y--)
	{

		out << y;

		for (unsigned int x = 0;x < t.width;x++)
		{

			out.width(displayed_length);
			out << t.fullboard[x][y].how_displayed<<" ";
		}
		out << endl;
		if (y == 0) {
			out << " ";
			for (unsigned int x = 0;x < t.width;x++)
			{

				out.width(displayed_length);

				out << x<<" ";

			}
			out << endl;
			break;
		}
	}
	return out;
}



bool Tic_Tac_Toe::done() {
	bool result=false;
	string winningplayer;
	//horizontal win
	for (int i = 1;i <= 3;i++) {
		
			if (fullboard[i][1].how_displayed == fullboard[i][2].how_displayed && fullboard[i][2].how_displayed == fullboard[i][3].how_displayed){
				if (fullboard[i][1].how_displayed != empty_display) {
					

					winningplayer = fullboard[i][1].how_displayed;
					result= true;
				}
				
		}
		
	}

	//vertical check
	for (int i = 1;i <= 3;i++) {

		if (fullboard[1][i].how_displayed == fullboard[2][i].how_displayed && fullboard[2][i].how_displayed == fullboard[3][i].how_displayed) {
			if (fullboard[1][i].how_displayed != empty_display) {
				

				winningplayer = fullboard[1][i].how_displayed;
				result= true;
			}
			
		}

	}

	///diagonal win
	if (fullboard[1][1].how_displayed == fullboard[2][2].how_displayed && fullboard[2][2].how_displayed == fullboard[3][3].how_displayed) {
		if (fullboard[1][1].how_displayed != empty_display) {
			
			
			winningplayer = fullboard[1][1].how_displayed;
			result= true;
		}
		
	}
	if (fullboard[3][1].how_displayed == fullboard[2][2].how_displayed && fullboard[2][2].how_displayed == fullboard[1][3].how_displayed) {
		if (fullboard[3][1].how_displayed != empty_display) {
			
			
			winningplayer = fullboard[3][1].how_displayed;
			result= true;
		}
		
	}

	if (result) {
		winner = winningplayer;
	}
	return result;

}
bool Tic_Tac_Toe::draw() {
	if (done())return false;
	
	if (num_moves >= total_move)return true;

	return false;
}

///parse the comma seperated input. 
Tic_enaum GameBase::prompt(unsigned int &x, unsigned int& y) {
	
	string userInput;
	cout << "Enter your move or quit:";
	getline(cin, userInput);


	while (userInput.find("  ") != userInput.npos) { //got the idea from www.cplusplus.com
		userInput.replace(userInput.find("  "), 2, " ");
	}

	if (userInput.find("quit") != userInput.npos )
	{
		
		return Tic_enaum::user_quit;
	}

	if (userInput.find(",") == userInput.npos)return Tic_enaum::bad_input;

	userInput.replace(userInput.find(","),1," ");

	
	
	istringstream iss(userInput);

	while (!(iss>>x))
	{
		
		
		if (iss.eof()) {
			
			return Tic_enaum::bad_input;
			break;
		}
		

		iss.clear();
		char temp;
		iss >> temp;				
	}

	while (!(iss >> y))
	{
		
		if (iss.eof()) {
			
			return Tic_enaum::bad_input;
			break;
		}
		iss.clear();
		char temp;
		iss >> temp;
		
		
	}

	
	
	return Tic_enaum::prompt_success;

}


///maintains turn and checks whether the input is in the board
Tic_enaum Tic_Tac_Toe::turn() {
	string player;
	
		
		if (whoseturn == Tic_enaum::X_turn) {
			player = playerXdisplay;
			whoseturn = Tic_enaum::Y_turn;
		}
		else {
			player = playerYdisplay;
			whoseturn= Tic_enaum::X_turn;
		}
		cout <<"player "<<player << endl;

		unsigned int x, y;
		for (;;) {
			Tic_enaum prompt_return = prompt(x, y);
			if (prompt_return == Tic_enaum::bad_input) {
				cout << "Please insert both x and y coordinate\n";
			}
			else if (prompt_return==Tic_enaum::user_quit)
			{
				return prompt_return;
			}
			else if (x >= width-1 || y >= height-1 || x<=0 || y<=0) {
				cout << "You have inserted position outside of the Board.\n";
			}
			else if (this->fullboard[x][y].how_displayed != empty_display) {
				cout << "The place is already occupied.\n";
			}
			else {
				break;
			}
		}
		
		
		vector <int> coord;
		
		coord.push_back(x);
		coord.push_back(y);

		if (player == playerXdisplay) {
			
			this->fullboard[x][y].how_displayed = playerXdisplay;
			
			xMoves.push_back(coord);
		}

		else {
			
			this->fullboard[x][y].how_displayed = playerYdisplay;
			yMoves.push_back(coord);
		}
		
		cout << *this;


		
		cout << endl;
		if (player == playerXdisplay) {
			cout << "Player " << player << ": ";
			for (size_t  i = 0;i < xMoves.size();i++) {
				if (i > 0) {
					cout << "; ";
				}
				cout << xMoves[i][0] << ", " << xMoves[i][1];
			}
		}
		else {
			cout << "Player " << player << ": ";
			for (size_t i = 0;i < yMoves.size();i++) {
				if (i > 0) {
					cout << "; ";
				}
				cout << yMoves[i][0] << ", " << yMoves[i][1];
			}
		}
		cout << endl<<endl;
	
	



	return Tic_enaum::turn_success;
}

/// executes the whole game
int  GameBase::play() {
	
	
	print();
	while(1) {
		Tic_enaum turn_response= turn();

		if (turn_response == Tic_enaum::user_quit) {
			cout << "Number of played moves=" << num_moves<<", user quits\n";
			return user_quit;

		}
		num_moves++;
		
		bool isDone=done();
		if (isDone) {
			cout << winner << " won!!!" << endl;
			return play_success;
		}
		bool isDraw = draw();
		if (isDraw) {
			cout << "Number of played moves=" << num_moves << ". A draw!!!\n";
			return play_draw;
		}
		
	}
	return play_unknownerror;
}



void Tic_Tac_Toe::print() {
	cout << *this;
}





GomokuGame::GomokuGame():GameBase(19,19),empty_display(" "), playerBdisplay("B"), playerWdisplay("W") {
	this->needed_to_win = 5;
	initialize_independentpart();
}
GomokuGame::GomokuGame(unsigned int weidth, unsigned int height, int needed_to_win):GameBase(weidth,height),empty_display(" "), playerBdisplay("B"), playerWdisplay("W") {
	this->needed_to_win = needed_to_win;
	initialize_independentpart();
}

///maintains turn and checks whether the input is in the board
Tic_enaum  GomokuGame::turn() {
	string player;


	if (whoseturn == Tic_enaum::B_turn) {
		player = playerBdisplay;
		whoseturn = Tic_enaum::W_turn;
	}
	else {
		player = playerWdisplay;
		whoseturn = Tic_enaum::B_turn;
	}
	cout << "player " << player << endl;



	unsigned int x, y;
	for (;;) {
		Tic_enaum prompt_return = prompt(x, y);
		if (prompt_return == Tic_enaum::bad_input) {
			cout << "Please insert both x and y coordinate\n";
		}
		else if (prompt_return == Tic_enaum::user_quit)
		{
			return prompt_return;
		}
		else if (x >width  || y > height  || x <= 0 || y <= 0) {
			cout << "You have inserted position outside of the Board.\n";
		}
		else if (this->fullboard[x-1][y-1].how_displayed != empty_display) {
			cout << "The place is already occupied.\n";
		}
		else {
			break;
		}
	}


	vector <int> coord;

	coord.push_back(x);
	coord.push_back(y);

	if (player == playerBdisplay) {

		this->fullboard[x-1][y-1].how_displayed = playerBdisplay;

		BMoves.push_back(coord);
	}

	else {

		this->fullboard[x-1][y-1].how_displayed = playerWdisplay;
		WMoves.push_back(coord);
	}

	cout << *this;



	cout << endl;
	if (player == playerBdisplay) {
		cout << "Player " << player << ": ";

		
		for (size_t i = 0;i < BMoves.size();i++) {
			if (i > 0) {
				cout << "; ";
			}
			
			cout << BMoves[i][0] << ", " << BMoves[i][1];
		}
	}
	else {
		cout << "Player " << player << ": ";
		for (size_t i = 0;i < WMoves.size();i++) {
			if (i > 0) {
				cout << "; ";
			}
			cout << WMoves[i][0] << ", " << WMoves[i][1];
		}
	}
	cout << endl << endl;





	return Tic_enaum::turn_success;
}

void GomokuGame::print()
{
	cout << *this;
}

void GomokuGame::initialize_independentpart() {
	whoseturn = Tic_enaum::B_turn;
	num_moves = 0;

	struct game_piece empty_piece;
	empty_piece.colour = piece_color::no_color;
	empty_piece.how_displayed = empty_display;
	empty_piece.name_of_piece = "";
	for (unsigned int i = 0;i < width;i++) {
		vector<game_piece>temp;
		for (unsigned int j = 0;j < height;j++) {


			temp.push_back(empty_piece);


		}
		fullboard.push_back(temp);

	}
	if (playerBdisplay.length() >= playerWdisplay.length()) {
		highest_displayed_string_length = playerBdisplay.length();
	}
	else
	{
		highest_displayed_string_length = playerWdisplay.length();
	}
}

void put_spaces(ostream & out,unsigned int height,unsigned int this_num)
{
	string strh = to_string(height);

	int lenh = strh.length();

	string strthis = to_string(this_num);

	int lenthis = strthis.length();


	int space_count = lenh - lenthis;

	for (int i = 0;i < space_count;i++) {
		cout << " ";
	}

}


ostream & operator<<(ostream &out, const  GomokuGame &t) {

	string widstr = to_string(t.width);
	size_t widlen = widstr.length();

	size_t displayed_length;
	if (widlen >= t.highest_displayed_string_length) {
		displayed_length = widlen;
	}
	else {
		displayed_length = t.highest_displayed_string_length;
	}
		



	for (unsigned int y = t.height - 1;;y--)
	{

		out << y+1;
		put_spaces(out, t.height, y+1);

		for (unsigned int x = 0;x < t.width;x++)
		{

			out.width(displayed_length);
			out << t.fullboard[x][y].how_displayed << " ";
		}
		out << endl;
		if (y == 0) {
			out << "X";
			put_spaces(out, t.height,1);///dummy
			for (unsigned int x = 0;x < t.width;x++)
			{

				out.width(displayed_length);

				out << x+1 << " ";

			}
			out << endl;
			break;
		}
	}
	return out;
}


bool GomokuGame::done()
{



	bool result = false;


	///horizontal win
	for (size_t y = 0;y < height;y++) {
		int horseq = 1;
		for (size_t x = 0;x < width - 1;x++) {
			if (fullboard[x][y].how_displayed == fullboard[x + 1][y].how_displayed && fullboard[x][y].how_displayed != empty_display)
			{
				horseq++;
				if (horseq == needed_to_win)
				{
					winner = fullboard[x][y].how_displayed;
					return true;
				}
			}
			else
			{
				horseq = 1;
			}
		}
	}


	//vertical win
	for (size_t x = 0; x < width; x++)
	{
		int verseq = 1;
		for (size_t y = 0;y < height - 1;y++) {
			if (fullboard[x][y].how_displayed == fullboard[x][y + 1].how_displayed && fullboard[x][y].how_displayed != empty_display)
			{
				verseq++;
				if (verseq == needed_to_win)
				{
					winner = fullboard[x][y].how_displayed;
					return true;
				}
			}
			else
			{
				verseq = 1;
			}
		}
	}


	//diagonal win. left to right
	for (size_t y = 0;y < height;y++) {

		for (size_t x = 0;x < width;x++) {
			int diagseq = 1;
			for (size_t yy = y, xx = x;yy<height - 1 && xx< width - 1;yy++, xx++) {
				if (fullboard[xx][yy].how_displayed == fullboard[xx + 1][yy + 1].how_displayed && fullboard[xx][yy].how_displayed != empty_display) {
					diagseq++;
					if (diagseq == needed_to_win) {
						winner = fullboard[xx][yy].how_displayed;
						return true;
					}
				}


			}
		}
	}

	//diagonal win. right to left
	for (size_t y = 0;y < height;y++) {
		for (size_t x = width - 1;;x--) {
			int diagseq = 1;
			for (size_t yy = y, xx = x;yy < height - 1 && x>0;yy++, xx--) {
				if (fullboard[xx][yy].how_displayed == fullboard[xx - 1][yy + 1].how_displayed && fullboard[xx][yy].how_displayed != empty_display) {
					diagseq++;
					if (diagseq == needed_to_win) {
						winner = fullboard[xx][yy].how_displayed;
						return true;
					}
				}


				if (xx == 1) {
					break;
				}
			}



			if (x == 0)
			{
				break;
			}
		}
	}
	return false;
}

bool GomokuGame::horizontal_win_impossible()
{
	int remaining_Bturn, remaining_Wturn;
	const int total_turn = height*width;
	int B_total_turn = (int)ceil(total_turn / 2.0);
	int W_total_turn = (int)floor(total_turn / 2.0);

	remaining_Bturn = B_total_turn - BMoves.size();
	remaining_Wturn = W_total_turn - WMoves.size();

	

	for (size_t y = 0;y < height;y++) {
		int horseq = 0,space_seq = 0;;
		string current_piece_how_displayed;
		int piece_found = 0;
		for (size_t x = 0;x < width;x++) {
			if (fullboard[x][y].how_displayed != empty_display)
			{
				if (piece_found == 0)
				{
					horseq++;
				}
				else if (fullboard[x][y].how_displayed != current_piece_how_displayed)
				{
					horseq = 0;
					space_seq = 0;
				}
				else {
					horseq++;
				}
				piece_found = 1;
				current_piece_how_displayed = fullboard[x][y].how_displayed;
			}
			else {
				space_seq++;
			}
			if (horseq+space_seq >= needed_to_win)
			{
				
				if (piece_found == 1) {
					if (current_piece_how_displayed == playerBdisplay) {
						if (remaining_Bturn >= space_seq) {
							return false;
						}
					}
					else {
						if (remaining_Wturn >= space_seq) {
							return false;
						}
					}

				}
				else {
					if (remaining_Wturn >= space_seq)
					{
						return false;
					}

				}

			}

		}
	}
	
	return true;
}

bool GomokuGame::vertical_win_impossible() {

	int remaining_Bturn, remaining_Wturn;
	const int total_turn = height*width;
	int B_total_turn = (int)ceil(total_turn / 2.0);
	int W_total_turn = (int)floor(total_turn / 2.0);

	remaining_Bturn = B_total_turn - BMoves.size();
	remaining_Wturn = W_total_turn - WMoves.size();



	for (size_t x = 0;x < width;x++) {
		int verseq = 0, space_seq = 0;
		string current_piece_how_displayed;
		int piece_found = 0;
		for (size_t y = 0;y < height;y++) {
			if (fullboard[x][y].how_displayed != empty_display)
			{
				if (piece_found == 0)
				{
					verseq++;
				}
				else if (fullboard[x][y].how_displayed != current_piece_how_displayed)
				{
					verseq = 0;
					
					space_seq = 0;
				}
				else {
					verseq++;
				}
				piece_found = 1;
				current_piece_how_displayed = fullboard[x][y].how_displayed;
				
			}
			else {
				space_seq++;
			}
			if (verseq+space_seq >= needed_to_win)
			{
				
				if (piece_found == 1) {
					if (current_piece_how_displayed == playerBdisplay) {
						if (remaining_Bturn >= space_seq) {
							return false;
						}
					}
					else {
						if (remaining_Wturn >= space_seq) {
							return false;
						}
					}

				}
				else {
					if (remaining_Wturn >= space_seq)
					{
						return false;
					}

				}

			}

		}
	}

	
	return true;

}


bool GomokuGame::lr_diagwin_impossible() {
	int remaining_Bturn, remaining_Wturn;
	const int total_turn = height*width;
	int B_total_turn = (int)ceil(total_turn / 2.0);
	int W_total_turn = (int)floor(total_turn / 2.0);

	remaining_Bturn = B_total_turn - BMoves.size();
	remaining_Wturn = W_total_turn - WMoves.size();

	
	for (size_t y = 0;y < height;y++) {

		for (size_t x = 0;x < width;x++) {
			int diagseq = 0,space_seq=0;
			int piece_found = 0;
			string current_piece_how_displayed;
			for (size_t yy = y, xx = x;yy < height  && xx < width;yy++, xx++) {
				if (fullboard[xx][yy].how_displayed != empty_display)
				{
					if (piece_found == 0)
					{
						diagseq++;
					}
					else if (fullboard[xx][yy].how_displayed != current_piece_how_displayed)
					{
						diagseq = 0;
						space_seq = 0;
					}
					else {
						diagseq++;
						
					}
					piece_found = 1;
					current_piece_how_displayed = fullboard[xx][yy].how_displayed;
					
					
				}
				else {
					space_seq++;
				}

				
				if (diagseq+space_seq >= needed_to_win)
				{
					
					
					
					if (piece_found == 1) {
						if (current_piece_how_displayed == playerBdisplay) {
							if (remaining_Bturn >= space_seq) {
								return false;
							}
						}
						else {
							if (remaining_Wturn >= space_seq) {
								return false;
							}
						}

					}
					else {
						if (remaining_Wturn >= space_seq)
						{
							return false;
						}

					}

				}
			}
		}
	}




	return true;




}




bool GomokuGame::rl_diagwin_impossible() {
	int remaining_Bturn, remaining_Wturn;
	const int total_turn = height*width;
	int B_total_turn = (int)ceil(total_turn / 2.0);
	int W_total_turn = (int)floor(total_turn / 2.0);

	remaining_Bturn = B_total_turn - BMoves.size();
	remaining_Wturn = W_total_turn - WMoves.size();

	

	for (size_t y = 0;y < height;y++) {

		for (size_t x = width - 1;;x--) {
			int diagseq = 0, space_seq = 0;
			int piece_found = 0;
			string current_piece_how_displayed;
			for (size_t yy = y, xx = x;yy < height ;yy++, xx--) {
				if (fullboard[xx][yy].how_displayed != empty_display)
				{
					if (piece_found == 0)
					{
						diagseq++;
					}
					else if (fullboard[xx][yy].how_displayed != current_piece_how_displayed)
					{
						diagseq = 0;
						space_seq = 0;
					}
					else {
						diagseq++;

					}
					piece_found = 1;
					current_piece_how_displayed = fullboard[xx][yy].how_displayed;
					

				}
				else {
					space_seq++;
				}


				if (diagseq + space_seq >= needed_to_win)
				{
				
					if (piece_found == 1) {
						if (current_piece_how_displayed == playerBdisplay) {
							if (remaining_Bturn >= space_seq) {
								return false;
							}
						}
						else {
							if (remaining_Wturn >= space_seq) {
								return false;
							}
						}

					}
					else {
						if (remaining_Wturn >= space_seq)
						{
							return false;
						}

					}

				}
			
				if (xx == 0) {
					break;
				}
				
			}
			if (x == 0) {
				break;
			}
		}
	}

	
	return true;




}



bool GomokuGame::draw()
{
	
	///horizontal win possible? 
	bool horzwin = horizontal_win_impossible();

	//vertical win possible?
	bool vertwin= vertical_win_impossible();

	//l to r Diag win?
	bool lr_diag = lr_diagwin_impossible();

	//r to l diag win?
	bool rl_diag = rl_diagwin_impossible();
	
	
	return  (horzwin && vertwin && lr_diag && rl_diag);


	




	
}

