//
// Created by Gilad Bitton on 1/20/24.
//

#include "Bitton_Gilad.h"
#include <iostream>
#include <vector>
using namespace std;



class TicTacToe {
public:
    bool win;
/* Constructor*/
    TicTacToe(){
/* Initialize defaults here */
        win = false;
    }
/* This is your game board*/
    vector<vector<char>> gameBoard
            {
                    {'1', '2', '3'},
                    {'4', '5', '6'},
                    {'7', '8', '9'}
            };
/* This prints your game board*/
    void printGameBoard()
    {
        for (int i = 0; i < gameBoard.size(); i++)
        {
            for (int j = 0; j < gameBoard[i].size(); j++)
            {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }
/* This method modifes the game board*/
    void modifyGameBoard(char player, int position)
    {
/*write code to modify the game board here*/
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(gameBoard[i][j] - '0' == position) {
                    gameBoard[i][j] = player;
                }
            }
        }
    }

    void checkWin(char player, int position) {
        position -=1;
        int i = position / 3;
        int j = position % 3;
        if(gameBoard[i][0] == player && gameBoard[i][1] == player && gameBoard[i][2] == player) {
            win = true;
        } else if(gameBoard[0][j] == player && gameBoard[1][j] == player && gameBoard[2][j] == player) {
            win = true;
        } else if(gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2] == player) {
            win = true;
        } else if(gameBoard[0][2] == player && gameBoard[1][1] == player && gameBoard[2][0] == player) {
            win = true;
        }
    }
    bool getWin(){return win;}
    vector<vector<char>> getGameboard(){return gameBoard;}
    void setWin(bool x) {win = x;}
};

int main() {
    TicTacToe game;
    int n = 0;
    int player = 0;
    while(!(game.getWin())) {
        game.printGameBoard();
        char p = 'X';
        if(player%2 != 0) {
            p = 'O';
        }
        cout << "player " << p << " choose a location" << endl;
        cin >> n;
        game.modifyGameBoard(p, n);
        player +=1;
        game.checkWin(p, n);
        if(game.getWin()) {
            game.printGameBoard();
            cout << "player " <<p << " won" << endl;
        } if(player >= 9) {
            game.printGameBoard();
            cout << "the game was a tie" << endl;
            break;
        }
    }

    return 0;
}
