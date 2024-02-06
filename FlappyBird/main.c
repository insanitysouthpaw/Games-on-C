#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
struct player{
    int x;
    int y;
};
struct wall{
    int p;
    int type;
};
int main()
{
    srand(time(NULL));
    char map[10][10];
    memset(map,46,sizeof(map));
    char rwalls[7][10] = {"*...******","**...*****","***...****","****...***","*****...**","******...*",".........."};
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    struct wall walls[2];
    for(int i=0;i<2;i++){
            walls[i].p=9;
            walls[i].type=7;
    }
    bool game = true;
    int curr = 0;
    char t = 0;
    struct player igrok = {5,1};
    int points = 0;
    while(game){
        t = 0;
        system("cls");
        if(kbhit()){
            t = getch();
        }
        if(t!=0)
            igrok.x--;
        else
            igrok.x++;
        if (curr%5 == 0 && curr < 10){
            walls[curr/5].p = 9;
            walls[curr/5].type = rand()%6;
        }
        memset(map,46,sizeof(map));
        for(int i=0;i<curr/5;i++){
            if (walls[i].p == 0){
                walls[i].p = 9;
                walls[i].type = rand()%6;
            }
            if (walls[i].p == igrok.y){
                points++;
            }
        }
        for(int k=0;k<curr/5;k++){
            for(int j=0;j<10;j++){
                map[j][walls[k].p] = rwalls[walls[k].type][j];
            }
        }
        if(igrok.x==-1 || igrok.x==10 || map[igrok.x][igrok.y]=='*'){
            game = false;
            break;
        }
        map[igrok.x][igrok.y] = '@';
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++)
                printf("%c",map[i][j]);
            printf("\n");
        }
        for(int i=0;i<curr/5;i++){
            walls[i].p--;
        }
        if (curr < 10)
            curr++;
        printf("Points: %i\n",points);
        usleep(300000);
    }
    printf("Game Over\nYou Points : %i\n", points-1);
}
