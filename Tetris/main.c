#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#define BLOCK 15
#define FILL 46
struct Figure{
    int Y1; int X1;
    int Y2; int X2;
    int Y3; int X3;
    int Y4; int X4;
    int Type;
    int Position;
};
void RandFigure(struct Figure *figure){
    int RandNumber = rand()%7;
    figure->Position = 0;
    switch(RandNumber){
    case 0:
        figure->Y1 = 0;
        figure->X1 = 4;
        figure->Y2 = 0;
        figure->X2 = 5;
        figure->Y3 = 1;
        figure->X3 = 4;
        figure->Y4 = 1;
        figure->X4 = 5;
        figure->Type = 0;
        break;
    case 1:
        figure->Y1 = 0;
        figure->X1 = 3;
        figure->Y2 = 0;
        figure->X2 = 4;
        figure->Y3 = 0;
        figure->X3 = 5;
        figure->Y4 = 0;
        figure->X4 = 6;
        figure->Type = 1;
        break;
    case 2:
        figure->Y1 = 0;
        figure->X1 = 4;
        figure->Y2 = 1;
        figure->X2 = 4;
        figure->Y3 = 2;
        figure->X3 = 4;
        figure->Y4 = 1;
        figure->X4 = 5;
        figure->Type = 2;
        break;
    case 3:
        figure->Y1 = 0;
        figure->X1 = 4;
        figure->Y2 = 1;
        figure->X2 = 4;
        figure->Y3 = 2;
        figure->X3 = 4;
        figure->Y4 = 2;
        figure->X4 = 5;
        figure->Type = 3;
        break;
    case 4:
        figure->Y1 = 0;
        figure->X1 = 5;
        figure->Y2 = 1;
        figure->X2 = 5;
        figure->Y3 = 2;
        figure->X3 = 5;
        figure->Y4 = 2;
        figure->X4 = 4;
        figure->Type = 4;
        break;
    case 5:
        figure->Y1 = 0;
        figure->X1 = 4;
        figure->Y2 = 1;
        figure->X2 = 4;
        figure->Y3 = 1;
        figure->X3 = 5;
        figure->Y4 = 2;
        figure->X4 = 5;
        figure->Type = 5;
        break;
    case 6:
        figure->Y1 = 0;
        figure->X1 = 5;
        figure->Y2 = 1;
        figure->X2 = 5;
        figure->Y3 = 1;
        figure->X3 = 4;
        figure->Y4 = 2;
        figure->X4 = 4;
        figure->Type = 6;
        break;
    }
}
void MoveFigure(struct Figure *figure, char map[20][10],bool *move){
    if(figure->Y1+1<20
       && map[figure->Y1+1][figure->X1] == FILL
       && figure->Y2+1<20
       && map[figure->Y2+1][figure->X2] == FILL
       && figure->Y3+1<20
       && map[figure->Y3+1][figure->X3] == FILL
       && figure->Y4+1<20
       && map[figure->Y4+1][figure->X4] == FILL){
        figure->Y1++;
        figure->Y2++;
        figure->Y3++;
        figure->Y4++;
    }
    else
        *move = true;
}
void DrawFigure(struct Figure *figure, char map[20][10]){
    map[figure->Y1][figure->X1] = BLOCK;
    map[figure->Y2][figure->X2] = BLOCK;
    map[figure->Y3][figure->X3] = BLOCK;
    map[figure->Y4][figure->X4] = BLOCK;
}
void Control(char button, struct Figure *figure, char map[20][10], char realmap[20][10]){
    switch(button){
        case 'a':
            if(figure->X1-1>=0
               && map[figure->Y1][figure->X1-1] == FILL
               && figure->X2-1>=0
               && map[figure->Y2][figure->X2-1] == FILL
               && figure->X3-1>=0
               && map[figure->Y3][figure->X3-1] == FILL
               && figure->X4-1>=0
               && map[figure->Y4][figure->X4-1] == FILL){
                figure->X1--;
                figure->X2--;
                figure->X3--;
                figure->X4--;
            }
            break;
        case 'd':
               if(figure->X1+1<10
               && map[figure->Y1][figure->X1+1] == FILL
               && figure->X2+1<10
               && map[figure->Y2][figure->X2+1] == FILL
               && figure->X3+1<10
               && map[figure->Y3][figure->X3+1] == FILL
               && figure->X4+1<10
               && map[figure->Y4][figure->X4+1] == FILL){
                figure->X1++;
                figure->X2++;
                figure->X3++;
                figure->X4++;
            }
            break;
        case ' ':
            switch(figure->Type){
            case 0:
                break;
            case 1:
                switch(figure->Position){
                case 0:
                    if(
                       realmap[figure->Y1-2][figure->X1]==FILL && realmap[figure->Y2-2][figure->X2]==FILL && realmap[figure->Y3-2][figure->X3]==FILL && realmap[figure->Y4-2][figure->X4]==FILL &&
                       realmap[figure->Y1-1][figure->X1-1]==FILL && realmap[figure->Y2-1][figure->X2-1]==FILL && realmap[figure->Y3-1][figure->X3]==FILL && realmap[figure->Y4-1][figure->X4]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y4][figure->X4]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y3+1][figure->X3]==FILL && realmap[figure->Y4+1][figure->X4]==FILL) {
                        figure->Y1 = figure->Y4-2;  figure->X1 = figure->X2;
                        figure->Y2 = figure->Y4-1; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y4; figure->X3 = figure->X2;
                        figure->Y4 = figure->Y4+1; figure->X4 = figure->X2;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 1:
                    if( figure->X1>0 && figure->X1<8 &&
                       realmap[figure->Y1][figure->X1-1]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y1][figure->X3+1]==FILL && realmap[figure->Y1][figure->X1+2]==FILL &&
                       realmap[figure->Y2][figure->X2-1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y2][figure->X3+1]==FILL && realmap[figure->Y2][figure->X2+2]==FILL &&
                       realmap[figure->Y3][figure->X3-1]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y3][figure->X3+1]==FILL && realmap[figure->Y3][figure->X3+2]==FILL &&
                       realmap[figure->Y4][figure->X4-1]==FILL && realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y4][figure->X3+1]==FILL && realmap[figure->Y4][figure->X4+2]==FILL) {
                        figure->Y1 = figure->Y3;  figure->X1 = figure->X4-1;
                        figure->Y2 = figure->Y3; figure->X2 = figure->X4;
                        figure->Y3 = figure->Y3; figure->X3 = figure->X4+1;
                        figure->Y4 = figure->Y3; figure->X4 = figure->X4+2;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 2:
                    if( figure->X1>1 && figure->X1<9 &&
                       realmap[figure->Y1-2][figure->X1]==FILL && realmap[figure->Y2-2][figure->X2]==FILL && realmap[figure->Y3-2][figure->X3]==FILL && realmap[figure->Y4-2][figure->X4]==FILL &&
                       realmap[figure->Y1-1][figure->X1-1]==FILL && realmap[figure->Y2-1][figure->X2-1]==FILL && realmap[figure->Y3-1][figure->X3]==FILL && realmap[figure->Y4-1][figure->X4]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y4][figure->X4]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y3+1][figure->X3]==FILL && realmap[figure->Y4+1][figure->X4]==FILL) {
                        figure->Y1 = figure->Y4-2;  figure->X1 = figure->X3;
                        figure->Y2 = figure->Y4-1; figure->X2 = figure->X3;
                        figure->Y3 = figure->Y4; figure->X3 = figure->X3;
                        figure->Y4 = figure->Y4+1; figure->X4 = figure->X3;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 3:
                    if(
                       realmap[figure->Y1][figure->X1-2]==FILL && realmap[figure->Y1-1][figure->X1]==FILL && realmap[figure->Y1][figure->X3]==FILL && realmap[figure->Y1][figure->X1+1]==FILL &&
                       realmap[figure->Y2][figure->X2-2]==FILL && realmap[figure->Y2-1][figure->X2]==FILL && realmap[figure->Y2][figure->X3]==FILL && realmap[figure->Y2][figure->X2+1]==FILL &&
                       realmap[figure->Y3][figure->X3-2]==FILL && realmap[figure->Y3-1][figure->X3]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y3][figure->X3+1]==FILL &&
                       realmap[figure->Y4][figure->X4-2]==FILL && realmap[figure->Y4-1][figure->X4]==FILL && realmap[figure->Y4][figure->X3]==FILL && realmap[figure->Y4][figure->X4+1]==FILL) {
                        figure->Y1 = figure->Y3;  figure->X1 = figure->X4-2;
                        figure->Y2 = figure->Y3; figure->X2 = figure->X4-1;
                        figure->Y3 = figure->Y3; figure->X3 = figure->X4;
                        figure->Y4 = figure->Y3; figure->X4 = figure->X4+1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                }
                break;
            case 2:
                switch(figure->Position){
                case 0:
                    if( figure->X2 > 0 &&
                       realmap[figure->Y1-1][figure->X1-1]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y4-1][figure->X4]==FILL &&
                       realmap[figure->Y1][figure->X2-1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y4][figure->X4]==FILL &&
                       realmap[figure->Y1+1][figure->X3-1]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y4+1][figure->X4]==FILL){
                        figure->Y1 = figure->Y2;  figure->X1 = figure->X2-1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y3; figure->X3 = figure->X3;
                        figure->Y4 = figure->Y4; figure->X4 = figure->X4;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 1:
                    if(
                       realmap[figure->Y1-1][figure->X1]==FILL && realmap[figure->Y2-1][figure->X2]==FILL && realmap[figure->Y4-1][figure->X4]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y4][figure->X4]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y4+1][figure->X4]==FILL){
                        figure->Y1 = figure->Y1;  figure->X1 = figure->X1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y3; figure->X3 = figure->X3;
                        figure->Y4 = figure->Y2-1; figure->X4 = figure->X2;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 2:
                    if( figure->X2 < 9 &&
                       realmap[figure->Y1-1][figure->X1]==FILL && realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y4][figure->X4+1]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y2][figure->X2+1]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y3][figure->X3+1]==FILL){
                        figure->Y1 = figure->Y1;  figure->X1 = figure->X1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2; figure->X3 = figure->X2+1;
                        figure->Y4 = figure->Y4; figure->X4 = figure->X4;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 3:
                    if(
                       realmap[figure->Y1-1][figure->X1]==FILL && realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y3-1][figure->X3]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y3+1][figure->X3]==FILL){
                        figure->Y1 = figure->Y2-1;  figure->X1 = figure->X2;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2+1; figure->X3 = figure->X2;
                        figure->Y4 = figure->Y2; figure->X4 = figure->X2+1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                }
                break;
            case 3:
                switch(figure->Position){
                case 0:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y1-1][figure->X1-1]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y4-2][figure->X4]==FILL &&
                       realmap[figure->Y1][figure->X2-1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y4-1][figure->X4]==FILL &&
                       realmap[figure->Y1+1][figure->X3-1]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y4][figure->X4]==FILL){
                        figure->Y1 = figure->Y2;  figure->X1 = figure->X2+1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2; figure->X3 = figure->X2-1;
                        figure->Y4 = figure->Y2+1; figure->X4 = figure->X2-1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 1:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y3-1][figure->X3]==FILL && realmap[figure->Y2-1][figure->X2]==FILL && realmap[figure->Y1-1][figure->X4]==FILL &&
                       realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y1][figure->X1]==FILL &&
                       realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y1+1][figure->X4]==FILL){
                        figure->Y1 = figure->Y2+1;  figure->X1 = figure->X2;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2-1; figure->X3 = figure->X2;
                        figure->Y4 = figure->Y2-1; figure->X4 = figure->X2-1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 2:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y1][figure->X3-1]==FILL &&
                       realmap[figure->Y4+1][figure->X4]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y2][figure->X3-1]==FILL &&
                       realmap[figure->Y4+2][figure->X4]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y3][figure->X3-1]==FILL){
                        figure->Y1 = figure->Y2;  figure->X1 = figure->X2-1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2; figure->X3 = figure->X2+1;
                        figure->Y4 = figure->Y2-1; figure->X4 = figure->X2+1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 3:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y1-1][figure->X1]==FILL && realmap[figure->Y2-1][figure->X2]==FILL && realmap[figure->Y4][figure->X4]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y3+1][figure->X3]==FILL){
                        figure->Y1 = figure->Y2-1;  figure->X1 = figure->X2;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2+1; figure->X3 = figure->X2;
                        figure->Y4 = figure->Y2+1; figure->X4 = figure->X2+1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                }
                break;
            case 4:
                switch(figure->Position){
                case 0:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y1-1][figure->X1-1]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y1][figure->X1+1]==FILL &&
                       realmap[figure->Y1][figure->X2-1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y2][figure->X2+1]==FILL &&
                       realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y3][figure->X3+1]==FILL){
                        figure->Y1 = figure->Y2;  figure->X1 = figure->X2+1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2; figure->X3 = figure->X2-1;
                        figure->Y4 = figure->Y2-1; figure->X4 = figure->X2-1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 1:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y2-1][figure->X2]==FILL && realmap[figure->Y2-1][figure->X2+1]==FILL &&
                       realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y1][figure->X1]==FILL &&
                       realmap[figure->Y2+1][figure->X2-1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y2+1][figure->X2+1]==FILL){
                        figure->Y1 = figure->Y2+1;  figure->X1 = figure->X2;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2-1; figure->X3 = figure->X2;
                        figure->Y4 = figure->Y2-1; figure->X4 = figure->X2+1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 2:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y2+1][figure->X2-1]==FILL && realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y4][figure->X4]==FILL &&
                       realmap[figure->Y2][figure->X2-1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y4+1][figure->X4]==FILL &&
                       realmap[figure->Y2+1][figure->X2-1]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y4+2][figure->X4]==FILL){
                        figure->Y1 = figure->Y2;  figure->X1 = figure->X2-1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2; figure->X3 = figure->X2+1;
                        figure->Y4 = figure->Y2+1; figure->X4 = figure->X2+1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                case 3:
                    if( figure->X2 < 9 && figure->X2 > 0 &&
                       realmap[figure->Y2-1][figure->X2-1]==FILL && realmap[figure->Y2-1][figure->X2]==FILL && realmap[figure->Y2-1][figure->X2+1]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL &&
                       realmap[figure->Y2+1][figure->X2-1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y4][figure->X4]==FILL){
                        figure->Y1 = figure->Y2-1;  figure->X1 = figure->X2;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y2+1; figure->X3 = figure->X2;
                        figure->Y4 = figure->Y2+1; figure->X4 = figure->X2-1;
                        figure->Position = (figure->Position+1)%4;
                    }
                    break;
                }
                break;
            case 5:
                switch(figure->Position){
                case 0:
                    if( figure->X2 > 0 && figure->X2 < 9 &&
                       realmap[figure->Y1][figure->X1-1]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y3-1][figure->X3]==FILL &&
                       realmap[figure->Y2][figure->X2-1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL &&
                       realmap[figure->Y2+1][figure->X2-1]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y4][figure->X4]==FILL){
                        figure->Y1 = figure->Y2+1;  figure->X1 = figure->X2-1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y3; figure->X3 = figure->X3;
                        figure->Y4 = figure->Y2+1; figure->X4 = figure->X2;
                        figure->Position = (figure->Position+1)%2;
                    }
                    break;
                case 1:
                    if( figure->X2 > 0 && figure->X2 < 9 &&
                       realmap[figure->Y1-1][figure->X1]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y3][figure->X3]==FILL &&
                       realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y3+1][figure->X3]==FILL &&
                       realmap[figure->Y1+1][figure->X1]==FILL && realmap[figure->Y4+1][figure->X4]==FILL && realmap[figure->Y3+2][figure->X3]==FILL){
                        figure->Y1 = figure->Y4-1;  figure->X1 = figure->X4;
                        figure->Y2 = figure->Y4; figure->X2 = figure->X4;
                        figure->Y3 = figure->Y4; figure->X3 = figure->X4+1;
                        figure->Y4 = figure->Y3+1; figure->X4 = figure->X3;
                        figure->Position = (figure->Position+1)%2;
                    }
                    break;
                }
                break;
            case 6:
                switch(figure->Position){
                case 0:
                    if( figure->X2 > 0 && figure->X2 < 9 &&
                       realmap[figure->Y3-1][figure->X3]==FILL && realmap[figure->Y1][figure->X1]==FILL && realmap[figure->Y1][figure->X2+1]==FILL &&
                       realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y2][figure->X2+1]==FILL &&
                       realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y2+1][figure->X2]==FILL && realmap[figure->Y4][figure->X2+1]==FILL){
                        figure->Y1 = figure->Y2+1;  figure->X1 = figure->X2+1;
                        figure->Y2 = figure->Y2; figure->X2 = figure->X2;
                        figure->Y3 = figure->Y3; figure->X3 = figure->X3;
                        figure->Y4 = figure->Y2+1; figure->X4 = figure->X2;
                        figure->Position = (figure->Position+1)%2;
                    }
                    break;
                case 1:
                    if( figure->X2 > 0 && figure->X2 < 9 &&
                       realmap[figure->Y3][figure->X3]==FILL && realmap[figure->Y2][figure->X2]==FILL && realmap[figure->Y1-1][figure->X1]==FILL &&
                       realmap[figure->Y3+1][figure->X3]==FILL && realmap[figure->Y4][figure->X4]==FILL && realmap[figure->Y1][figure->X1]==FILL &&
                       realmap[figure->Y3+2][figure->X3]==FILL && realmap[figure->Y4+1][figure->X4]==FILL && realmap[figure->Y1+1][figure->X1]==FILL){
                        figure->Y1 = figure->Y4-1;  figure->X1 = figure->X4;
                        figure->Y2 = figure->Y4; figure->X2 = figure->X4;
                        figure->Y3 = figure->Y4; figure->X3 = figure->X4-1;
                        figure->Y4 = figure->Y3+1; figure->X4 = figure->X3;
                        figure->Position = (figure->Position+1)%2;
                    }
                    break;
                }
                break;
            }
    }
}
int Line(char map[20][10]){
    int Lines = 0;
    for(int i=0;i<20;i++){
        int CheckLine = 0;
        for(int j=0;j<10;j++){
            if(map[i][j] == BLOCK)
                CheckLine++;
        }
        if(CheckLine==10){
            for(int k=i;k>0;k--){
                for(int r=0;r<10;r++){
                    map[k][r] = map[k-1][r];
                }
            }
            for(int r=0;r<10;r++){
                map[0][r] = FILL;
            }
            Lines++;
        }
    }
    return Lines;
}
void Print(char map[20][10],int Points){
    const int SIDES = 42;
    for(int j=0;j<10+2;j++)
        printf("%2.c",SIDES);
    printf("\n");
    for(int i=0;i<20;i++){
        printf("%2.c",SIDES);
        for(int j=0;j<10;j++)
            printf("%2.c",map[i][j]);
        printf("%2.c\n",SIDES);
    }
    for(int j=0;j<10+2;j++)
        printf("%2.c",SIDES);
    printf("\nLines : %i",Points);
}
int main()
{
    srand(time(NULL));
    char map[20][10];
    memset(map,FILL,sizeof(map));
    struct Figure CurrentFigure;
    RandFigure(&CurrentFigure);
    bool Move = false;
    int Points = 0;
    while(true){
        system("cls");
        char tmp[20][10];
        if(Move){
            DrawFigure(&CurrentFigure,map);
            RandFigure(&CurrentFigure);
            Move = false;
        }
        memcpy(tmp,map,sizeof(map));
        char Button = 'q';
        if(kbhit())
            Button = getch();
        Control(Button,&CurrentFigure,tmp,map);
        MoveFigure(&CurrentFigure,tmp,&Move);
        Points += Line(map);
        DrawFigure(&CurrentFigure,tmp);
        Print(tmp,Points);
        usleep(250000);
    }
}
