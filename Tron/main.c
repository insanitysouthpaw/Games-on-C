#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
#define SIZE 10
#define FILL 46
struct Entity{
    int y;
    int x;
};
void Print(char map[SIZE][SIZE]){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++)
            printf("%2.c",map[i][j]);
        printf("\n");
    }
}
void Control(char * button , struct Entity * Player, char map[SIZE][SIZE], bool * Game){
    switch(*button){
    case('w'):
        if(Player->y!=0 && map[Player->y-1][Player->x]==FILL)
            Player->y--;
        else
            *Game = false;
        break;
    case('s'):
        if(Player->y!=SIZE-1 && map[Player->y+1][Player->x]==FILL)
            Player->y++;
        else
            *Game = false;
        break;
    case('a'):
        if(Player->x!=0 && map[Player->y][Player->x-1]==FILL)
            Player->x--;
        else
            *Game = false;
        break;
    case('d'):
        if(Player->x!=SIZE-1 && map[Player->y][Player->x+1]==FILL)
            Player->x++;
        else
            *Game = false;
        break;
    }
}
bool EnemyMove(struct Entity * Enemy, char map[SIZE][SIZE]){
    int Move = rand()%4;
    for(int i=0;i<5;i++){
        switch(Move){
        case 0:
            if(Enemy->y!=0 && map[Enemy->y-1][Enemy->x]==FILL){
                Enemy->y--;
                return false;
            }
            break;
        case 1:
            if(Enemy->y!=SIZE-1 && map[Enemy->y+1][Enemy->x]==FILL){
                Enemy->y++;
                return false;
            }
            break;
        case 2:
            if(Enemy->x!=0 && map[Enemy->y][Enemy->x-1]==FILL){
                Enemy->x--;
                return false;
            }
            break;
        case 3:
            if(Enemy->x!=SIZE-1 && map[Enemy->y][Enemy->x+1]==FILL){
                Enemy->x++;
                return false;
            }
            break;
        }
        Move = (Move + 1) % 4;
    }
    return true;
}
int main()
{
    srand(time(NULL));
    char map[SIZE][SIZE];
    memset(map,FILL,sizeof(map));
    struct Entity Player =  {SIZE-2,SIZE-2};
    struct Entity Enemy = {1,1};
    char button = 'w';
    bool Game = true;
    while(Game){
        system("cls");
        if(kbhit()){
            char tmp = getch();
            if(tmp=='a' || tmp=='d' || tmp=='w' || tmp=='s')
                button = tmp;
        }
        Control(&button,&Player,map,&Game);
        if(EnemyMove(&Enemy,map))
            break;
        map[Player.y][Player.x] = 2;
        map[Enemy.y][Enemy.x] = 1;
        Print(map);
        usleep(200000);
    }
    if(Game){
        Print(map);
        printf("Congrats, you win!\n");
    }
    else
        printf("You lose!\n");
    return 0;
}
