#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#include <math.h>
#define BLOCK 42
#define FILL 46
void FillArr(int arr[][3], int length){
    for(int i=0;i<length;i++)
        for(int j=0;j<3;j++)
            arr[i][j] = 0;
    for(int i=0;i<length;i++)
         arr[i][0] = length - i;
}
void Print(int arr[][3], int length){
    for(int i=length-1;i>=0;i--){
        for(int j=0;j<3;j++){
            for(int k=0;k<length*2-1;k++){
                if(abs(k-(length*2-1)/2)>=arr[i][j])
                    printf("%c",FILL);
                else
                    printf("%c",BLOCK);
            }
            printf(" ");
        }
        printf("\n");
    }
}
void step(int arr[][3], int length, int step1, int step2){
    int index1 = -1;
    int index2 = -1;
    for(int i=length-1;i>=0;i--){
        if(arr[i][step1]!=0){
            index1 = i;
            break;
        }
    }
    for(int i=length-1;i>=0;i--){
        if(arr[i][step2]!=0){
            index2 = i;
            break;
        }
    }
    if(index1 == -1 && index2 == -1){
        return;
    }
    else if(index1 == -1){
        arr[0][step1] = arr[index2][step2];
        arr[index2][step2] = 0;
    }
    else if(index2 == -1){
        arr[0][step2] = arr[index1][step1];
        arr[index1][step1] = 0;
    }
    else if(arr[index1][step1] > arr[index2][step2]){
        arr[index1+1][step1] = arr[index2][step2];
        arr[index2][step2] = 0;
    }
    else {
        arr[index2+1][step2] = arr[index1][step1];
        arr[index1][step1] = 0;
    }
}
bool DrawArr(int arr[][3], int length, int speed, int End, int StepsLeft){
    usleep(speed);
    system("cls");
    Print(arr, length);
    printf("Steps left: %i\n", StepsLeft);
    int Sum = 0;
    for(int k=0;k<length;k++)
        Sum += arr[k][2];
    if(Sum == End)
        return true;
    else return false;
}
void Algorithm(int arr[][3], int length, int speed){
    int End = 0;
    for(int i=0;i<length;i++){
        End += arr[i][0];
    }
    int StepsLeft = pow(2, length) - 1;
    DrawArr(arr, length, speed, End, StepsLeft);
    while(true){
        if(length%2==0){
            step(arr, length, 0, 1); StepsLeft--;
            if(DrawArr(arr, length, speed, End, StepsLeft))
                break;
            step(arr, length, 0, 2); StepsLeft--;
            if(DrawArr(arr, length, speed, End, StepsLeft))
                break;
        }
        else{
            step(arr, length, 0, 2); StepsLeft--;
            if(DrawArr(arr, length, speed, End, StepsLeft))
                break;
            step(arr, length, 0, 1); StepsLeft--;
            if(DrawArr(arr, length, speed, End, StepsLeft))
                break;
        }
        step(arr, length, 1, 2); StepsLeft--;
        if(DrawArr(arr, length, speed, End, StepsLeft))
            break;
    }
}
int main()
{
    int n;
    int speed;
    printf("Enter the height of the tower: ");
    scanf("%i",&n);
    printf("Enter the speed: ");
    scanf("%i",&speed);
    int arr[n][3];
    FillArr(arr, n);
    Algorithm(arr, n, speed);
}
