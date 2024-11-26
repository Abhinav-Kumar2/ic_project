//SANITY WALA FUNDA
/*
TERMINAL COLOR DENA
enemy will be red
player is blue
empty space as is (terminal bg color)
*/ 
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include <windows.h>
HANDLE hConsole;
#include "b24cm1018_b24cm1002_b24cm1053_b24cs1056_character.h"


#define MAX 1000
#define WALL '#'
#define SPACE ' '
#define PLAYER 'O'
#define ENEMY 'X'
#define EXIT 'E'
#define WIDTH 40
#define HEIGHT 20
#define initX 1
#define initY 1
char map[HEIGHT][WIDTH];
void move(char, int*,int*, char[]); // movement ke liye
void init(int *x, int *y); // initialize map at t=0
void draw(); // draw map after game starts.
int state=1; // to check if game is won or not 
int sanity=100;

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int main()
{   
    int xCoord=initX, yCoord=initY;
    init(&xCoord, &yCoord);

    char name[MAX];
    FILE *fp = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_datastorage.txt", "r");
    fgets(name,MAX,fp);
    fclose(fp);

    while(1)
    {
        draw(&xCoord, &yCoord);
        Sleep(100);
        char input = getch();
        move(input, &xCoord,&yCoord, name);
        if(state == 0) break;
    }
}

void init(int *xCoord, int *yCoord)
{
    for(int i=0;i<WIDTH;i++) map[0][i] = '#'; // top wall
    for(int i=0;i<WIDTH;i++) map[HEIGHT-1][i] = '#'; // bottom wall
    for(int i=0;i<HEIGHT;i++) map[i][0] = '#'; // left wall   
    for(int i=0;i<HEIGHT;i++) map[i][WIDTH-1] = '#'; // right wall
    map[*yCoord][*xCoord] = 'O';

    srand(time(NULL));
    for(int i=2; i<HEIGHT;i+=2) // randomly generates horizontal walls, i is row position of wall
    {
        int hole1=0, hole2=0;
        while(hole1==0 || hole2==0)
        {
            hole1 = rand() % (WIDTH-1);
            hole2 = rand() % (WIDTH-1);
        }
        for(int j=0;j<WIDTH;j++) map[i][j] = '#';
        map[i][hole1] = ' ';
        map[i][hole2] = ' ';

        float enemyProb = (float) (rand()%5)/5; 
        if(enemyProb<=0.6 && enemyProb>0) map[i][hole1] = 'E';
        else if(enemyProb >0.6)
        {
            map[i][hole1] = 'E';
            map[i][hole2] = 'E';
        }

        if(i==HEIGHT-4) // mandatory enemies on final hole
        {
            map[i][hole1] = 'E';
            map[i][hole2] = 'E';           
        }
        if(i==HEIGHT-2) // exit
        {
            map[i][hole1] = 'X';
            map[i][hole2] = 'X';    
        } 
    }
    
    for(int i=0;i<HEIGHT;i++) // create empty space in remaining places
    {
        for(int j=0;j<WIDTH;j++)
        {
            if((map[i][j] != '#') && (map[i][j] != 'O') && (map[i][j] != 'X') && (map[i][j] != 'E')) map[i][j] = ' ';
        }
    }
}

void move(char input, int *xCoord, int *yCoord, char *name)
{
    if(input <=95) input+=32; // for handling uppercase input

    switch (input)
    {
        case 'w':
            if(map[*yCoord-1][*xCoord] != WALL)
            {
                map[*yCoord][*xCoord] = ' ';
                *yCoord = *yCoord -1;
            }
            break;
        case 'a':
            if(map[*yCoord][*xCoord-1] != WALL)
            {
                map[*yCoord][*xCoord] = ' ';
                *xCoord = *xCoord-1;
            }
            break;
        case 's':
            if(map[*yCoord+1][*xCoord] != WALL)
            {
                map[*yCoord][*xCoord] = ' ';
                *yCoord= *yCoord+1;
            }
            break;
        case 'd':
            if(map[*yCoord][*xCoord+1] != WALL)
            {
                map[*yCoord][*xCoord] = ' ';
                *xCoord = *xCoord+1;
            }
            break;
        default:
            break;
    }

    if(map[*yCoord][*xCoord]=='X')
    {
        printf("You have reached the end of the maze. Congratulations, but this is not the end of your journey.\n");
        state=0;
    }  
    if(map[*yCoord][*xCoord]=='E')
    {
        printf("You see a shadowy figure moving in the corridor. Ready up for a fight!\n");
        Sleep(1000);
        
        name[strcspn(name, "\n")] = 0; // appends \0
        Character *Me = malloc(sizeof(Character));
        initializeChar(Me, 250);// 3 for giving pistol 
        strcpy(Me->mname,name);
        Me->isowned[3] = 1;
        Me->isowned[4] = 1;

        Character *Enemy = malloc(sizeof(Character));
        strcpy(Enemy->mname,"Enemy");
        initializeChar(Enemy, 100);
        initializeOpp(Enemy);

        battle(Me,Enemy);
        Sleep(3000);
    }
}

void draw(int *xCoord, int *yCoord)
{
    hideCursor();
    map[*yCoord][*xCoord] = 'O';
    system("cls");
    for(int i=-3;i<=3;i++)
    {
        for(int j=-3;j<=3;j++)
        {
            printf("%c", map[*yCoord + i][*xCoord + j]);
        }
        printf("\n");
    }
}