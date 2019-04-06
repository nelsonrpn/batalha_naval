#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <batalha_lib.h>


/*
    Casas cobertas com valores > 10
    e descobertar com valores < 10
    
    0/10 = Àgua
    1/11 = Corveta
    2/12 = Submarino
    3/13 = Fragata
    4/14 = Destroyer
    5/15 = Porta-Aviões
    
*/


//Printa o mapa durante alocação de navios no mapa
void print_map_selection(int map[][10]){
    system("clear");
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0;i<10;i++){
        printf("%d",i);
        for(int j = 0;j<10;j++){
            switch(map[i][j]){
                case 10: printf(" ~");  break;
                case 11: printf(" C");  break;
                case 12: printf(" S");  break;
                case 13: printf(" F");  break;
                case 14: printf(" D");  break;
                case 15: printf(" P");  break;
            }
        }
        printf("\n");
    }
}    

//Printa mapa durante jogo
void print_map_game(int map[][10]){
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0;i<10;i++){
        printf("%d",i);
        for(int j = 0;j<10;j++){
            if(map[i][j] >= 10) printf(" #");
            else{
                switch(map[i][j]){
                    case 0: printf(" ~");   break;
                    case 1: printf(" C");   break;
                    case 2: printf(" S");   break;
                    case 3: printf(" F");   break;
                    case 4: printf(" D");   break;
                    case 5: printf(" P");   break;
                }
            }
        }
        printf("\n");
    }
}


//Verifica se o navio cabe no local selecionado
unsigned int it_fit(Ship nav,int map[][10],int x,int y){
    if(nav.dir == 'H'){
        for(int i = 0;i<nav.size;i++){
            if(map[x][y] != 10 || x > 9 || y > 9) return 0;
            y++;
        }
    }
    else if(nav.dir == 'V'){
        for(int i = 0;i<nav.size;i++){
            if(map[x][y] != 10 || x > 9 || y > 9) return 0;
            x++;
        }
    return 1;
    }
}
    

//Adiciona navio ao mapa
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

//Pede coordenadas de entrada pra adicionar navio
void input_ship(int map[][10], Ship nav){
    int y,x,check = 0;

    do{
        printf("Digite as coordenadas e direcao para posicionar a %s (%d casas) [0 0 H/V]\n",nav.name, nav.size);
        scanf("%d %d %c",&x,&y,&nav.dir);

        if(!it_fit(nav,map,x,y))
            printf("Coordenada invalida para posicionamento de %s!\n",nav.name);
        else{
            add_ship(nav,map,x,y);
            check = 1;
        }
    }while(!check);

    print_map_selection(map);
}

//Fase de posicionamento
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
    
    //free(corveta.name);
    //free(submarino.name);
    //free(fragata.name);
    //free(destroyer.name);
    //free(porta.name);
}

//Ataca nas coordenadas pedidas, revela a casa atacada, e recalcula a vida do jogador se acerta navio
void attack(int map[][10],int *enemyLife,int player){
    int x,y;
    
    system("clear");
    printf("Player %d turn\n",player);
    print_map_game(map);
    
    printf("Selecione as coordenadas para disparar:\n");
    scanf("%d %d",&x,&y);
    
    if(map[x][y] >= 10) map[x][y] -= 10;
    //Se a casa já está descoberta, sai da função
    else return;
    
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


//Retorna quantidade de casas do mapa que estão ocupadas por navios
int how_many_lifes(int map[][10]){
    int lifes = 0;
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            if(map[i][j] > 10) lifes++;
        }
    }
    return lifes;
}

//Inicializa mapa
void start_map(int map[][10]){
    for(int i = 0;i<10;i++){
        for(int j = 0;j<10;j++){
            map[i][j] = 10;
        }
    }
}
