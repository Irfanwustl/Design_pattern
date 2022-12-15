Lab4
Name: Irfan Alahi




Error and warning:
1. When I tried to implement step 10, I did not include the declaration of pure virtual method print() in the derived class and got an error. I thought pure virtual method did not need to include in derived
class. Then I have included the declaration in the derived class too.




Test cases with program start:

Coomand:Lab4.exe
Output:
usage: Lab4.exe <game name>
valid game_name: TicTacToe or Gomoku

Command: Lab4.exe   TicTacToe as
Output:
usage: Lab4.exe <game name>
valid game_name: TicTacToe or Gomoku

Command:Lab4.exe  asdasdfa
Output:
usage: Lab4.exe <game name>
valid game_name: TicTacToe or Gomoku


Finally, if the commandline is 
Lab3.exe TicTacToe

or 

Lab3.exe Gomoku

the game starts successfully. Moreover, as I have ipmplemented Extra credit, for Gomoku maximum 2 additional argument can be provided.



Test cases with user move:
I try to make this part as robust as I can. I have tested all the following cases for both TicTacToe and Gomoku.

If the move is comma seperated, my program can parse it. For example:
1,    2
or 
   1,   2
My program parses it as 1,2.

If there are some other characters with the integers, the program can also parse it. Example:

asd2aa,hyug1bsch

My program finds out the integers 2,1


If more than two numbers are provided first two will be taken as coordinate and the third will be ignored. Example:
1,2,3
The program considers it as 1,2

If only one integer is given the program will print a message indicating this and prompts again.

If user input position which is not inside the board, the program prints a message indicating this and prompts again.

If user do not provides comma seperated input, the program consider it bad input and prompts again.

If user inputs such a coordinate which is already occupied, the programs print a message indicating this and prompts again.

If the user quits, the programs print a message indicating this as well as how many turns are played, and returns a non zero unique value.

If the game is won, the program prints the message indicating who has won.

If the game is draw, the program prints the message indicating that this is a draw as well as how many turns are played.

Along with all the above cases, the program behaves correctly with the standard format like 1,2




In summary, I think my program can handle both valid and invalid moves.

Known Issues:
There is one known input that is not handled by my program. I have handled floating point. Please do not input something like 1.3,4. 





Extra Credit:
Design: I have written another constructor to handle the aribtrary sized Gomoku board. If no additional argument is specified, then a default constructor is called which creates 19*19
board with 5 as the number of pieces needed to win. On the other hand, if one additional argument is specified then that argument is treated as dimension and 5 is used as the number of pieces needed to win which
is handled with another constructor. Howeever, if the dimension is less than 5, then dimension itself is used as the number of pieces needed to win. If two additional arguments are supplied, first is considered as dimensiona and the second
one is considered as the number of pieces needed to win. Note that both dimension and the number of pieces needed to win(if  supplied) must be greater than
zero, otherwise my program prints a message and returns. I have tested the design with different game size and different number of pieces needed to win.


Example complete run:
Lab4.exe Gomoku 5 4
5
4
3
2
1
X1 2 3 4 5
player B

Enter your move or quit:1,1
5
4
3
2
1B
X1 2 3 4 5

Player B: 1, 1

player W
Enter your move or quit:2,2
5
4
3
2  W
1B
X1 2 3 4 5

Player W: 2, 2

player B
Enter your move or quit:1,2
5
4
3
2B W
1B
X1 2 3 4 5

Player B: 1, 1; 1, 2

player W
Enter your move or quit:3,3
5
4
3    W
2B W
1B
X1 2 3 4 5

Player W: 2, 2; 3, 3

player B
Enter your move or quit:1,3
5
4
3B   W
2B W
1B
X1 2 3 4 5

Player B: 1, 1; 1, 2; 1, 3

player W
Enter your move or quit:4,4
5
4      W
3B   W
2B W
1B
X1 2 3 4 5

Player W: 2, 2; 3, 3; 4, 4

player B
Enter your move or quit:3,4
5
4    B W
3B   W
2B W
1B
X1 2 3 4 5

Player B: 1, 1; 1, 2; 1, 3; 3, 4

player W
Enter your move or quit:5,5
5        W
4    B W
3B   W
2B W
1B
X1 2 3 4 5

Player W: 2, 2; 3, 3; 4, 4; 5, 5

W won!!!





Finally, I try to make it as robust as possible. 
If user does not give a space with in two additional arguments it will be counted
as one argument. It is also true if they are comma seperated. For example: Lab4.exe Gomoku  5,3 will be treated as one additional argument of dimension 5,
3 will be ignored.
If an user gives such an input where dimension is smaller than number of pieces needed to win, the game will start. But
after the first move it will say that it is a draw.
 