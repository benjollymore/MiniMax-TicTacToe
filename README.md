This is a simple program that plays a game of tic tac toe between two computer players, each who employ a limited minimax algorithm for move choice. 
Player X is at an advantage to Player Y, as it can see 3 levels deep, compared to 2 level deep for Y.
This must be compiled using the -std=c++11 flag, as it employes C++11 syntax.
Program will display all states of the board leading up to the victory state or tie state, upon which it will terminate, telling the user which player won or if it were a tie.
Using the flag -s when running from the command line will suppress intermediary states and only display the first and final state alongside win/tie information.