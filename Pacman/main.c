#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <unistd.h>

struct figure {
        int x;
        int y;
        bool life;
        int type;
    };

int main()
{
    char z[10][10] = {"..........",".***..***.",".*......*.",".*.*..*.*.","...*..*...","...*..*...",".*.*..*.*.",".*......*.",".***..***.",".........."};

    bool work = true, correct = false, sleep = false;
    int points = 100;
    char button;
    struct figure hero = {0, 0+rand()%10,true,2};
    struct figure enemy = {9, 0+rand()%10,true,1};
    struct figure Points[100];

    z[hero.x][hero.y]=hero.type;
    z[enemy.x][enemy.y]=enemy.type;

    for (int i = 0;i < 10;i++){
            for(int j = 0;j < 10;j++){
                printf("%c",z[i][j]);
            }
            printf("\n");
        }
    printf("Hunter hunting\n");

    int lx = 0,ly = 0;
    for(int i=0;i<100;i++){
        Points[i].x = lx;
        Points[i].y = ly;
        Points[i].life = true;
        Points[i].type = 44;
        if(z[lx][ly]=='*'){
            Points[i].life=false;
            points--;
        }
        lx++;
        if(lx==10){
            lx = 0;
            ly++;
        }
    }
    printf("Points left: %d\n", points);

    while(work){
        if(kbhit()){
            button = getch();
        }
        usleep(100);
        switch(button){
        case 'w':
            if (hero.x!=0 && z[hero.x-1][hero.y]!='*')
                hero.x--;
            correct = true;
            break;
        case 's':
            if (hero.x!=9 && z[hero.x+1][hero.y]!='*')
                hero.x++;
            correct = true;
            break;
        case 'a':
            if (hero.y!=0 && z[hero.x][hero.y-1]!='*')
                hero.y--;
            correct = true;
            break;
        case 'd':
            if (hero.y!=9 && z[hero.x][hero.y+1]!='*')
                hero.y++;
            correct = true;
            break;
        default:
            correct=false;
        }
        if(correct){

            if(!sleep){
                bool step = 0, p1 = true, p2 = true, p3 = true, p4 = true, px = true, py = true;
                while(!step){
                    if(abs(hero.x-enemy.x)>abs(hero.y-enemy.y) && px || !py){
                        if (!p2 && !p4){
                            enemy.x--;
                            step = true;
                        }
                        if (hero.x-enemy.x <= 0 && p1){
                            if (z[enemy.x-1][enemy.y]!='*' && enemy.x!=0){
                                enemy.x--;
                                step = true;
                            }
                            else{
                                p1 = false;
                            }
                        }
                        else if (p2) {
                            if (z[enemy.x+1][enemy.y]!='*' && enemy.x!=9){
                                enemy.x++;
                                step = true;
                            }
                            else {
                                p2 = false;
                            }
                        }
                        else
                            px = false;
                    }
                    else {
                        if (hero.y-enemy.y <= 0 && p3){
                            if (z[enemy.x][enemy.y-1]!='*' && enemy.y!=0){
                                enemy.y--;
                                step = true;
                            }
                            else {
                                p3 = false;
                            }
                        }
                        else if (p4) {
                            if (z[enemy.x][enemy.y+1]!='*' && enemy.y!=9){
                                enemy.y++;
                                step = true;
                            }
                            else {
                                p4 = false;
                            }
                        }
                        else
                            py = false;
                    }
                }
                sleep = true;
            } else {sleep = false;}

            char z[10][10] = {"..........",".***..***.",".*......*.",".*.*..*.*.","...*..*...","...*..*...",".*.*..*.*.",".*......*.",".***..***.",".........."};

            for(int i=0;i<100;i++){
                if(Points[i].x==hero.x && Points[i].y==hero.y && Points[i].life){
                    Points[i].life = false;
                    points--;
                }
                if(Points[i].life)
                    z[Points[i].x][Points[i].y] = Points[i].type;
            }

            z[hero.x][hero.y]=hero.type;
            z[enemy.x][enemy.y]=enemy.type;

            system("cls");
            for (int i = 0;i < 10;i++){
                for(int j = 0;j < 10;j++){
                    printf("%c",z[i][j]);
                }
                printf("\n");
            }
            printf("Points left: %d\n",points);
            if(!sleep)
                printf("Hunter hunting\n");
            else
                printf("Hunter sleep\n");


            if (hero.x-enemy.x==0 && hero.y-enemy.y==0){
                hero.life=false;
                work=false;
            }

            if (points==0){
                enemy.life=false;
                work=false;
            }
        }
    }
    if (!hero.life){
        system("cls");
        printf("----------\n----------\n----------\n----------\n---YOU_---\n---LOSE---\n----------\n----------\n----------\n----------");
    }
    if (!enemy.life){
        system("cls");
        printf("----------\n----------\n----------\n----------\n---YOU_---\n---_WIN---\n----------\n----------\n----------\n----------");
    }
    getchar();
    return 0;
}
