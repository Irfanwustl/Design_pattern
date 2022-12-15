Lab 3
Name: Irfan Alahi

Error and warning: Fortunately I did not get any errors. I got one warning in several places when try to compare an signed int variable with size of a vector which is unsigned.
I have changed the int variable to i=unsigned typee and the warning is gone.

In my design player X starts first.

Test cases with program start:
If the input number, argc, is not equal to 2 the program calls the usage function and usage function prints how to run the program\. Example:
Commandline:Lab3.exe
Output:usage: Lab3.exe TicTacToe
Commandline:Lab3.exe TicTacToe sdfsdf
Output:usage: Lab3.exe TicTacToe

If any string other than TicTacToe is provided, program calls the usage function. Example:
Commandline:Lab3.exe bhjvdsg
Output:usage: Lab3.exe TicTacToe

Finally, if the commandline is 
Lab3.exe TicTacToe
the game will start successfully.


Test cases with user move:
I try to make this part as robust as I can. I have tested all the following cases.

If the move is comma seperated, my program can parse it. For example:
1,    2
or 
   1,   2
My program pares it as 1,2.

If there are some other characters with the integers, the program can also parse it. Example:

asd2aa,hyug1bsch

My program finds out the integers 1,2.
If floating points are given, my program cast it to int. Example:

1.2,3

It will be 1,3.

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




 