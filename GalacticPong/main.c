#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#include <time.h>
#define size 10
#define pointsrows 3
struct ball{
    int row;
    int column;
    char type;
    char direction;
};
struct pong{
    int row;
    int column1;
    int column2;
    char type;
};
struct point{
    int row;
    int column;
    char type;
    bool life;
};
int main()
{
    srand(time(NULL));
    bool game = true;
    struct pong player = {size-2,size/2-1,size/2,'_'};
    struct point points[size*pointsrows];
    for(int i=0;i<pointsrows;i++){
        for(int j=0;j<size;j++){
            points[i*size+j].row = i;
            points[i*size+j].column = j;
            points[i*size+j].type = 42;
            points[i*size+j].life = true;
        }
    }
    char randorb[4]={'z','c'};
    struct ball orb = {3,1+rand()%(size-2),'@',randorb[rand()%2]};

    char map[size][size];
    memset(map,46,sizeof(map));
    map[player.row][player.column1] = player.type;
    map[player.row][player.column2] = player.type;

    for(int i=0;i<size*pointsrows;i++)
        if(points[i].life)
            map[points[i].row][points[i].column] = points[i].type;
    map[orb.row][orb.column] = orb.type;

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    printf("Press any key\n");
    getch();
    bool ending = true;
    while(game){
        if(orb.row==size){
            ending = false;
            game = false;
            break;
        }
        char b = 0;
        system("cls");
        if(kbhit())
            b = getch();
        switch(b){
        case 'a':
            if(player.column1!=0){
                player.column1--;
                player.column2--;
            }
            break;
        case 'd':
            if(player.column2!=size-1){
                player.column1++;
                player.column2++;
            }
            break;
        default:
            break;
        }

        switch(orb.direction){
        case 'q':
            if(orb.row==0){
                orb.direction = 'z';
                break;
            }
            if(orb.column==0){
                orb.direction = 'e';
                break;
            }
            orb.row--;
            orb.column--;
            break;
        case 'e':
            if(orb.row==0){
                orb.direction = 'c';
                break;
            }
            if(orb.column==size-1){
                orb.direction = 'q';
                break;
            }
            orb.row--;
            orb.column++;
            break;
        case 'z':
            if(orb.row==player.row && (orb.column==player.column1 || orb.column==player.column2)){
                if(orb.column!=0 && orb.row==player.row && orb.column==player.column2)
                    orb.column--;
                orb.direction = 'q';
                break;
            }
            if(orb.column==0){
                orb.direction = 'c';
                break;
            }
            orb.row++;
            orb.column--;
            break;
        case 'c':
            if(orb.row==player.row && (orb.column==player.column1 || orb.column==player.column2)){
                if(orb.column!=size-1 && orb.row==player.row && orb.column==player.column1)
                    orb.column++;
                orb.direction = 'e';
                break;
            }
            if(orb.column==size-1){
                orb.direction = 'z';
                break;
            }
            orb.row++;
            orb.column++;
            break;
        default:
            break;
        }

        char map[size][size];
        memset(map,46,sizeof(map));

        for(int i=0;i<size*pointsrows;i++)
            if(points[i].row==orb.row && points[i].column==orb.column)
                points[i].life=false;

        map[player.row][player.column1] = player.type;
        map[player.row][player.column2] = player.type;

        for(int i=0;i<size*pointsrows;i++)
            if(points[i].life)
                map[points[i].row][points[i].column] = points[i].type;
        map[orb.row][orb.column] = orb.type;

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++)
                printf("%c",map[i][j]);
            printf("\n");
        }
        int left = size*pointsrows;
        for(int i=0;i<size*pointsrows;i++)
            if(!points[i].life)
                left--;
        if(left == 0){
            game = false;
            break;
        }
        printf("Direction : %c\nPoints left : %i",orb.direction, left);
        usleep(250000);
    }
    if(ending){
        printf("\nCongratulations, you've won!\n");
    }
    else {
        printf("\nYou've lost...\n");
    }
}
