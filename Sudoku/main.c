#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
struct Point{
    int y;
    int x;
};
void Control(char Button, struct Point *Player, int map[9][9]){
    switch(Button){
    case 'w':
        if(Player->y!=0)
            Player->y--;
        break;
    case 's':
        if(Player->y!=8)
            Player->y++;
            break;
    case 'a':
        if(Player->x!=0)
            Player->x--;
        break;
    case 'd':
        if(Player->x!=8)
            Player->x++;
        break;
    default:
        if(Button >= 48 && Button <= 57 && map[Player->y][Player->x] == 0)
            map[Player->y][Player->x] = Button - 48;
        break;
    }
}
void FillMap(int map[9][9]){
     for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            map[i][j] = (j+i*3+i/3)%9+1;
     for(int i=0;i<3;i++){
        int ShuffleStrok1 = (i*3) + rand()%3;
        int ShuffleStrok2 = (i*3) + rand()%3;
        for(int j=0;j<9;j++){
            int tmp = map[ShuffleStrok1][j];
            map[ShuffleStrok1][j] = map[ShuffleStrok2][j];
            map[ShuffleStrok2][j] = tmp;
        }
     }
     for(int i=0;i<3;i++){
        int ShuffleStolb1 = (i*3) + rand()%3;
        int ShuffleStolb2 = (i*3) + rand()%3;
        for(int j=0;j<9;j++){
            int tmp = map[j][ShuffleStolb1];
            map[j][ShuffleStolb1] = map[j][ShuffleStolb2];
            map[j][ShuffleStolb2] = tmp;
        }
     }
}
void MapPreparation(int map[9][9]){
    int CountZeros = 0;
    while(CountZeros!=40){
        int Position = rand()%81;
        if(map[Position/9][Position%9]==0)
            continue;
        map[Position/9][Position%9] = 0;
        CountZeros++;
    }
}
bool CheckEnd(int map[9][9], int result[9][9]){
    int Result = 0;
     for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(map[i][j]==result[i][j])
                Result++;
        }
     }
     if(Result==81)
        return true;
     else return false;
}
void Print(int map[9][9],struct Point *Player){
    for(int i=0;i<9;i++){
        if(i%3==0){
            for(int j=0;j<31;j++)
                printf("-");
            printf("\n");
        }
        for(int j=0;j<9;j++){
            if(i != Player->y || j != Player->x || time(NULL)%2 != 1){
                if(j%3==0)
                    printf("|%2.i ",map[i][j]);
                else
                    printf("%2.i ",map[i][j]);
            }
            else {
                if(j%3==0)
                    printf("|%2.c ",'*');
                else
                    printf("%2.c ",'*');
            }
        }
        printf("|\n");
    }
    for(int j=0;j<31;j++)
        printf("-");
    printf("\n");
}
int main()
{
    srand(time(NULL));
    int map[9][9];
    int result[9][9];
    FillMap(map);
    memcpy(result,map,sizeof(map));
    MapPreparation(map);
    struct Point Player = {0,0};
    while(true){
        system("cls");
        char Button = ' ';
        if(kbhit()){
            Button = getch();
        }
        Control(Button,&Player,map);
        Print(map,&Player);
        if(CheckEnd(map,result)){
            printf("You win!\n");
            break;
        }
        usleep(100000);
    }
    return 0;
}
