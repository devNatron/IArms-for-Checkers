#include "AIcheckers.cpp"
#include "stdio.h"

int main(){
    CheckersGame game;
    int win = 0;
    game.print();

    AI robson;
    AI hudson;
    hudson.init(1);
    robson.init(2);

    while(true){
        printf("robson: \n");
        win = robson.performMove(game);
        game.print();

        if(win == 1){
            printf("robson WIN!!!!\n");
            break;
        }
        else if(win == -1){
            printf("EMPATE!!!!\n");
            break;
        }

        getchar();

        printf("hudson: \n");
        win = hudson.performMove(game);
        game.print();

        if(win == 1){
            printf("hudson WIN!!!!\n");
            break;
        }
        else if(win == -1){
            printf("EMPATE!!!!\n");
            break;
        }
        getchar();
    }


}