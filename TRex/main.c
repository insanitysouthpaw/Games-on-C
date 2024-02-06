#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
struct player{
    int x;
    int y;
    bool jump;
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
    char rwalls[3][10] = {".......***","........**",".........*"};
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    struct wall walls[2];
    for(int i=0;i<2;i++){
            walls[i].p=9;
            walls[i].type=3;
    }
    bool game = true;
    int curr = 0;
    char t = 0;
    struct player igrok = {8,1,false};
    int points = 0;
    while(game){
        t = 0;
        system("cls");
        if(kbhit()){
            t = getch();
        }
        if(igrok.jump){
            igrok.x--;
        }
        if(t!=0 && !igrok.jump && igrok.x==8){
            igrok.jump = true;
            igrok.x--;
        }
        else {
            if(igrok.x!=8 && !igrok.jump)
                igrok.x++;
        }
        if(igrok.x==6)
            igrok.jump = false;
        if (curr%5 == 0 && curr < 10){
            walls[curr/5].p = 9;
            walls[curr/5].type = rand()%2;
        }
        memset(map,46,sizeof(map));
        for(int i=0;i<curr/5;i++){
            if (walls[i].p == 0){
                walls[i].p = 9;
                walls[i].type = rand()%2;
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
        for(int k=0;k<10;k++){
            map[9][k] = 42;
        }
        if(igrok.x==-1 || igrok.x==10 || map[igrok.x][igrok.y]=='*'){
            game = false;
            break;
        }
        map[igrok.x][igrok.y] = 'L';map[igrok.x-1][igrok.y] = 'O';map[igrok.x-2][igrok.y-1] = '_';map[igrok.x-2][igrok.y+1] = 'p';

        map[1][0]='P';map[1][1]='o';map[1][2]='i';map[1][3]='n';map[1][4]='t';
        map[1][5]='s';map[1][6]='-';map[1][7]=points/100%10+48;map[1][8]=points/10%10+48;map[1][9]=points%10+48;
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++)
                printf("%2.c",map[i][j]);
            printf("\n");
        }
        for(int i=0;i<curr/5;i++){
            walls[i].p--;
        }
        if (curr < 10)
            curr++;
        usleep(300000);
    }
    printf("Game Over\nYou Points : %i\n", points-1);
}
