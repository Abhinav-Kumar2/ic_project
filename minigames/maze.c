#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

#define WALL '#'
#define SPACE ' '
#define PLAYER 'O'
#define ENEMY 'X'
#define WIDTH 40
#define HEIGHT 30
#define initX 1
#define initY 1
char map[HEIGHT][WIDTH];
void move(char, int*,int*); // movement ke liye
void init(int *x, int *y); // initialize map at t=0
void draw(); // draw map after game starts.

int main()
{
    int xCoord=initX, yCoord=initY;
    init(&xCoord, &yCoord);

    while(1)
    {
        draw(&xCoord, &yCoord);
        char input = getch();
        move(input, &xCoord,&yCoord);
    }
}

void init(int *xCoord, int *yCoord)
{
    for(int i=0;i<WIDTH;i++) map[0][i] = '#'; // top wall
    for(int i=0;i<WIDTH;i++) map[HEIGHT-1][i] = '#'; // bottom wall
    for(int i=0;i<HEIGHT;i++) map[i][0] = '#'; // left wall   
    for(int i=0;i<HEIGHT;i++) map[i][WIDTH-1] = '#'; // right wall
    map[*yCoord][*xCoord] = 'O';
    
    int pos = 1; // to control gap in random walls
    srand(time(NULL));
    for(int i=0; i<5;i++) // randomly generates horizontal walls 
    {
        int row = 0;
        row = rand() % (HEIGHT-3);  
        if(pos) // leaves gap at right side
        {
            for(int i=0;i<WIDTH-5;i++) // width-5 to leave gap at right end
            {
                map[row][i] = '#'; // places random walls
            }
            pos = 0;
        }
        else
        {
            for(int i=WIDTH-1;i>=5;i--) // gap at left end
            {
                map[row][i] = '#';
            }
            pos = 1;
        }
    }

    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            if((map[i][j] != '#') && (map[i][j] != 'O') && (map[i][j] != 'X')) map[i][j] = ' ';
        }
    }
}

void move(char input, int *xCoord, int *yCoord)
{
    //input = tolower(input);

    if(input == 'w')
    {
        if(map[*yCoord-1][*xCoord] != WALL)
        {
            map[*yCoord][*xCoord] = ' ';
            *yCoord = *yCoord -1;
        }
    }
    if(input == 'a')
    {
        if(map[*yCoord][*xCoord-1] != WALL)
        {
            map[*yCoord][*xCoord] = ' ';
            *xCoord = *xCoord-1;
        }
    }
    if(input == 's')
    {
        if(map[*yCoord+1][*xCoord] != WALL)
        {
            map[*yCoord][*xCoord] = ' ';
            *yCoord= *yCoord+1;
        }
    }
    if(input == 'd')
    {
        if(map[*yCoord][*xCoord+1] != WALL)
        {
            map[*yCoord][*xCoord] = ' ';
            *xCoord = *xCoord+1;
        }
    }   
}

void draw(int *xCoord, int *yCoord)
{
    map[*yCoord][*xCoord] = 'O';
    system("cls");
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++) printf("%c",map[i][j]);
        printf("\n");
    }
}