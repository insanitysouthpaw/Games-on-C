#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <strings.h>
#define s 127
int main()
{
    while(true){
        system("cls");
        char display[7][29];
        memset(display,46,sizeof(display));
        display[1][9] = s; display[1][19] = s;
        display[5][9] = s; display[5][19] = s;
        time_t t = time(NULL);
        int sec = t%60;
        int min = t/60%60;
        int hours = (t/3600+5)%24;
        for(int i=0;i<=6;i++){
            int n; int v;
            if(i==0){n = 1; v = hours/10%10;} if(i==1){n = 5; v = hours%10;}
            if(i==2){n = 11; v = min/10%10;} if(i==5){n = 15; v = min%10;}
            if(i==4){n = 21; v = sec/10%10;} if(i==6){n = 25; v = sec%10;}
            if(v==0){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n]=s; display[2][n+2]=s; display[3][n]=s; display[3][n+2]=s; display[4][n]=s; display[4][n+2]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==1){
                display[1][n+1]=s; display[2][n]=s; display[2][n+1]=s; display[3][n+1]=s; display[4][n+1]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==2){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n+2]=s; display[3][n+1]=s; display[4][n]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==3){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n+2]=s; display[3][n+1]=s; display[4][n+2]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==4){
                display[1][n]=s; display[1][n+2]=s;
                display[2][n]=s; display[2][n+2]=s;
                for(int k=n;k<n+3;k++) display[3][k]=s;
                display[4][n+2]=s; display[5][n+2]=s;
            }
            if(v==5){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n]=s; display[3][n+1]=s; display[4][n+2]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==6){
                display[1][n+1]=s; display[2][n]=s;
                for(int k=n;k<n+3;k++) display[3][k]=s;
                display[4][n]=s; display[4][n+2]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==7){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n+2]=s; display[3][n+2]=s; display[4][n+1]=s; display[5][n]=s;
            }
            if(v==8){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n]=s; display[2][n+2]=s;
                for(int k=n;k<n+3;k++) display[3][k]=s;
                display[4][n]=s; display[4][n+2]=s;
                for(int k=n;k<n+3;k++) display[5][k]=s;
            }
            if(v==9){
                for(int k=n;k<n+3;k++) display[1][k]=s;
                display[2][n]=s; display[2][n+2]=s;
                for(int k=n;k<n+3;k++) display[3][k]=s;
                display[4][n+2]=s; display[5][n+1]=s;
            }
        }
        printf("hour: %i min: %i sec: %i\n",hours,min,sec);
        for(int i=0;i<7;i++){
            for(int j=0;j<29;j++)
                printf("%c",display[i][j]);
            printf("\n");
        }
        usleep(100000);
    }
    return 0;
}
