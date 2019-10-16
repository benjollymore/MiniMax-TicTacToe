/*
tictac.cpp

Ben Jollymore

2019-02-15
A simple program to allow a user to play tic tac toe between minimax computer opponents.
Run on Ubuntu 16.04 in C++11 - must compile with -std=c++11 flag
Using -s flag at command line will suppress intermediary moves 
*/

#include <iostream>
#include <stdio.h>
#define PLAYER1 'X'
#define PLAYER2 'O'

using namespace std;

//Game board empty 2d array
char board[4][4]{};

//Global bool to determine which player's turn
//true - X's turn
//false - O's turn
bool xTurn = true;

//Turn counter
int turn = 0;

//object representing coordinates for player token to be placed
struct Move{
    int row;
    int col;
};

/*
Initializes gameboard
*/
void initBoard(){
     for (int i = 1; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            board[i][j] = ' ';
            board[0][j] = (char)('0' + j);
            board[j][0] = (char)('0' + j);
        }
    }
}

/*
Prints the game board to the screen
*/
void printGrid() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << board[i][j] << "   |   ";
        }
        cout << endl << "----|-------|-------|-------|" << endl;
    }
}

/*
Checks to see if win conditions are met and consequently if the game should end.
If three-in-a-row non blank tiles found, returns 10 or -10 as a weight if the player is 1 or 2 respectively. returns 0 if no win state found
*/
int generateTree() {
    for (int i = 1; i < 4; i++) {
        //Checks rows for 3 in a row
        if (board[i][1] == board[i][2] && board[i][2] == board[i][3])
        {
            if (board[i][1] == PLAYER1) {
                return 10;
            }
            else if(board[i][1] == PLAYER2){
                return -10;
            }
        }

        //Checks columns for 3 in a row
        else if (board[1][i] == board[2][i] && board[2][i] == board[3][i])
        {
            if (board[1][i] == PLAYER1) {
                return 10;
            }
            else if(board[1][i] == PLAYER2){
                return -10;
            }
        }
    }

    //Checks right>left diagonal for 3 in a row
    if (board[1][1] == board[2][2] && board[2][2] == board[3][3])
    {
        if (board[1][1] == PLAYER1) {
            return 10;
        }
        else if(board[1][1] == PLAYER2){
            return -10;
        }
    }

    //Checks left>right diagonal for 3 in a row
    else if (board[1][3] == board[2][2] && board[2][2] == board[3][1])
    {
        if (board[1][3] == PLAYER1) {
            return 10;
        }
        else if(board[1][3] == PLAYER2){
            return -10;
        }
    }

    //no win
    return 0;
}

/*
Checks to see if win conditions are met and consequently if the game should end.
If three-in-a-row non blank tiles found, returns true.
Otherwise returns false.
*/
bool gameOver() {

    for (int i = 1; i < 4; i++) {
        //Checks rows for 3 in a row
        if (board[i][1] == board[i][2] && board[i][2] == board[i][3])
        {
            if (board[i][1] != ' ') {
                //Win/lose condition met. Game over.
                return true;
            }
        }

        //Checks columns for 3 in a row
        else if (board[1][i] == board[2][i] && board[2][i] == board[3][i])
        {
            if (board[1][i] != ' ') {
                //Win/lose condition met. Game over.
                return true;
            }
        }
    }

    //Checks diagonals for 3 in a row if middle tile occupied.

    if (board[1][1] == board[2][2] && board[2][2] == board[3][3])
    {
        //Win/lose condition met. Game over.
        if (board[1][1] != ' ') {
                //Win/lose condition met. Game over.
                return true;
            }
    }

    else if (board[1][3] == board[2][2] && board[2][2] == board[3][1])
    {
        //Win/lose condition met. Game over.
       if (board[1][3] != ' ') {
                //Win/lose condition met. Game over.
                return true;
            }
    }


    //Win/lose condition not met. Game not over.
    return false;
}

