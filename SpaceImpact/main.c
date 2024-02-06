#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <unistd.h>
#include <conio.h>
#define WIDTH 30
#define HEIGHT 9
#define FILL 46
#define ENEMYCOUNT 20
struct Spaceship{
    int y;
    int x;
    bool life;
};
struct Enemy{
    int y;
    int x;
    int health;
    int type;
    bool life;
};
void ControlSpaceship(char Button, struct Spaceship *Player,int bulletmap[HEIGHT][WIDTH]){
    switch(Button){
    case 'w':
        if(Player->y>=1)
            Player->y--;
        break;
    case 's':
        if(Player->y<HEIGHT-1)
            Player->y++;
        break;
    case 'a':
        if(Player->x>=3)
            Player->x--;
        break;
    case 'd':
        if(Player->x<WIDTH-2)
            Player->x++;
        break;
    case ' ':
        bulletmap[Player->y][Player->x+2] = 1;
        break;
    default:
        break;
    }
}
void DrawBullets(int bulletmap[HEIGHT][WIDTH], char map[HEIGHT][WIDTH]){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            switch(bulletmap[i][j]){
            case 0:
                break;
            case 1:
                map[i][j] = 'o';
                break;
            case -1:
                map[i][j] = '*';
                break;
            default:
                break;
            }
        }
    }
}
void BulletsMove(int bulletmap[HEIGHT][WIDTH], int *BaseHealth){
    for(int i=0;i<HEIGHT;i++){
        bulletmap[i][WIDTH-1] = 0;
    }
    for(int i=0;i<HEIGHT;i++){
        if(bulletmap[i][0] == -1){
            *BaseHealth -= 5;
        }
        bulletmap[i][0] = 0;
    }
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH - 1;j++){
            if(bulletmap[i][j] == 1){
                if(bulletmap[i][j+1] == -1){
                    bulletmap[i][j] = 0;
                    bulletmap[i][j+1] = 0;
                    continue;
                }
                bulletmap[i][j+1] = 1;
                bulletmap[i][j] = 0;
                j++;
            }
        }
    }
    for(int i=0;i<HEIGHT;i++){
        for(int j=WIDTH - 1;j>0;j--){
            if(bulletmap[i][j] == -1){
                if(bulletmap[i][j-1] == 1){
                    bulletmap[i][j] = 0;
                    bulletmap[i][j-1] = 0;
                    continue;
                }
                bulletmap[i][j-1] = -1;
                bulletmap[i][j] = 0;
                j--;
            }
        }
    }
}
void DrawSpaceShip(struct Spaceship *Player, char map[HEIGHT][WIDTH]){
    for(int i=0;i<HEIGHT;i++)
        map[i][0] = ')';
    map[Player->y][Player->x-1] = 'X';
    map[Player->y][Player->x] = '#';
    map[Player->y][Player->x+1] = '>';

}
bool CheckSpaceShipDefeat(struct Spaceship *Player, struct Enemy Enemies[ENEMYCOUNT], int bulletmap[HEIGHT][WIDTH], int *BaseHealth){
    for(int k=0;k<ENEMYCOUNT;k++){
        if(Enemies[k].life &&
           (Player->y == Enemies[k].y && Player->x == Enemies[k].x
           || Player->y == Enemies[k].y && Player->x+1 == Enemies[k].x
           || Player->y == Enemies[k].y && Player->x-1 == Enemies[k].x))
            Player->life = false;
    }
    if(bulletmap[Player->y][Player->x-1] == -1 || bulletmap[Player->y][Player->x] == -1 || bulletmap[Player->y][Player->x+1] == -1){
        Player->life = false;
        return true;
    }
    if(*BaseHealth<=0 || Player->life == false)
        return true;
    return false;
}
void DrawEnemies(struct Enemy Enemies[ENEMYCOUNT], char map[HEIGHT][WIDTH]){
    for(int k=0;k<ENEMYCOUNT;k++){
        if(Enemies[k].life)
            switch(Enemies[k].type){
            case 1:
                map[Enemies[k].y][Enemies[k].x] = '<';
                break;
            case 2:
                map[Enemies[k].y][Enemies[k].x] = '{';
                if(Enemies[k].x<WIDTH-1)
                    map[Enemies[k].y][Enemies[k].x+1] = 'D';
                break;
            case 3:
                map[Enemies[k].y][Enemies[k].x] = '[';
                if(Enemies[k].x<WIDTH-1)
                    map[Enemies[k].y][Enemies[k].x+1] = 'H';
                if(Enemies[k].x<WIDTH-2)
                    map[Enemies[k].y][Enemies[k].x+2] = ']';
                break;
            case 4:
                for(int n=0;n<HEIGHT;n++){
                    if(time(NULL)%2==0){
                        if(n%2==0){
                            map[n][Enemies[k].x] = '/';
                            if(Enemies[k].x<WIDTH-1)
                                map[n][Enemies[k].x+1] = '\\';
                            if(Enemies[k].x<WIDTH-2)
                                map[n][Enemies[k].x+2] = '/';
                        }
                        else{
                            map[n][Enemies[k].x] = '\\';
                            if(Enemies[k].x<WIDTH-1)
                                map[n][Enemies[k].x+1] = '/';
                            if(Enemies[k].x<WIDTH-2)
                                map[n][Enemies[k].x+2] = '\\';
                        }
                    map[Enemies[k].y][Enemies[k].x] = '0';
                    }
                    else{
                        if(n%2!=0){
                            map[n][Enemies[k].x] = '/';
                            if(Enemies[k].x<WIDTH-1)
                                map[n][Enemies[k].x+1] = '\\';
                            if(Enemies[k].x<WIDTH-2)
                                map[n][Enemies[k].x+2] = '/';
                        }
                        else{
                            map[n][Enemies[k].x] = '\\';
                            if(Enemies[k].x<WIDTH-1)
                                map[n][Enemies[k].x+1] = '/';
                            if(Enemies[k].x<WIDTH-2)
                                map[n][Enemies[k].x+2] = '\\';
                        }
                    map[Enemies[k].y][Enemies[k].x] = 'O';
                    }
                }
                break;
            }

    }
}
void CreateEnemy(struct Enemy Enemies[ENEMYCOUNT], int Current, int type){
    switch(type){
    case 1:
        Enemies[Current].y = rand()%9;
        Enemies[Current].x = WIDTH-1;
        Enemies[Current].health = 1;
        Enemies[Current].life = true;
        Enemies[Current].type = 1;
        break;
    case 2:
        Enemies[Current].y = rand()%9;
        Enemies[Current].x = WIDTH-1;
        Enemies[Current].health = 2;
        Enemies[Current].life = true;
        Enemies[Current].type = 2;
        break;
    case 3:
        Enemies[Current].y = rand()%9;
        Enemies[Current].x = WIDTH-1;
        Enemies[Current].health = 4;
        Enemies[Current].life = true;
        Enemies[Current].type = 3;
        break;
    case 4:
        Enemies[Current].y = HEIGHT/2;
        Enemies[Current].x = WIDTH-1;
        Enemies[Current].health = 100;
        Enemies[Current].life = true;
        Enemies[Current].type = 4;
        break;
    }
}
void EnemyMove(struct Enemy Enemies[ENEMYCOUNT], int Timeline, int bulletmap[HEIGHT][WIDTH], int *BaseHealth, int *EnemyLost, struct Spaceship *Player){
    for(int i=0;i<ENEMYCOUNT;i++){
        int shoot = rand()%10;
        if(Enemies[i].life){
            if(Enemies[i].x==0){
                Enemies[i].life = false;
                switch(Enemies[i].type){
                case 1:
                    *BaseHealth -= 10;
                    break;
                case 2:
                    *BaseHealth -= 20;
                    break;
                case 3:
                    *BaseHealth -= 30;
                    break;
                case 4:
                    *BaseHealth -= 100;
                    break;
                }
                *EnemyLost -= 1;
                continue;
            }
            if(bulletmap[Enemies[i].y][Enemies[i].x] == 1){
                Enemies[i].health -= 1;
                bulletmap[Enemies[i].y][Enemies[i].x] = 0;
                if(Enemies[i].health <= 0){
                    Enemies[i].life = false;
                    *EnemyLost -= 1;
                }
            }
            switch(Enemies[i].type){
            case 1:
                if(Timeline%2==0){
                    if(shoot != 0)
                        Enemies[i].x--;
                    else
                        bulletmap[Enemies[i].y][Enemies[i].x] = -1;
                }
                break;
            case 2:
                if(Timeline%4==0){
                    if(shoot != 0)
                        Enemies[i].x--;
                    else
                        bulletmap[Enemies[i].y][Enemies[i].x] = -1;
                }
                break;
            case 3:
                if(Timeline%8==0){
                    if(shoot != 0)
                        Enemies[i].x--;
                    else
                        bulletmap[Enemies[i].y][Enemies[i].x] = -1;
                }
                break;
            case 4:
                if(Timeline%16==0){
                    if(shoot != 0){
                        Enemies[i].x--;
                        if(Player->x == Enemies[i].x ||
                           Player->x+1 == Enemies[i].x ||
                           Player->x-1 == Enemies[i].x ||
                            Enemies[i].x == 0)
                            Player->life = false;
                    }
                    else{
                        for(int n=0;n<HEIGHT;n++)
                            bulletmap[n][Enemies[i].x] = -1;
                    }
                }
                break;
            }
            if(bulletmap[Enemies[i].y][Enemies[i].x] == 1){
                Enemies[i].health -= 1;
                bulletmap[Enemies[i].y][Enemies[i].x] = 0;
                if(Enemies[i].health <= 0){
                    Enemies[i].life = false;
                    *EnemyLost -= 1;
                }
            }
        }
    }
}
void Print(char map[HEIGHT][WIDTH], struct Spaceship *Player, int *BaseHealth, int *Current, struct Enemy Enemies[ENEMYCOUNT]){
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    if(*Current != 1)
        printf("BaseHealth : %3.i \nEnemy lost : %3.i \n", *BaseHealth, *Current);
    else
        printf("BaseHealth : %3.i \nBOSS HEALTH : %3.i \n", *BaseHealth, Enemies[ENEMYCOUNT-1].health);
}
int main()
{
    srand(time(NULL));
    char map[HEIGHT][WIDTH];
    int bulletmap[HEIGHT][WIDTH];
    memset(bulletmap,0,sizeof(bulletmap));
    struct Spaceship Player = {HEIGHT/2,3,true};
    struct Enemy Enemies[ENEMYCOUNT];
    for(int k=0;k<ENEMYCOUNT;k++) Enemies[k].life = false;
    int Timeline = time(NULL);
    int Fraps = 0;
    bool EnemyCooldown = true;
    int EnemySpawn = 0;
    int CurrentEnemy = 0;
    int BaseHealth = 100;
    int EnemyLost = ENEMYCOUNT;
    while(true){
        if(EnemyCooldown){
            EnemySpawn = 2+rand()%3;
            EnemyCooldown = false;
        }
        if(Timeline + EnemySpawn == time(NULL) && CurrentEnemy < ENEMYCOUNT){
            if(CurrentEnemy<ENEMYCOUNT-1)
                CreateEnemy(&Enemies,CurrentEnemy,1+rand()%3);
            else
                CreateEnemy(&Enemies,CurrentEnemy,4);
            EnemyCooldown = true;
            CurrentEnemy++;
            Timeline += EnemySpawn;
        }
        memset(map,FILL,sizeof(map));
        system("cls");
        char Button = '/';
        if(kbhit())
            Button = getch();
        ControlSpaceship(Button,&Player,bulletmap);
        EnemyMove(Enemies, Fraps, bulletmap, &BaseHealth, &EnemyLost, &Player);
        BulletsMove(bulletmap, &BaseHealth);
        DrawBullets(bulletmap, map);
        DrawSpaceShip(&Player, map);
        DrawEnemies(&Enemies, map);
        Print(map, &Player, &BaseHealth, &EnemyLost, Enemies);
        if(CheckSpaceShipDefeat(&Player, Enemies, bulletmap, &BaseHealth))
            break;
        if(EnemyLost == 0)
            break;
        Fraps++;
        usleep(100000);
    }
    if(Player.life)
        printf("Victory!");
    else
        printf("Defeat...");
}
