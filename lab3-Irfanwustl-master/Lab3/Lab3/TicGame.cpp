
#include "stdafx.h"
#include "TicGame.h"

using namespace std;


Tic_Tac_Toe::Tic_Tac_Toe() {
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
}




ostream & operator<<(ostream &out, const  Tic_Tac_Toe &t) {
	
	for (unsigned int y = t.height - 1;;y--)
	{
		out << y;
		for (unsigned int x = 0;x < t.width;x++)
		{
			
			out << t.fullboard[x][y].how_displayed<<" ";
		}
		out << endl;
		if (y == 0) {
			out << " ";
			for (unsigned int x = 0;x < t.width;x++)
			{
				out << x << " ";
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
Tic_enaum Tic_Tac_Toe::prompt(unsigned int &x, unsigned int& y) {
	
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
int  Tic_Tac_Toe::play() {
	
	cout << *this;
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
			cout << "Number of played moves=" << num_moves << ", no moves remaining. A draw!!!\n";
			return play_draw;
		}
		
	}
	return play_unknownerror;
}

