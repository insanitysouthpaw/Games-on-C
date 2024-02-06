#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <unistd.h>
struct player{
    int x;
    int y;
    bool life;
};
struct bomb{
    int x;
    int y;
};
int main()
{
    srand(time(NULL));
    char map[10][10];
    memset(map,46,sizeof(map));
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    struct bomb bombs[10];
    int b = 0;
    for(int i=0;i<10;i++){
        while(true){
        bombs[i].x = rand()%9;
        bombs[i].y = rand()%9;
        bool q = false;
        for(int t = 0;t < b;t++){
            if(bombs[i].x == bombs[t].x && bombs[i].y == bombs[t].y)
                q = true;
        }
        if(!q){
            b++;
            break;
        }
        }
    }
    struct player igrok = {rand()%9,rand()%9,true};
    bool game = true, end = true;
    char move;
    while(game){
        int close = 0;
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++)
                if(map[i][j]==46)
                    close++;
        }
        if(close==10){
            game = false;
            break;
        }
        move = getchar();
        char tmp[10][10];
        memcpy(tmp,map,sizeof(map));
        switch(move){
        case 'w':
            if(igrok.x!=0)
                igrok.x--;
            break;
        case 's':
            if(igrok.x!=9)
                igrok.x++;
            break;
        case 'a':
            if(igrok.y!=0)
                igrok.y--;
            break;
        case 'd':
            if(igrok.y!=9)
                igrok.y++;
            break;
        case ' ':
            for(int i=0;i<10;i++){
                if(igrok.x==bombs[i].x && igrok.y==bombs[i].y){
                    game = false;
                    end = false;
                    break;
                }
            }
            for(int i = igrok.x-1;i <= igrok.x+1; i++){
                for(int j = igrok.y-1;j <= igrok.y+1; j++){
                    if(i>=0 && i<=9 && j>=0 && j<=9){
                        int col_bombs = 0;
                        for(int k = i-1;k <= i+1; k++){
                            for(int l = j-1;l <= j+1; l++){
                                if(k>=0 && k<=9 && l>=0 && l<=9)
                                    for(int z=0;z<10;z++)
                                        if(k==bombs[z].x && l==bombs[z].y)
                                            col_bombs++;
                            }
                        }
                        int c = 0;
                        for(int z=0;z<10;z++)
                            if(bombs[z].x==i && bombs[z].y==j)
                                c++;
                        if(c==0)
                            map[i][j]=col_bombs+48;
                    }
                }
            }
        default:
            break;
        }
        system("cls");
        tmp[igrok.x][igrok.y]='@';
        for(int i=0;i<10;i++)
            map[bombs[i].x][bombs[i].y]='*';
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++)
                printf("%c",tmp[i][j]);
            printf("\n");
        }
    }
    if(end) printf("Victory!\n");
    else printf("Defeat!\n");
    return 0;
}
