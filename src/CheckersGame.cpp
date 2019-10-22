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
	Move(){}
	Move(int Score) : score(Score){}
    int j;
    int i;
	int oldJ;
    int oldI;
	int capJ; //block after capture
    int capI; //block after block
    int score;
};

class CheckersGame
{
	public:
		int board[BOARD_SIZE][BOARD_SIZE];
		int piecesP1;
		int piecesP2;

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
			piecesP1 = 12;
			piecesP2 = 12;
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

		std::vector<Move> getValidMoves(int j, int i, int player){
			std::vector<Move> moves;
			int direction; int enemy;
			int LeftX, RightX, fwdY, bwdY;
			int Left2X, Right2X, fwd2Y, bwd2Y;

			player == 1 ? enemy = 2 : enemy = 1;
			player == 1 ? direction = 1 : direction = -1;

			//moves
			LeftX = j + direction;
			RightX = j - direction;
			fwdY = i + direction;
			bwdY = i - direction;

			Left2X = j + (direction * 2);
			Right2X = j - (direction * 2);
			fwd2Y = i + (direction * 2);
			bwd2Y = i - (direction * 2);

			//forward check
			if( validPos(LeftX, fwdY) && this->board[fwdY][LeftX] == BLOCK_EMPTY){
				Move move;
				move.j = LeftX;
				move.i = fwdY;
				move.oldJ = j;
				move.oldI = i;
				moves.push_back(move);
			}
			else if( validPos(LeftX, fwdY) && validPos(Left2X, fwd2Y) && this->board[fwdY][LeftX] == enemy && this->board[fwd2Y][Left2X] == BLOCK_EMPTY){
				Move move;
				move.j = LeftX;
				move.i = fwdY;
				move.oldJ = j;
				move.oldI = i;
				move.capJ = Left2X;
				move.capI = fwd2Y;
				moves.push_back(move);
			}
			if( validPos(RightX, fwdY) && this->board[fwdY][RightX] == BLOCK_EMPTY){
				Move move;
				move.j = RightX;
				move.i = fwdY;
				move.oldJ = j;
				move.oldI = i;
				moves.push_back(move);
			}
			else if(  validPos(RightX, fwdY) && validPos(Right2X, fwd2Y) && this->board[fwdY][RightX] == enemy && this->board[fwd2Y][Right2X] == BLOCK_EMPTY){
				Move move;
				move.j = RightX;
				move.i = fwdY;
				move.oldJ = j;
				move.oldI = i;
				move.capJ = Right2X;
				move.capI = fwd2Y;
				moves.push_back(move);
			}
			
			//backward check
			if( validPos(LeftX, bwdY) && validPos(Left2X, bwd2Y) && this->board[bwdY][LeftX] == enemy && this->board[bwd2Y][Left2X] == BLOCK_EMPTY){
				Move move;
				move.j = LeftX;
				move.i = bwdY;
				move.oldJ = j;
				move.oldI = i;
				move.capJ = Left2X;
				move.capI = bwd2Y;
				moves.push_back(move);
			}
			if( validPos(RightX, bwdY) && validPos(Right2X, bwd2Y) && this->board[bwdY][RightX] == enemy && this->board[bwd2Y][Right2X] == BLOCK_EMPTY){
				Move move;
				move.j = RightX;
				move.i = bwdY;
				move.oldJ = j;
				move.oldI = i;
				move.capJ = Right2X;
				move.capI = bwd2Y;
				moves.push_back(move);
			}

			return moves;
		}

		CheckersGame getNewState(Move move, int player){
			CheckersGame newState;

			newState.copyBoard(this->board);
			newState.piecesP1 = this->piecesP1;
			newState.piecesP2 = this->piecesP2;

			int enemy;
			player == 1 ? enemy = 2 : enemy = 1;

			if(newState.board[move.i][move.j] == BLOCK_EMPTY){
				newState.board[move.i][move.j] = player;
				newState.board[move.oldI][move.oldJ] = BLOCK_EMPTY;
			}
			else if(newState.board[move.i][move.j] == enemy){
				newState.board[move.oldI][move.oldJ] = BLOCK_EMPTY;
				newState.board[move.i][move.j] = BLOCK_EMPTY;
				newState.board[move.capI][move.capJ] = player;
			}

			return newState;
		}

		int setState(Move move, int player){
			int enemy;
			player == 1 ? enemy = 2 : enemy = 1;
			if(this->board[move.i][move.j] == BLOCK_EMPTY){
				this->board[move.i][move.j] = player;
				this->board[move.oldJ][move.oldI] = BLOCK_EMPTY;
				return 0;
			}
			else if(this->board[move.i][move.j] == enemy){
				this->board[move.oldJ][move.oldI] = BLOCK_EMPTY;
				this->board[move.i][move.j] = BLOCK_EMPTY;
				this->board[move.capI][move.capJ] = player;
				return 1;
			}
		}

		bool validPos(int j, int i){
			if (j >= 0 && j <= BOARD_SIZE-1 && i >= 0 && i <= BOARD_SIZE-1)
				return true;
			else
				return false;
		}

		void copyBoard(int copyBoard[BOARD_SIZE][BOARD_SIZE]){
			for(int i=0; i<BOARD_SIZE; i++){
				for(int j=0; j<BOARD_SIZE; j++){
					this->board[i][j] = copyBoard[i][j];
				}
			}
		}

		int getPieces(int player){
			if(player == 1){
				return piecesP1;
			}
			else
				return piecesP2;
		}
};

#endif
