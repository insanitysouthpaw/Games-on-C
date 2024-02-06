#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#define SIZE 5
#define FILL 46
#define TREE 73
#define TWIG 42
#define TICK 15
#define COOLDOWN 10
void Print(int length, bool arr[], bool Player, int Points, int Fraps){
    char map[length*2][length*2+1];
    memset(map,FILL,sizeof(map));
    for(int i=0;i<length;i++){
        if(!arr[i]){
            for(int k=0;k<length;k++)
                map[i*2][k] = TWIG;
        }
        else{
            for(int k=length+1;k<=length*2;k++)
                map[i*2][k] = TWIG;
        }
    }
    for(int i=0;i<length*2;i++)
        map[i][length] = TREE;
    if(Player){
        map[length*2-3][length-2] = '@';
        map[length*2-2][length-3] = '/';  map[length*2-2][length-2] = '-'; map[length*2-2][length-1] = 'T';
        map[length*2-1][length-3] = '/'; map[length*2-1][length-2] = '\\';
    }
    else{
        map[length*2-3][length+2] = '@';
        map[length*2-2][length+1] = 'T'; map[length*2-2][length+2] = '-'; map[length*2-2][length+3] = '\\';
        map[length*2-1][length+2] = '/'; map[length*2-1][length+3] = '\\';
    }
    for(int k=0;k < length*2+1;k++){
        if(k * COOLDOWN < Fraps * (length*2+1))
            printf("%2.c",TICK);
    }
    printf("\n");
    for(int i=0;i<length*2;i++){
        for(int j=0;j<length*2+1;j++)
            printf("%2.c",map[i][j]);
        printf("\n");
    }
    printf("Points : %i\n",Points);
}
bool Move(int length, bool arr[], bool *Player, char Step, int *Points, int *Fraps){
    if(*Fraps <= 0)
        return true;
    switch(Step){
    case 'd':
        *Player = false;
        break;
    case 'a':
        *Player = true;
        break;
    default:
        return false;
    }
    for(int i=length-1;i>0;i--){
        arr[i] = arr[i-1];
    }
    arr[0] = rand()%2;
    *Points += 1;
    *Fraps = COOLDOWN;
    return *Player != arr[length-1];
}
void FillArr(int length, bool arr[]){
    for(int i=0;i<length;i++)
        arr[i] = rand()%2;
}
int main()
{
    if(SIZE < 3) return 0;
    srand(time(NULL));
    bool arr[SIZE];
    FillArr(SIZE,arr);
    bool Player = arr[SIZE-1];
    char Step;
    int Points = 0;
    int Fraps = COOLDOWN * COOLDOWN;
    Print(SIZE,arr,Player,Points,Fraps);
    while(true){
        Fraps--;
        Step = ' ';
        if(kbhit())
            Step = getch();
        system("cls");
        if(Move(SIZE,arr,&Player,Step,&Points,&Fraps)){
            Print(SIZE,arr,Player,Points,Fraps);
            break;
        }
        Print(SIZE,arr,Player,Points,Fraps);
        usleep(100000);
    }
}
