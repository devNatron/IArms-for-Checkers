#include "CheckersGame.cpp"

class AI {
    public:
        void init(int aiPlayer);
        void score(CheckersGame& game, int player);
    private:
        Move minimax(CheckersGame& game, int player, int depth);
};

void AI::score(CheckersGame& game, int player){

}

Move AI::minimax(CheckersGame& game, int player, int depth){

    std::vector<Move> moves;
    for(int i=0; i < BOARD_SIZE; i++){
        for(int j=0; j < BOARD_SIZE; j++){
            if(game.board[i][j] == player){
                game.moves(i, j);
            }
        }
    }
}