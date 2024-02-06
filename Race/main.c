#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>
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
    int rwalls[8] = {2,3,4,5,6,7,8,0};

    struct wall walls[2];
    for(int i=0;i<2;i++){
            walls[i].p=9;
            walls[i].type=8;
    }
    bool game = true;
    int curr = 0;
    char t = 0;
    struct player igrok = {8,1+rand()%7};
    map[igrok.x][igrok.y] = '@';
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    int points = 0;
    printf("Press any button to start...");
    getch();
    while(game){
        t = 0;
        system("cls");
        if(kbhit()){
            t = getch();
        }
        if(t=='a' && igrok.y!=1)
            igrok.y--;
        if(t=='d' && igrok.y!=8)
            igrok.y++;
        if (curr%5 == 0 && curr < 10){
            walls[curr/5].p = 1;
            walls[curr/5].type = rand()%7;
        }
        memset(map,46,sizeof(map));
        for(int k=0;k<curr/5;k++){
            map[walls[k].p][rwalls[walls[k].type]] = 'V';
            map[walls[k].p][rwalls[walls[k].type]-1] = '|'; map[walls[k].p][rwalls[walls[k].type]+1] = '|';
            if(walls[k].p-1>=0){
                map[walls[k].p-1][rwalls[walls[k].type]] = 'M';
                map[walls[k].p-1][rwalls[walls[k].type]-1] = '|'; map[walls[k].p-1][rwalls[walls[k].type]+1] = '|';
            }
        }
        for(int i=0;i<curr/5;i++){
            if (walls[i].p == igrok.x+1){
                points++;
            }
            if (walls[i].p == 9){
                walls[i].p = 0;
                walls[i].type = rand()%7;
            }
        }
        if(map[igrok.x][igrok.y]!=46 || map[igrok.x][igrok.y-1]!=46 || map[igrok.x][igrok.y+1]!=46){
            game = false;
            break;
        }
        map[igrok.x][igrok.y] = 'A'; map[igrok.x+1][igrok.y] = 'U';
        map[igrok.x][igrok.y+1] = '|'; map[igrok.x][igrok.y-1] = '|';
        map[igrok.x+1][igrok.y+1] = '|'; map[igrok.x+1][igrok.y-1] = '|';
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++)
                printf("%c",map[i][j]);
            printf("\n");
        }
        for(int i=0;i<curr/5;i++){
            walls[i].p++;
        }
        if (curr < 10)
            curr++;
        printf("Points: %i\n",points);
        usleep(300000);
    }
    printf("Game Over\nYou Points : %i\n", points-1);
}
