#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <conio.h>
bool AddNumber(int arr[4][4]){
    int FullyFilled = 0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            if(arr[i][j] == 0)
                FullyFilled++;
    }
    if(FullyFilled == 0)
        return false;
    else{
        while(true){
            int Y = rand()%4;
            int X = rand()%4;
            if(arr[Y][X] == 0){
                arr[Y][X] = 2;
                break;
            }
        }
        return true;
    }
}
void Print(int map[4][4]){
    for(int i=0;i<4;i++){
        printf("----------------------------\n");
        for(int j=0;j<4;j++)
            printf("|%5.i|",map[i][j]);
        printf("\n");
    }
    printf("----------------------------\n");
}
void Move(char Button,int arr[4][4]){
    switch(Button){
    case 'a':
        for(int i=0;i<4;i++){
            int notNullElements = 0;
            for(int n=0;n<4;n++){
                if(arr[i][n]!=0)
                    notNullElements++;
            }
            for(int n=0;n<notNullElements;n++){
                while(arr[i][n]==0){
                    for(int k=n;k<3;k++){
                        arr[i][k] = arr[i][k+1];
                    }
                    arr[i][3] = 0;
                }
            }
            for(int s=0;s<4;s++){
                if(arr[i][s]==arr[i][s+1]){
                    arr[i][s] += arr[i][s+1];
                    for(int k=s+1;k<3;k++){
                        arr[i][k] = arr[i][k+1];
                    }
                    arr[i][3] = 0;
                }
            }
        }
        break;
    case 'd':
        for(int i=0;i<4;i++){
            int notNullElements = 0;
            for(int n=0;n<4;n++){
                if(arr[i][n]!=0)
                    notNullElements++;
            }
            for(int n=0;n<notNullElements;n++){
                while(arr[i][3-n]==0){
                    for(int k=3-n;k>0;k--){
                        arr[i][k] = arr[i][k-1];
                    }
                    arr[i][0] = 0;
                }
            }
            for(int s=3;s>0;s--){
                if(arr[i][s]==arr[i][s-1]){
                    arr[i][s] += arr[i][s-1];
                    for(int k=s-1;k>0;k--){
                        arr[i][k] = arr[i][k-1];
                    }
                    arr[i][0] = 0;
                }
            }
        }
        break;
    case 'w':
        for(int i=0;i<4;i++){
            int notNullElements = 0;
            for(int n=0;n<4;n++){
                if(arr[n][i]!=0)
                    notNullElements++;
            }
            for(int n=0;n<notNullElements;n++){
                while(arr[n][i]==0){
                    for(int k=n;k<3;k++){
                        arr[k][i] = arr[k+1][i];
                    }
                    arr[3][i] = 0;
                }
            }
            for(int s=0;s<4;s++){
                if(arr[s][i]==arr[s+1][i]){
                    arr[s][i] += arr[s+1][i];
                    for(int k=s+1;k<3;k++){
                        arr[k][i] = arr[k+1][i];
                    }
                    arr[3][i] = 0;
                }
            }
        }
        break;
    case 's':
        for(int i=0;i<4;i++){
            int notNullElements = 0;
            for(int n=0;n<4;n++){
                if(arr[n][i]!=0)
                    notNullElements++;
            }
            for(int n=0;n<notNullElements;n++){
                while(arr[3-n][i]==0){
                    for(int k=3-n;k>0;k--){
                        arr[k][i] = arr[k-1][i];
                    }
                    arr[0][i] = 0;
                }
            }
            for(int s=3;s>0;s--){
                if(arr[s][i]==arr[s-1][i]){
                    arr[s][i] += arr[s-1][i];
                    for(int k=s-1;k>0;k--){
                        arr[k][i] = arr[k-1][i];
                    }
                    arr[0][i] = 0;
                }
            }
        }
        break;
    }
}
bool Check2048(int arr[4][4]){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++)
            if(arr[i][j] == 2048)
                return true;
    }
    return false;
}
int main()
{
    srand(time(NULL));
    int arr[4][4] = {0};
    AddNumber(arr);
    Print(arr);
    bool GameWin = false;
    while(true){
        char button = ' ';
        if(kbhit()){
            button = getch();
        }
        system("cls");
        if(button=='a' || button=='d' || button=='w' || button=='s'){
            Move(button,arr);
            if(!AddNumber(arr))
                break;
        }
        if(Check2048(arr)){
            GameWin = true;
            break;
        }
        Print(arr);
        usleep(10000);
    }
    Print(arr);
    if(GameWin)
        printf("You win!\n");
    else
        printf("Game Over\n");
}
