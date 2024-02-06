#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#define Width 20
#define Height 15
#define Fill 46
void DrawCar(int point,int pos,char map[Height][Width]){
    switch(pos){
    case 0:
        map[3][point-1] = '_'; map[3][point] = '_';
        map[2][point-2] = '/'; map[2][point-1] = '_'; map[2][point] = '_'; map[2][point+1] = '\\';
        map[1][point-3] = '('; map[1][point-2] = 'O'; map[1][point-1] = '_'; map[1][point] = '_'; map[1][point+1] = 'O'; map[1][point+2] = ')';
        map[0][point-2] = '0'; map[0][point+1] = '0';
        break;
    case 1:
        map[3][point-1] = '_'; map[3][point] = '_';
        map[2][point-2] = '/'; map[2][point-1] = '_'; map[2][point] = '\\'; map[2][point+1] = '\\'; map[2][point+2] = '_';
        map[1][point-3] = '('; map[1][point-2] = 'O'; map[1][point-1] = '_'; map[1][point] = 'O'; map[1][point+1] = ')'; map[1][point+2] = '_'; map[1][point+3] = ')';
        map[0][point-2] = '0'; map[0][point] = '0'; map[0][point+2] = '0';
        break;
    case 2:
        map[3][point-1] = '_'; map[3][point] = '_';
        map[2][point-3] = '_'; map[2][point-2] = '/'; map[2][point-1] = '//'; map[2][point] = '_'; map[2][point+1] = '\\';
        map[1][point-4] = '('; map[1][point-3] = '_'; map[1][point-2] = '('; map[1][point-1] = 'O'; map[1][point] = '_'; map[1][point+1] = 'O';  map[1][point+2] = ')';
        map[0][point-3] = '0'; map[0][point-1] = '0'; map[0][point+1] = '0';
        break;
    }
}
void DrawRoad(double angle, char RandRoad[6], char map[Height][Width]){
    for(int i=Height-1;i>=0;i--){
        for(int j=0;j<Width;j++){
            if(((Width-1)/4-j)*(-(Width)/4-j) + i*i*angle < Width || !((3*(Width-2)/4-j)*(-3*(Width)/4-j) + i*i*angle <= Width))
                map[i][j] = RandRoad[rand()%6];
            else
                map[i][j] = Fill;
        }
    }
}
void Rotate(int* x,double angle){
    if(angle>1)
        (*x)++;
    if(angle<-1)
        (*x)--;
}
void Print(char map[Height][Width]){
    for(int i=Height-1;i>=0;i--){
        for(int j=0;j<Width;j++)
            printf("%2.c",map[i][j]);
        printf("\n");
    }
}
int main()
{
    char map[Height][Width];
    char RandRoad[6] = "*#+%&$";
    double TimeLine = 0;
    int Position = 0;
    int X = Width/2;
    int RoadRotate = 0;
    double phi = 0;
    while(true){
        system("cls");
        char b = ' ';
        if(kbhit()) b = getch();
        switch(b){
        case 'a':
            Position = 2;
            if(X>4)
                X--;
            break;
        case 'd':
            Position = 1;
            if(X<Width-4)
                X++;
            break;
        default:
            Position = 0; break;
        }
        memset(map,Fill,sizeof(map));
        switch((int)TimeLine%50){
        case 5:
            RoadRotate = 1; break;
        case 15:
            RoadRotate = -1; break;
        case 30:
            RoadRotate = 2; break;
        case 40:
            RoadRotate = -2; break;
        }
        switch(RoadRotate){
        case 0: break;
        case 1:
            if(phi<3.0)
                phi+=0.1;
            else
                RoadRotate = 0;
            break;
        case 2:
            if(phi>-3.0)
                phi-=0.1;
            else
                RoadRotate = 0;
            break;
        case -1:
            if(phi>0.0)
                phi-=0.1;
            else
                RoadRotate = 0;
            break;
        case -2:
            if(phi<0.0)
                phi+=0.1;
            else
                RoadRotate = 0;
            break;
        }
        Rotate(&X,phi);
        DrawRoad(phi,RandRoad,map);
        DrawCar(X, Position, map);
        Print(map);
        TimeLine+=0.1;
        printf("Time: %lf\n",TimeLine);
        if(X<3 || X>17){
            printf("GameOver!\n");
            break;
        }
        usleep(100000);
    }
    return 0;
}
