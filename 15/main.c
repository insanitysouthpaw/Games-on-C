#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
void Fill(int a[4][4]){
    int t = 1;
    while(true){
        if(t==16)
            break;
        int pos = rand()%16;
        if(a[pos/4][pos%4]!=0)
            continue;
        a[pos/4][pos%4]=t;
        t++;
    }
}
void Print(int a[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            printf("%3.i",a[i][j]);
        printf("\n");
    }
}
void Find(int a[4][4],int* r,int* c){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            if(a[i][j]==0){
                *r = i;
                *c = j;
            }
    }
}
int main()
{
    srand(time(NULL));
    int arr[4][4] = {0};
    Fill(arr);
    while(!(arr[0][0]==1 && arr[0][1]==2 && arr[0][2]==3 && arr[0][3]==4
          && arr[1][0]==5 && arr[1][1]==6 && arr[1][2]==7 && arr[1][3]==8
          && arr[2][0]==9 && arr[2][1]==10 && arr[2][2]==11 && arr[2][3]==12
          && arr[3][0]==13 && arr[3][1]==14 && arr[3][2]==15))
    {
        system("cls");
        char b = ' ';
        if(kbhit()){
            b = getch();
        }
        int row,column;
        Find(arr,&row,&column);
        switch(b){
        case 'w':
            if(row==3)
                break;
            arr[row][column] = arr[row+1][column];
            arr[row+1][column] = 0;
            break;
        case 's':
            if(row==0)
                break;
            arr[row][column] = arr[row-1][column];
            arr[row-1][column] = 0;
            break;
        case 'a':
            if(column==3)
                break;
            arr[row][column] = arr[row][column+1];
            arr[row][column+1] = 0;
            break;
        case 'd':
            if(column==0)
                break;
            arr[row][column] = arr[row][column-1];
            arr[row][column-1] = 0;
            break;
        default:
            break;
        }
        Print(arr);
        usleep(500000);
    }
    printf("Congratulations, you win!\n");
}
