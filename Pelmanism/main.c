#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#define Size 4
#define Fill 42
#define Sides 46
#define Point 15
struct Select{
    int y;
    int x;
    bool s;
};
void Print(char map[Size][Size], struct Select Player);
void WASD(char map[Size][Size], char hide[Size][Size], int See[Size][Size],struct Select *Player, char Button,struct Select *Look){
    switch(Button){
    case 'w':
        if(Player->y!=0)
            Player->y--;
        break;
    case 's':
        if(Player->y!=Size-1)
            Player->y++;
        break;
    case 'a':
        if(Player->x!=0)
            Player->x--;
        break;
    case 'd':
        if(Player->x!=Size-1)
            Player->x++;
        break;
    case ' ':
        if(See[Player->y][Player->x] != 2){
            if(!Look->s){
                if(See[Player->y][Player->x]==0){
                    Look->s=true;
                    Look->y=Player->y;
                    Look->x=Player->x;
                    See[Look->y][Look->x] = 1;
                }
            }
            else{
                if(!(Look->y==Player->y && Look->x==Player->x) && hide[Look->y][Look->x]==hide[Player->y][Player->x]){
                    See[Look->y][Look->x] = 2;
                    See[Player->y][Player->x] = 2;
                    Look->s=false;
                }
                else {
                    Look->s=false;
                    See[Player->y][Player->x] = 1;
                    memset(map,Fill,sizeof(map));
                    for(int i=0;i<Size;i++){
                        for(int j=0;j<Size;j++){
                            if(See[i][j]==1 || See[i][j]==2)
                                map[i][j]=hide[i][j];
                        }
                    }
                    Print(map,*Player);
                    usleep(100000);
                    system("cls");
                    See[Look->y][Look->x] = 0;
                    See[Player->y][Player->x] = 0;
                }
            }
        }
        break;
    }
}
void Print(char map[Size][Size], struct Select Player){
    for(int i=0;i<Size;i++){
        for(int k=0;k<=Size*2;k++){
            if((Player.y==i ||  Player.y+1==i) && (Player.x==k/2 || Player.x*2+2==k))
                printf("%2.c",Point);
            else
                printf("%2.c",Sides);
        }
        printf("\n");
        for(int j=0;j<Size;j++){
            if(i==Player.y && (j==Player.x || j==(Player.x+1)))
                printf("%2.c%2.c",Point,map[i][j]);
            else
                printf("%2.c%2.c",Sides,map[i][j]);
        }
        if(i==Player.y && Size-1==Player.x)
            printf("%2.c\n",Point);
        else
            printf("%2.c\n",Sides);
    }
    for(int k=0;k<=Size*2;k++){
        if(Player.y==Size-1 && (Player.x==k/2 || Player.x*2+2==k))
            printf("%2.c",Point);
        else
            printf("%2.c",Sides);
    }
}
void RandFill(char map[Size][Size]){
    for(int r=0;r<Size*Size;r++){
        char Pair;
        if(r%2==0)
            Pair = 65+rand()%25;
        while(true){
            int X = rand()%Size;
            int Y = rand()%Size;
            if(map[Y][X]!=Fill)
                continue;
            map[Y][X] = Pair;
            break;
        }
    }
}
int main()
{
    if(Size%2!=0){
        printf("The Size number must be even!\n");
        return 0;
    }
    srand(time(NULL));
    char map[Size][Size];
    char hide[Size][Size];
    int look[Size][Size];
    memset(look,0,sizeof(look));
    memset(hide,Fill,sizeof(hide));
    RandFill(hide);
    struct Select Player = {0,0,true};
    struct Select See = {0,0,false};
    while(true){
        system("cls");
        char b = 'q';
        if(kbhit())
            b = getch();
        memset(map,Fill,sizeof(map));
        for(int i=0;i<Size;i++){
            for(int j=0;j<Size;j++){
                if(look[i][j]==1 || look[i][j]==2)
                    map[i][j]=hide[i][j];
            }
        }
        int Result = 0;
        for(int i=0;i<Size;i++){
            for(int j=0;j<Size;j++){
                if(look[i][j]==2)
                    Result++;
            }
        }
        WASD(map,hide,look,&Player,b,&See);
        Print(map,Player);
        printf("\nPair lost : %i\n",Size*Size/2-Result/2);
        if(Result==Size*Size) break;
        usleep(100000);
    }
    printf("You win!\n");
    return 0;
}
