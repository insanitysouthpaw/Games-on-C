#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
int main()
{
    char t[3][3];
    bool XO;
    int moves = 0;
    memset(t,46,sizeof(t));
    char f;
    while(true){
    printf("Choose who goes first, X or O: ");
    f = getchar();
    if(f=='X' || f=='O') break;
    else system("cls"); printf("Incorrect input\n");}
    if(f=='X') XO = true;
    else XO = false;
    char p;
    system("cls");
    while(true){
        int x,y;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                printf("%c",t[i][j]);
            printf("\n");
        }
        if(XO) {p='X'; printf("X chooses a move\nEnter a row and a column\n");}
        else {p='O'; printf("O chooses a move\nEnter a row and a column\n");}
        printf("Moves: %i\n",moves);
        scanf("%i %i",&x,&y); x--; y--;

        if(!(x>=0 && x<=2 && y>=0 && y<=2) || t[x][y]!=46){
            system("cls");
            printf("Incorrect input\n");
            continue;
        }

        t[x][y]=p;
        if(t[0][0]==p && t[0][1]==p && t[0][0]==p && t[0][2]==p
           || t[1][0]==p && t[1][1]==p && t[1][0]==p && t[1][2]==p
           || t[2][0]==p && t[2][1]==p && t[2][0]==p && t[2][2]==p
           || t[0][0]==p && t[1][0]==p && t[2][0]==p && t[1][0]==p
           || t[0][1]==p && t[1][1]==p && t[2][1]==p && t[1][1]==p
           || t[0][2]==p && t[1][2]==p && t[2][2]==p && t[1][2]==p
           || t[0][0]==p && t[1][1]==p && t[2][2]==p && t[1][1]==p
           || t[0][2]==p && t[1][1]==p && t[2][0]==p && t[1][1]==p)
            break;

        if(XO) XO = false;
        else XO = true;
        moves++;
        if(moves==9) break;
        system("cls");
    }
    system("cls");
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            printf("%c",t[i][j]);
        printf("\n");
    }
    if(moves!=9) printf("%c won!\n",p);
    else printf("Draw!\n",p);
}
