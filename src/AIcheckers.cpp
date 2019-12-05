#include "CheckersGame.cpp"
#include <stdlib.h>
#include <time.h>

class AI {
    public:
        void init(int player);
        int performMove(CheckersGame& game);
    private:
        Move minimax(CheckersGame& game, int player, int depth);
        int _AI;
        int _HUMAN;
};

void AI::init(int aiPlayer){
    _AI = aiPlayer;
    if(_AI == BLOCK_P1){
        _HUMAN = BLOCK_P2;
    }
    else
        _HUMAN = BLOCK_P1;  
    
}

int AI::performMove(CheckersGame& game){
    Move bestMove = minimax(game, _AI, 0);
    if(bestMove.score == 777){
        return -1;
    }
    else{
        game.setState(bestMove, _AI);
        if(game.getPieces(_HUMAN) == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
}

Move AI::minimax(CheckersGame& game, int player, int depth){
    
    //check AI victory
    if(game.getPieces(_HUMAN) == 0){
        return Move(100);
    }//check Player victory
    else if(game.getPieces(_AI) == 0){
        return Move(-100);
    }
    else if(depth == 3){
        return Move( (game.getPieces(_AI) - game.getPieces(_HUMAN)) );
    }
    depth++;

    std::vector<Move> moves;
    CheckersGame possibleState;
    for(int i=0; i < BOARD_SIZE; i++){
        for(int j=0; j < BOARD_SIZE; j++){
            if(game.board[i][j] == player){
                std::vector<Move> validMoves = game.getValidMoves(j, i, player);
                for(int k = 0; k < validMoves.size(); k++){
                    possibleState = game.getNewState(validMoves[k], player);
                    //possibleState.print();
                    if(player == _AI){
                        validMoves[k].score = minimax(possibleState, _HUMAN, depth).score;
                    }
                    else{
                        validMoves[k].score = minimax(possibleState, _AI, depth).score;
                    }
                    moves.push_back(validMoves[k]);
                }
            }
        }
    }
    /* for(int k = 0; k < moves.size(); k++){
        std::cout << "s:" << moves[k].score << " i:" << moves[k].i << " j:" << moves[k].j << " p:" << player << "\n";
    } */
    if(moves.size() == 0){
        if(depth == 1)
            return Move(777);
        else
            return Move(0);
    }

    std::vector<Move> bestMoves;
    int bestMove = 0;
    
    //verifica se há jogada de captura
    int flag = 0;
    for(int i=0; i < moves.size(); i++){
        if(moves[i].capI != -1){
            flag = 1;
            break;
        }
    }
    
    //se houver, elimina todas jogadas de nao captura
    if(flag){
        for(int i=0; i < moves.size(); i++){
            if(moves[i].capI == -1){
                moves.erase(moves.begin()+i);
                i--;
            }
        }
    }

    if(player == _AI){ //AI select the best move
        int bestScore = -1000000;
        for(int i=0; i < moves.size(); i++){
            if(moves[i].score > bestScore){
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    else{ //Player select the worst move
        int bestScore = 1000000;
        for(int i=0; i < moves.size(); i++){
            if(moves[i].score < bestScore){
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }

    for(int i=0; i < moves.size(); i++){
        if(moves[i].score == moves[bestMove].score){
            bestMoves.push_back(moves[i]);
        }
    }
    srand (time(NULL));
    int sortedMove = rand() % bestMoves.size();
    return bestMoves[sortedMove];
}