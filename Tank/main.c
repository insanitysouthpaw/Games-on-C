#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <conio.h>
#include <unistd.h>
#define size 15
struct tank{
    int y;
    int x;
    bool life;
    bool move;
    char direction;
    bool bullet;
    int bullet_x;
    int bullet_y;
    char direction_bullet;
};
struct enemy{
    int y;
    int x;
    char direction;
    bool life;
    bool move;
};
int main()
{
    srand(time(NULL));
    struct tank player = {size/2,1,true,false,'w',false,0};
    struct enemy enemy ={1+rand()%(size-3),size-2,'d',true,false};
    int points = 10;
    while(true){
        if(points==0)
            break;
        if(enemy.life && abs(player.x-enemy.x)<3 && abs(player.y-enemy.y)<3){
            player.life = false;
            break;
        }
        system("cls");
        if(!enemy.life){
            enemy.y=1+rand()%(size-3);
            enemy.x=size-2;
            enemy.direction='d';
            enemy.life=true;
            enemy.move=false;
        }
        bool fire = false;
        if(kbhit()){
            char tmp = player.direction;
            char t = getch();
            if(t=='w' || t=='s' || t=='a' || t=='d' || t==' '){
                if(t==' '){
                    player.direction = tmp;
                }
                else {
                    player.direction = t;
                    player.move = true;
                }
            }
            if(t==' ')
                fire = true;
        }
        char map[size][size];
        memset(map,46,sizeof(map));
        switch(player.direction){
        case 'w':
            if(player.y!=1 && player.move)
                player.y--;
            map[player.y-1][player.x-1] = '*'; map[player.y-1][player.x] = '|'; map[player.y-1][player.x+1] = '*';
            map[player.y][player.x-1] = '*'; map[player.y][player.x] = 'O'; map[player.y][player.x+1] = '*';
            map[player.y+1][player.x-1] = '*'; map[player.y+1][player.x] = 'X'; map[player.y+1][player.x+1] = '*';
            break;
        case 's':
            if(player.y!=size-2 && player.move)
                player.y++;
            map[player.y-1][player.x-1] = '*'; map[player.y-1][player.x] = 'X'; map[player.y-1][player.x+1] = '*';
            map[player.y][player.x-1] = '*'; map[player.y][player.x] = 'O'; map[player.y][player.x+1] = '*';
            map[player.y+1][player.x-1] = '*'; map[player.y+1][player.x] = '|'; map[player.y+1][player.x+1] = '*';
            break;
        case 'd':
            if(player.x!=size-2 && player.move)
                player.x++;
            map[player.y-1][player.x-1] = '*'; map[player.y-1][player.x] = '*'; map[player.y-1][player.x+1] = '*';
            map[player.y][player.x-1] = 'X'; map[player.y][player.x] = 'O'; map[player.y][player.x+1] = '-';
            map[player.y+1][player.x-1] = '*'; map[player.y+1][player.x] = '*'; map[player.y+1][player.x+1] = '*';
            break;
        case 'a':
            if(player.x!=1 && player.move)
                player.x--;
            map[player.y-1][player.x-1] = '*'; map[player.y-1][player.x] = '*'; map[player.y-1][player.x+1] = '*';
            map[player.y][player.x-1] = '-'; map[player.y][player.x] = 'O'; map[player.y][player.x+1] = 'X';
            map[player.y+1][player.x-1] = '*'; map[player.y+1][player.x] = '*'; map[player.y+1][player.x+1] = '*';
            break;
        case ' ':
            if(!player.bullet){
                player.bullet = true;
                player.direction_bullet = player.direction;
                player.bullet_x = player.x;
                player.bullet_y = player.y;
            }
            break;
        default:
            break;
        }
        if(fire){
            if(!player.bullet){
                player.bullet = true;
                player.direction_bullet = player.direction;
                player.bullet_x = player.x;
                player.bullet_y = player.y;
            }
        }
        if(player.bullet){
            switch(player.direction_bullet){
            case 'w':
                player.bullet_y--;
                break;
            case 's':
                player.bullet_y++;
                break;
            case 'd':
                player.bullet_x++;
                break;
            case 'a':
                player.bullet_x--;
                break;
            }
        }
        if(player.bullet_x<0 || player.bullet_x>size-1 || player.bullet_y<0 || player.bullet_y>size-1)
            player.bullet = false;
        if((enemy.x-1==player.bullet_x && enemy.y-1==player.bullet_y) ||
           (enemy.x==player.bullet_x && enemy.y-1==player.bullet_y) ||
           (enemy.x+1==player.bullet_x && enemy.y-1==player.bullet_y) ||
           (enemy.x-1==player.bullet_x && enemy.y==player.bullet_y) ||
           (enemy.x==player.bullet_x && enemy.y==player.bullet_y) ||
           (enemy.x+1==player.bullet_x && enemy.y==player.bullet_y) ||
           (enemy.x-1==player.bullet_x && enemy.y+1==player.bullet_y) ||
           (enemy.x==player.bullet_x && enemy.y+1==player.bullet_y) ||
           (enemy.x+1==player.bullet_x && enemy.y+1==player.bullet_y)){
            enemy.life = false;
            points--;
           }
        if(enemy.life){
        switch(enemy.direction){
            case 'w':
                map[enemy.y-1][enemy.x-1] = '*'; map[enemy.y-1][enemy.x] = 'o'; map[enemy.y-1][enemy.x+1] = '*';
                map[enemy.y][enemy.x-1] = '*'; map[enemy.y][enemy.x] = 'O'; map[enemy.y][enemy.x+1] = '*';
                map[enemy.y+1][enemy.x-1] = '*'; map[enemy.y+1][enemy.x] = 'o'; map[enemy.y+1][enemy.x+1] = '*';
                break;
            case 's':
                map[enemy.y-1][enemy.x-1] = '*'; map[enemy.y-1][enemy.x] = 'o'; map[enemy.y-1][enemy.x+1] = '*';
                map[enemy.y][enemy.x-1] = '*'; map[enemy.y][enemy.x] = 'O'; map[enemy.y][enemy.x+1] = '*';
                map[enemy.y+1][enemy.x-1] = '*'; map[enemy.y+1][enemy.x] = 'o'; map[enemy.y+1][enemy.x+1] = '*';
                break;
            case 'd':
                map[enemy.y-1][enemy.x-1] = '*'; map[enemy.y-1][enemy.x] = '*'; map[enemy.y-1][enemy.x+1] = '*';
                map[enemy.y][enemy.x-1] = 'o'; map[enemy.y][enemy.x] = 'O'; map[enemy.y][enemy.x+1] = 'o';
                map[enemy.y+1][enemy.x-1] = '*'; map[enemy.y+1][enemy.x] = '*'; map[enemy.y+1][enemy.x+1] = '*';
                break;
            case 'a':
                map[enemy.y-1][enemy.x-1] = '*'; map[enemy.y-1][enemy.x] = '*'; map[enemy.y-1][enemy.x+1] = '*';
                map[enemy.y][enemy.x-1] = 'o'; map[enemy.y][enemy.x] = 'O'; map[enemy.y][enemy.x+1] = 'o';
                map[enemy.y+1][enemy.x-1] = '*'; map[enemy.y+1][enemy.x] = '*'; map[enemy.y+1][enemy.x+1] = '*';
                break;
        }
        }
        if(enemy.move){
            if(abs(enemy.x-player.x)>abs(enemy.y-player.y)){
                if(enemy.x-player.x>0){
                    enemy.direction = 'a';
                    enemy.x--;
                }
                else {
                    enemy.direction = 'd';
                    enemy.x++;
                }
            }
            else
                if(enemy.y-player.y>0) {
                    enemy.direction = 'w';
                    enemy.y--;
                }
                else {
                    enemy.direction = 's';
                    enemy.y++;
                }
            enemy.move = false;
        }
        else
            enemy.move = true;
        switch(player.direction_bullet){
            case 'w':
                player.bullet_y--;
                break;
            case 's':
                player.bullet_y++;
                break;
            case 'd':
                player.bullet_x++;
                break;
            case 'a':
                player.bullet_x--;
                break;
        }
        if(player.move)
            player.move = false;
        if(player.bullet)
            map[player.bullet_y][player.bullet_x]='o';
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++)
                printf("%2.c",map[i][j]);
            printf("\n");
        }
        printf("Tanks left: %i\n",points);
        usleep(500000);
    }
    if(player.life)
        printf("Congratulations, you win!\n");
    else
        printf("You lost...\n");
    return 0;
}
