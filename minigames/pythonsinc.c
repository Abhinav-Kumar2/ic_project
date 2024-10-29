#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LENGTH 100

int gameOver;
int x, y, fruitX, fruitY, score;
int tailX[MAX_LENGTH], tailY[MAX_LENGTH];
int tailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum Direction dir;
HANDLE hConsole;
COORD cursorPosition;

void gotoXY(int x, int y) {
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(hConsole, cursorPosition);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    tailLength = 0;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

void draw() {
    gotoXY(0, 0);
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) printf("#");
            if (i == y && j == x) printf("O");
            else if (i == fruitY && j == fruitX) printf("F");
            else {
                int print = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print) printf(" ");
            }
            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT)  // Prevent reversing to the right
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)   // Prevent reversing to the left
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)   // Prevent reversing to down
                dir = UP;
            break;
        case 's':
            if (dir != UP)     // Prevent reversing to up
                dir = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        default:
            // Ignore any non-WASD inputs
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0], prevY = tailY[0], prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        gameOver = 1;
    }

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = 1;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        srand(time(NULL));
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    return 0;
}
