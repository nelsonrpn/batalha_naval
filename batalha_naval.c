#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/*  
    -1 = Destroço
    0 = Àgua
    1 = Corveta
    2 = Submarino
    3 = Fragata
    4 = Destroyer
    5 = Porta-Aviões
*/

void print_map_selection(int map[][10]){
    system("clear");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0;i<10;i++){
        printf("%d",i);
        for(int j = 0;j<10;j++){
            if(map[i][j] == 10) printf(" ~");
            else if(map[i][j] == -1) printf(" #");
            else if(map[i][j] == 11) printf(" C");
            else if(map[i][j] == 12) printf(" S");
            else if(map[i][j] == 13) printf(" F");
            else if(map[i][j] == 14) printf(" D");
            else if(map[i][j] == 15) printf(" P");
        }
        printf("\n");
    }
}

void print_map_game(int map[][10]){
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0;i<10;i++){
        printf("%d",i);
        for(int j = 0;j<10;j++){
            if(map[i][j] >= 10) printf(" #");
            else if(map[i][j] == 0) printf(" ~");
            else if(map[i][j] == -1) printf(" #");
            else if(map[i][j] == 1) printf(" C");
            else if(map[i][j] == 2) printf(" S");
            else if(map[i][j] == 3) printf(" F");
            else if(map[i][j] == 4) printf(" D");
            else if(map[i][j] == 5) printf(" P");
        }
        printf("\n");
    }
}

unsigned int it_fit(Ship nav,int map[][10],int x,int y){
    if(nav.dir == 'H'){
        for(int i = 0;i<nav.size;i++){
            if(map[x][y] != 10 && map[x][y] != 0) return 0;
            y++;
        }
    }
    else if(nav.dir == 'V'){
        for(int i = 0;i<nav.size;i++){
            if(map[x][y] != 10 && map[x][y] != 0) return 0;
            x++;
        }
    return 1;
    }
}

void add_ship(Ship nav, int map[][10], int x, int y){
    if(it_fit(nav,map,x,y)){
        if(nav.dir == 'H'){
            for(int i = 0;i<nav.size;i++){
                map[x][y] = nav.valCov;
                y++;
            }
        }
        else if(nav.dir == 'V'){
            for(int i = 0;i<nav.size;i++){
                map[x][y] = nav.valCov;
                x++;
            }
        }
    }
}

void input_ship(int map[][10], Ship nav){
    int y,x,check = 0;

    do{
        printf("Digite as coordenadas e direcao para posicionar a %s (%d casas) [0 0 H/V]\n",nav.name, nav.size);
        scanf("%d %d %c",&x,&y,&nav.dir);

        if(!it_fit(nav,map,x,y))
            printf("Coordenada invalida para posicionamento de Corveta!\n");
        else{
            add_ship(nav,map,x,y);
            check = 1;
        }
    }while(!check);

    print_map_selection(map);
}

//Automatizar criação do navio e liberar memoria (ED?)
void set_game(int map[][10]){

    //Define navios
    Ship corveta,submarino,fragata,destroyer,porta;

    corveta.name = (char *) malloc(sizeof(20));
    corveta.name = "Corveta";
    corveta.size = 4;
    corveta.valCov = 11;
    corveta.valUnc = 1;

    submarino.name = (char *) malloc(sizeof(20));
    submarino.name = "Submarino";
    submarino.size = 2;
    submarino.valCov = 12;
    submarino.valUnc = 2;

    fragata.name = (char *) malloc(sizeof(20));
    fragata.name = "Fragata";
    fragata.size = 3;
    fragata.valCov = 13;
    fragata.valUnc = 3;

    destroyer.name = (char *) malloc(sizeof(20));
    destroyer.name = "Destroyer";
    destroyer.size = 3;
    destroyer.valCov = 14;
    destroyer.valUnc = 4;

    porta.name = (char *) malloc(sizeof(20));
    porta.name = "Porta-Avioes";
    porta.size = 5;
    porta.valCov = 15;
    porta.valUnc = 5;
    //

    print_map_selection(map);
    input_ship(map,corveta);
    input_ship(map,submarino);
    input_ship(map,fragata);
    input_ship(map,destroyer);
    input_ship(map,porta);
}

void attack(int map[][10],int *enemyLife,int player){
    int x,y;
    system("clear");
    printf("Player %d turn\n",player);
    print_map_game(map);
    printf("Selecione as coordenadas para disparar:\n");
    scanf("%d %d",&x,&y);
    if(map[x][y] >= 10) map[x][y] -= 10;
    system("clear");

    switch(map[x][y]){
        case 0:
            printf("Acertou agua!\n");
            break;
        case 1:
            printf("Acertou Corveta inimiga!\n");
            *enemyLife -= 1;
            break;
        case 2:
            printf("Acertou Submarino inimigo!\n");
            *enemyLife -= 1;
            break;
        case 3:
            printf("Acertou Fragata inimiga!\n");
            *enemyLife -= 1;
            break;
        case 4:
            printf("Acertou Destroyer inimigo!\n");
            *enemyLife -= 1;
            break;
        case 5:
            printf("Acertou Porta-Aviões inimigo!\n");
            *enemyLife -= 1;
            break;
        }

    print_map_game(map);
    sleep(2);
}

int how_many_lifes(int map[][10]){
    int lifes = 0;
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(map[i][j] > 10) lifes++;
        }
    }
    return lifes;
}

void start_map(int map[][10]){
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            map[i][j] = 10;
        }
    }
}

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
        attack(mapPlayer2,&player1life,1);
        if(player2life <= 0){
            winner = 1;
            break;
        }
        attack(mapPlayer1,&player2life,2);
        if(player1life <= 0){
            winner = 2;
            break;
        }
    }

    system("clear");
    printf("Player 1");
    print_map_game(mapPlayer1);
    printf("Player 2");
    print_map_game(mapPlayer2);
    printf("\n\tFim de jogo\n\t JOGADOR %d VENCEU\n!",winner);


}