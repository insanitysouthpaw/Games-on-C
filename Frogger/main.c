#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
struct Frog{
    int y;
    int x;
};
void MoveBarriers(int barriers[18]){
    for(int i=0;i<18;i++){
        if(i%2==0){
            if(barriers[i]>10)
                barriers[i]-=10;
            barriers[i]++;
        }
        else{
            if(barriers[i]<10)
                barriers[i]+=10;
            barriers[i]--;
        }
    }
}
void Fill(char barrier[10], int barriers[18], char m[20][10]){
    for(int i=1;i<19;i++){
        for(int j=0;j<10;j++)
            m[i][j]=barrier[(j+barriers[i-1])%10];
    }
}
void Print(char m[20][10]){
    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++)
            printf("%2.c",m[i][j]);
        printf("\n");
    }
}
int main()
{
    srand(time(NULL));
    char map[20][10];
    char barrier[10] = "...*******";
    int barriers[18];
    for(int i=0;i<10;i++)
        barriers[i] = rand()%10;
    struct Frog player = {19,rand()%10};
    bool timeout = false;
    while(true){
        system("cls");
        char b = ' ';
        if(kbhit())
            b = getch();
        switch(b){
        case 'd':
            if(player.x!=9)
                player.x++;
            break;
        case 'a':
            if(player.x!=0)
                player.x--;
            break;
        case 's':
            if(player.y!=19)
                player.y++;
            break;
        case 'w':
            if(player.y!=0)
                player.y--;
            break;
        }
        if(player.y==0){
            printf("You win!");
            break;
        }
        memset(map,46,sizeof(map));
        Fill(barrier,barriers,map);
        if(map[player.y][player.x]=='*'){
            printf("Game Over!");
            break;
        }
        map[player.y][player.x] = '@';
        Print(map);
        if(timeout){
            MoveBarriers(barriers);
            timeout = false;
        }
        else
            timeout = true;
        usleep(500000);
    }
}