/*
Function to walk through the tree of possible moves to determine weights for each terminal node. 
*/
int minimax(int depth, bool isPlayerX) { 
    int weight = generateTree(); 
  
    //if in terminal node
    if (weight == 10 || weight == -10) 
        return weight; 

    //if player 1 is 3 levels deep or player 2 is 2 levels deep
    if (isPlayerX && depth == 3 || !isPlayerX && depth == 2){
        return weight;
    }

    //check if tie
    if (turn==10) 
        return 0; 
  
    // If player1s move
    if (isPlayerX) 
    { 
        int best = -1000; 
  
        //Walk across all nodes in tree  
        for (int i = 1; i<4; i++) 
        { 
            for (int j = 1; j<4; j++) 
            { 
                 // If empty tile  
                if (board[i][j]==' ') 
                { 
                    // Make  move 
                    board[i][j] = PLAYER1; 
  
                    // Call minimax 
                    best = max(best, minimax(depth+1, !isPlayerX) ); 
  
                    // Reset tile
                    board[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } 
  
    // If player2s move 
    else
    { 
        int best = 1000; 
  
        //Walk across all nodes in tree 
        for (int i = 1; i<4; i++) 
        { 
            for (int j = 1; j<4; j++) 
            { 
                // If empty tile 
                if (board[i][j]==' ') 
                { 
                    // Make  move 
                    board[i][j] = PLAYER2; 
  
                    // Call minimax
                    best = min(best, minimax(depth+1, !isPlayerX)); 
  
                    // Reset tile 
                    board[i][j] = ' '; 
                } 
            } 
        } 
        return best; 
    } 
}

/*
Function to return the best possible move for the player 
*/
Move getMove(bool isPlayerX) { 
    char token;
    if(isPlayerX){
        token = PLAYER1;
    }
    else{
        token = PLAYER2;
    }

    //init values for move struct to be returned
    int bestVal = -1000; 
    Move move; 
    move.row = -1; 
    move.col = -1; 
  
    // Walk through all nodes, evaluate minimax function for 
    // all empty nodes. And return the node with best outcome
    for (int i = 1; i<4; i++) 
    { 
        for (int j = 1; j<4; j++) 
        { 
            // Check if cell is empty 
            if (board[i][j]==' ') 
            { 
                // Make the move 
                board[i][j] = token; 
  
                // compute evaluation function for this 
                // move. 
                int moveVal = minimax(0, isPlayerX); 
  
                // Undo the move 
                board[i][j] = ' '; 
  
                // If the value of the current move is better than prior best,make this new best
                if (moveVal > bestVal) 
                { 
                    move.row = i; 
                    move.col = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    } 
  
    return move; 
} 

/*
Function to place the player token on the gameboard
*/
void placeToken(){

    Move move = getMove(xTurn);
    if(xTurn){
        board[move.row][move.col] = PLAYER1;
    }
    else{
        board[move.row][move.col] = PLAYER2;
    }
    xTurn = !xTurn;
    turn++;
}

/*
Main driver method.
runs the game.
*/
int main(int argc, char* argv[]) {

    //Game board value are initialized.
    initBoard();
    printGrid();
    
    //While gameOver false(win/lose conditons not met), game loops
    while (!gameOver()) {

        //If the board is full and win/lose conditions not met it is a tie and loop breaks.
        if (turn == 10 && !gameOver()) {
            cout << "It is a tie! Game over!\n\n";
            return 0;
        }
        
        //player places token in this instance of loop
        placeToken();

        //If user enters "-s" flag at command line (or anything else, really), the gameboard is not printed at every turn, just start and end
        //Makes analyzing test cases easier to sift through
        if (argv[1] == NULL){
            printGrid();
        }

    }

    //Game loop broken, final state of board printed
    printGrid();
    cout << "GAME OVER\n\n";

    //Dialouge if win conditions met after X's turn
    if (!xTurn) {
        cout << "Player X wins!\n\n";
        return 1;

    }

    //Dialouge if win conditions met after O's turn
    else {
        cout << "Player O wins!\n\n";
        return -1;
    }
}






