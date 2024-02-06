#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <unistd.h>
#define size 15
struct player{
    int x;
    int y;
    char type;
};
int main()
{
    char map[size][size];
    memset(map,46,sizeof(map));
    struct player igrok = {0,0,'@'};
    bool prepare = true;
    while(prepare){
        char b = 0;
        char tmp[size][size];
        memcpy(tmp,map,sizeof(map));
        tmp[igrok.x][igrok.y]=igrok.type;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++)
                printf("%c",tmp[i][j]);
            printf("\n");
        }
        if(kbhit())
            b = getch();
        usleep(100000);
        system("cls");
        switch(b){
        case 'w':
            if(igrok.x!=0)
                igrok.x--;
            break;
        case 's':
            if(igrok.x!=size-1)
                igrok.x++;
            break;
        case 'a':
            if(igrok.y!=0)
                igrok.y--;
            break;
        case 'd':
            if(igrok.y!=size-1)
                igrok.y++;
            break;
        case ' ':
            map[igrok.x][igrok.y]=42;
            break;
        case 'q':
            prepare = false;
            break;
        default:
            break;
        }
    }
    system("cls");
    while(true){
        usleep(100000);
        system("cls");
        char tmp[size][size];
        memcpy(tmp,map,sizeof(map));

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                int colvo = 0;
                for(int k = i-1;k <= i+1; k++){
                    for(int l = j-1;l <= j+1; l++){
                        if((i!=k || j!=l) && k>=0 && k<size && l>=0 && l<size && tmp[k][l]==42)
                            colvo++;
                    }
                }
                if(tmp[i][j]==46){
                    if(colvo==3)
                        map[i][j]=42;
                }

                if(tmp[i][j]==42){
                    if(colvo<2 || colvo>3)
                        map[i][j]=46;
                }
            }
        }

        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++)
                printf("%c",map[i][j]);
            printf("\n");
        }
    }
    return 0;

}
