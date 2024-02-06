#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#define Height 20
#define Width 13
#define Fill 46
#define Rock 42
struct Figure{
    int y;
    int x;
    int type;
};
void DrawFigure(int y, int x, int type, char map[Height][Width]){
    switch(type){
    case 0:
        map[y-1][x] = Rock;
        map[y][x-1] = Rock; map[y][x] = Rock; map[y][x+1] = Rock;
        map[y+1][x] = Rock;
        break;
    case 1:
        map[y-1][x-1] = Rock; map[y-1][x+1] = Rock;
        map[y][x] = Rock;
        map[y+1][x-1] = Rock; map[y+1][x+1] = Rock;
        break;
    case 2:
        map[y-1][x-1] = Rock; map[y-1][x] = Rock; map[y-1][x+1] = Rock;
        map[y][x-1] = Rock; map[y][x+1] = Rock;
        map[y+1][x-1] = Rock; map[y+1][x] = Rock; map[y+1][x+1] = Rock;
        break;
    }
}
void DrawSelect(int select,char map[Height][Width]){
    switch(select){
    case 0:
        for(int i=1;i<=3;i++)
            map[Height-1][i] = '_';
        break;
    case 1:
        for(int i=5;i<=7;i++)
            map[Height-1][i] = '_';
        break;
    case 2:
        for(int i=9;i<=11;i++)
            map[Height-1][i] = '_';
        break;
    }
}
void Print(char map[Height][Width]){
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++)
            printf("%2.c",map[i][j]);
        printf("\n");
    }
}
int main()
{
    srand(time(NULL));
    char map[Height][Width];
    bool Correct = false;
    int Select = 1;
    struct Figure PlayerFigure[3] = {{Height-3,2,rand()%2},{Height-3,6,rand()%2},{Height-3,10,rand()%2}};
    struct Figure Right[3] = {{1,2,rand()%2},{1,6,rand()%2},{1,10,rand()%2}};
    int Timeout = 0;
    int Points = 0;
    while(true){
        system("cls");
        char b = 'q';
        if(kbhit())
            b = getch();
        switch(b){
        case 'a':
            if(Select!=0) Select--;
            break;
        case 'd':
            if(Select!=2) Select++;
            break;
        case ' ':
            PlayerFigure[Select].type = (PlayerFigure[Select].type+1)%3;
            break;
        }
        if(Right[0].y==Height-3){
            int Check = 0;
            for(int i=0;i<3;i++)
                if(PlayerFigure[i].type==Right[i].type)
                    Check++;
            if(Check!=3)
                break;
            Correct = true;
            Points++;
        }
        if(Timeout==0){
            for(int i=0;i<3;i++)
                Right[i].y++;
        }
        Timeout = (Timeout+1)%2;
        if(Correct){
            PlayerFigure[0].y = Height-3; PlayerFigure[0].x = 2; PlayerFigure[0].type = rand()%2;
            PlayerFigure[1].y = Height-3; PlayerFigure[1].x = 6; PlayerFigure[1].type = rand()%2;
            PlayerFigure[2].y = Height-3; PlayerFigure[2].x = 10; PlayerFigure[2].type = rand()%2;
            Right[0].y = 2; Right[0].x = 2; Right[0].type = rand()%2;
            Right[1].y = 2; Right[1].x = 6; Right[1].type = rand()%2;
            Right[2].y = 2; Right[2].x = 10; Right[2].type = rand()%2;
            Correct = false;
        }
        memset(map,Fill,sizeof(map));
        for(int i=0;i<3;i++){
            DrawFigure(PlayerFigure[i].y,PlayerFigure[i].x,PlayerFigure[i].type,map);
            DrawFigure(Right[i].y,Right[i].x,Right[i].type,map);
        }
        DrawSelect(Select,map);
        Print(map);
        printf("Points : %i",Points);
        usleep(100000);
    }
    Print(map);
    printf("GameOver!\nYou Points : %i",Points);
    return 0;
}
