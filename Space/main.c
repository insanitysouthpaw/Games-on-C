#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#define size 15
struct igrok{
    int x;
    int y;
    bool life;
    char move;
    bool fire;
    int fire_x;
    int fire_y;
};
struct ufo{
    int x;
    int y;
    bool life;
    int move;
};
void Draw(struct igrok player, struct ufo enemy[3],char m[size][size]){
    m[player.y-1][player.x] = 'I';
    m[player.y][player.x] = 'O';
    m[player.y][player.x-1] = '/';
    m[player.y][player.x+1] = '\\';
    m[player.y+1][player.x] = 'U';
    m[player.y+1][player.x-1] = '\\';
    m[player.y+1][player.x+1] = '/';
    for(int k=0;k<3;k++){
        if(enemy[k].life){
            m[enemy[k].y-1][enemy[k].x-1]='/'; m[enemy[k].y-1][enemy[k].x]='-'; m[enemy[k].y-1][enemy[k].x+1]='\\';
            m[enemy[k].y][enemy[k].x-1]='|'; m[enemy[k].y][enemy[k].x]='O'; m[enemy[k].y][enemy[k].x+1]='|';
            m[enemy[k].y+1][enemy[k].x-1]='\\'; m[enemy[k].y+1][enemy[k].x]='-'; m[enemy[k].y+1][enemy[k].x+1]='/';
        }
    }
    if(player.fire)
        m[player.fire_y][player.fire_x] = 42;
}
void Print(char m[size][size],int start,int current,int points){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            printf("%2.c",m[i][j]);
        printf("\n");
    }
    printf("Current points : %i\nTime survived : %i\n",points,current-start);
}
int main()
{
    srand(time(NULL));
    struct igrok player = {size/2,size-2,true,0,false,0,0,false};
    struct ufo enemy[3] = {{1+rand()%4,0,true,0},{6+rand()%4,0,true,0},{11+rand()%3,0,true,0}};
    int t = time(NULL);
    int points = 0;
    while(true){
        system("cls");
        for(int k=0;k<3;k++){
            if(enemy[k].life){
                if(player.fire && abs(enemy[k].x-player.fire_x)<=1 && abs(enemy[k].y-player.fire_y)<=1){
                    enemy[k].life = false;
                    player.fire = false;
                    enemy[k].x = 1+rand()%13;
                    enemy[k].y = 0;
                    enemy[k].life = true;
                    enemy[k].move = 0;
                    points++;
                }
                if(enemy[k].y==size-1)
                    player.life = false;
                if(enemy[k].move%3==0)
                    enemy[k].y++;
                enemy[k].move++;
                if(enemy[k].y==size-1 || (abs(enemy[k].x-player.x)<=2 && abs(enemy[k].y-player.y)<=2))
                    player.life = false;
            }
        }
        if(player.fire){
            if(player.fire_y==0)
                player.fire = false;
            player.fire_y--;
        }
        char b = 0;
        if(kbhit())
            b = getch();
        switch(b){
        case 'a':
            if(player.x!=1)
                player.x--;
            break;
        case 'd':
            if(player.x!=size-2)
                player.x++;
            break;
        case ' ':
            if(!player.fire){
                player.fire = true;
                player.fire_y = player.y-2;
                player.fire_x = player.x;
            }
            break;
        default:
            break;
        }
        char map[size][size];
        memset(map,46,sizeof(map));
        Draw(player,enemy ,map);
        int c_t = time(NULL);
        Print(map,t,c_t,points);
        if(!player.life)
            break;
        usleep(100000);
    }
    printf("Game Over!\n");
    return 0;
}
