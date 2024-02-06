#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#define SIZE 9
#define WALL 15
#define VOID 46
#define PLAYER 1
#define FINISH 88
struct Entity{
    int y;
    int x;
};
void GeneratePlan(bool Plan[SIZE][SIZE]){
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(i==0)
                Plan[i][j] = false;
            else if(j==0)
                Plan[i][j] = true;
            else
                Plan[i][j] = rand()%2;
}
void FillMaze(char Maze[SIZE*2+1][SIZE*2+1], bool Plan[SIZE][SIZE]){
    for(int i=0;i<SIZE*2+1;i++){
        Maze[i][0] = WALL;
        Maze[0][i] = WALL;
        Maze[i][SIZE*2] = WALL;
        Maze[SIZE*2][i] = WALL;
    }
    for(int i=0;i<SIZE;i++){
        for(int j=SIZE-1;j>=0;j--){
            int y = (SIZE-i)*2;
            int x = (SIZE-j)*2+1;
            if(Plan[i][j]){
                Maze[y][x-1] = WALL;
                Maze[y+1][x-1] = WALL;
            }
            else{
                Maze[y][x] = WALL;
                Maze[y][x-1] = WALL;
            }
        }
    }
}
void Control(struct Entity * Player, char * Button, char Maze[SIZE*2+1][SIZE*2+1]){
    switch(*Button){
    case 'w':
        if(Maze[Player->y-1][Player->x]!=WALL)
            Player->y--;
        break;
    case 's':
        if(Maze[Player->y+1][Player->x]!=WALL)
            Player->y++;
        break;
    case 'a':
        if(Maze[Player->y][Player->x-1]!=WALL)
            Player->x--;
        break;
    case 'd':
        if(Maze[Player->y][Player->x+1]!=WALL)
            Player->x++;
        break;
    }
}
void Print(char Maze[SIZE*2+1][SIZE*2+1],struct Entity * Player,struct Entity * Exit){
    for(int i=0;i<SIZE*2+1;i++){
        for(int j=0;j<SIZE*2+1;j++){
            if(i==Player->y && j==Player->x)
                printf("%2.c",PLAYER);
            else if(i==Exit->y && j==Exit->x)
                printf("%2.c",FINISH);
            else
                printf("%2.c",Maze[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    srand(time(NULL));
    bool Plan[SIZE][SIZE];
    GeneratePlan(Plan);
    char Maze[SIZE*2+1][SIZE*2+1];
    memset(Maze,VOID,sizeof(Maze));
    FillMaze(Maze,Plan);
    struct Entity Player = {1,1};
    struct Entity Exit = {SIZE*2-1,SIZE*2-1};
    while(true){
        system("cls");
        char Button = " ";
        if(kbhit())
            Button = getch();
        Control(&Player,&Button,Maze);
        Print(Maze,&Player,&Exit);
        if(Player.y==Exit.y && Player.x==Exit.x)
            break;
        usleep(100000);
    }
    return 0;
}
