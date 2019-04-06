#ifndef BATALHA_NAVAL_H
#define BATALHA_NAVAL_H

//valCov para valor do navio coberto no mapa 'ingame'
//valUnc para valor do navio descoberto no mapa 'ingame'
typedef struct ship{
    char *name;
    int size;
    int valCov;
    int valUnc;
    char dir;
}Ship;

//Printa o mapa durante alocação de navios no mapa
void print_map_selection(int map[][10]);

//Printa mapa durante jogo
void print_map_game(int map[][10]);


//Verifica se o navio cabe no local selecionado
unsigned int it_fit(Ship nav,int map[][10],int x,int y);

//Adiciona navio ao mapa
void add_ship(Ship nav, int map[][10], int x, int y);

//Pede coordenadas de entrada pra adicionar navio
void input_ship(int map[][10], Ship nav);

//Fase de posicionamento
void set_game(int map[][10]);

//Ataca nas coordenadas pedidas, revela a casa atacada, e recalcula a vida do jogador se acerta navio
void attack(int map[][10],int *enemyLife,int player);

//Retorna quantidade de casas do mapa que estão ocupadas por navios
int how_many_lifes(int map[][10]);

//Inicializa mapa
void start_map(int map[][10]);

#endif
