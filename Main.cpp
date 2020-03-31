#include "AIcheckers.cpp"
#include "stdio.h"
#define ROBSON 1

int main(){
    CheckersGame game;
    int win = 0, opcao = 0;
    game.print();

    AI robson;
    AI hudson;

    cout << "Qual o modo de jogo?" << endl;
    cout << "(digite 1 para jogar contra a IA, 2 para ver 2 IAs jogando e 3 ou 4 para testes)";
    cin >> opcao;

    if (opcao == 1) { // humano vs CPU
        while(true){
            robson.init(ROBSON);

            printf("Vez do Robson: \n");
            win = robson.performMove(game);
            game.print();

            if(game.getPieces(ROBSON) == 0){
                cout << "Robson perdeu!" << endl;
                break;
            }

            if(win == 1){
                printf("Robson WIN!!!!\n");
                break;
            }
            else if(win == -1){
                printf("Empate!!!!\n");
                break;
            }

            getchar();
            // game.print();

            // jogada da pessoa

            // getchar();

            // game.setState(bestMove, _AI);
        }
    }
    else if (opcao == 2) {
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
    else if (opcao == 3) {
        cout << "embreve";
    } 
    else if (opcao == 4) {
        cout << "embreve";
    }
    else {
        cout << "voce digitou uma opcao invalida";
    }
}