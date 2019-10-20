#include <string>
#include <iostream>
#include <vector>

#ifndef CHECKERS_GAME_CPP
#define CHECKERS_GAME_CPP

#define BLOCK_EMPTY 0
#define BLOCK_P1 1
#define BLOCK_P2 2
#define BOARD_SIZE 8

using namespace std;

struct Move{
    int x;
    int y;
    int score;
};

class CheckersGame
{
	public:
		int board[BOARD_SIZE][BOARD_SIZE];
		
		//Create a new game
		CheckersGame()
		{
			int i, j;
			for(i = 0; i < BOARD_SIZE; i++)
			{
				for(j = 0; j < BOARD_SIZE; j++)
				{
					this -> board[i][j] = 0;
				}
			}
		}

		//Print game board to cout
		void print()
		{
			int i, j;

			cout << "[";
			for(i = 0; i < BOARD_SIZE; i++)
			{
				for(j = 0; j < BOARD_SIZE; j++)
				{
					cout << this->board[i][j] << ", ";
				}

				if(i == (BOARD_SIZE - 1) )
				{
					cout << "]";
				}
				else
				{
					cout << "\n";
				}
			}
			cout << endl;
		}

		/* std::vector<Move> getValidMoves(int x, int y, int player){
			std::vector<Move> moves;
			int direction;
			int fwdLeftX, fwdLeftY, fwdRightX, fwdRightY;

			player == 1 ? direction = 1 : direction = -1;

			fwdLeftX = x + direction; fwdLeftY = y + direction;
			fwdRightX = x - direction; fwdRightY = y + direction;
			
			if(this.board[fwdLeftX][fwdLeftY] == BLOCK_EMPTY){
				Move move;
				move.x = fwdLeftX;
				move.y = fwdLeftY;
				move.score = 
				moves.push_back(move);
			}
			if(this.board[fwdRightX][fwdRightY] == BLOCK_EMPTY){
				Move move;
				move.x = fwdRightX;
				move.y = fwdRightY;
				moves.push_back(move);
			}
		} */
};

#endif
