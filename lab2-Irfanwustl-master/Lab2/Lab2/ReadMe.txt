Name: Irfan Alahi
Lab:2

General Note: I have included blue as a valid color with other suggested colors of the assignment document.

Error:
1. I got an error as I did not include stdfax.h in every source file. I have included the header file in every source file and run successfully.

Test Cases:
1. I have tested two provided input files(gomoku.txt and tic-tac-toe.txt). The outputs are correct.
2. I have tested without dimension and my program exits with the message "cannot read the dimension".
3. A test was designed with some lines above the dimension line and my program goes through all those lines and finally read the dimension successfully.
4. In one test case, the game pieces were separated from the dimension line by newlines. However my program correctly read the game pieces.
5. In the dimension line, some extra words are inserted. My program correctly ignores them.
6. An empty file is supplied as input and my program exits with the message "cannot read the dimension".
7. The program is also tested with wrong co-ordinate of the piece, for example, with negative co-ordinate and with co-ordinate greater than dimension. The program does not insert such pieces into the 
vector and successfully works with other legitimate pieces.

Extra Credit:
I have designed the Extra Credit part as follows. First the code checks whether there is a piece or not in a location of the board. If yes, it checks the adjacent
the locations. For the adjacent locations, first I check whether it is a valid location(not outside the board). For every valid location, it checks whether there is
a piece (by checking the color). If there is a a piece, it is printed according to the prescribed format. If there is no piece adjacent to a particular piece, the particular piece will be printed, but
after the colon(:) nothing will be printed indicating no adjacent piece.
Testing of extra credit: I have placed a game_piece in every position and found that my program can output the adjacent piece information correctly.