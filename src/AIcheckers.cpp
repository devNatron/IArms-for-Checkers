#include "CheckersGame.cpp"

class AI {
    public:
        void init(int player);
        void performMove(CheckersGame& game);
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

void AI::performMove(CheckersGame& game){
    Move bestMove = minimax(game, _AI, 0);
    game.setState(bestMove, _AI);
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
        return ( game.getPieces(_AI) - game.getPieces(_HUMAN) );
    }

    std::vector<Move> moves;
    for(int i=0; i < BOARD_SIZE; i++){
        for(int j=0; j < BOARD_SIZE; j++){
            if(game.board[i][j] == player){
                moves = game.getValidMoves(j, i, player);
                for(int k = 0; k < moves.size(); k++){
                    CheckersGame possibleState = game.getNewState(moves[k], player);
                    if(player == _AI){
                        moves[k].score = minimax(possibleState, _HUMAN, depth).score;
                    }
                    else
                        moves[k].score = minimax(possibleState, _AI, depth).score;
                }
            }
        }
    }

    int bestMove = 0;
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

    return moves[bestMove];
}