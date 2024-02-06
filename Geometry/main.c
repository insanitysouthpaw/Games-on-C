#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
int main()
{
    srand(time(NULL));
    char z[15][15];
    memset(z,46,sizeof(z));
    double s = 0;
    int color = 42;
    while(true){
        system("cls");
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++)
                if(((double)i-7)*((double)i-7)+((double)j-7)*((double)j-7)<s)
                    z[i][j]=color;
        }
        for(int i=0;i<15;i++){
            for(int j=0;j<15;j++)
                printf("%2.c",z[i][j]);
            printf("\n");
        }
        s+=5;
        if(s==110){
            s=0;
            color = rand()%100;
        }
        usleep(50000);
    }
    return 0;
}
