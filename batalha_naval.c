#include <stdio.h>
#include "batalha.h"

void main(){
    int mapPlayer1[10][10];
    int mapPlayer2[10][10];
    int winner = 0;

    start_map(mapPlayer1);
    start_map(mapPlayer2);

    set_game(mapPlayer1);
    set_game(mapPlayer2);

    int player1life = how_many_lifes(mapPlayer1);
    int player2life = how_many_lifes(mapPlayer2);

    while(1){
        attack(mapPlayer2,&player2life,1);
        if(player2life <= 0){
            winner = 1;
            break;
        }
        attack(mapPlayer1,&player1life,2);
        if(player1life <= 0){
            winner = 2;
            break;
        }
    }

    system("clear");
    printf("Player 1\n");
    print_map_game(mapPlayer1);
    printf("Player 2\n");
    print_map_game(mapPlayer2);
    printf("\n\tFim de jogo\n\tJOGADOR %d VENCEU\n!",winner);
    
}
