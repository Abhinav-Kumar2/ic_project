#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include "b24cm1018_b24cm1002_b24cm1053_b24cs1056_character.h"
#include "b24cm1018_b24cm1002_b24cm1053_b24cs1056_wordle.h"
#define MAX 1000

void first_room();
void second_room();
void third_room(char *name);
int sanity;

int wordleState = 0;
int hangmanState = 0;
int winState=0; // for final epilogue

int main()
{
    printf("Welcome to 'The Weight Of Love'!\n Developed by NotEpicGames.\n");
    printf("A game built to test your skills in deduction and reasoning.\n");
    printf("Prepare to embark on a mysterious journey filled with puzzles, challenges, and choices.\n");
    
    char name[MAX];
    printf("What would you like to name your character?\n");
    fgets(name, MAX, stdin);
    FILE *fp = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_datastorage.txt", "w");
    fputs(name, fp);
    fclose(fp);

    int a;
    char code[MAX];
    printf("Do you know the secret code?\n");
    scanf("%s", code);
    if(strcmp(code,"xyz")==0) a=1;
    else if(strcmp(code,"abc")==0)
    {
        wordleState=1;
        a=1;
    }
    else if(strcmp(code,"lmn")==0)
    {
        wordleState=1;
        hangmanState=1;
        a=1;
    }

    if(a!=1) system("b24cm1018_b24cm1002_b24cm1053_b24cs1056_investigation.exe");

    printf("\nYou wake up in a daze, disoriented and unsure of your surroundings.\n");
    printf("As your memories slowly start returning,you began to remember the reason why you are here. You came here to find out the murdere of your wife.\n");
    printf("You see around and observe that the chamber you are in is small, with three doors: two unlocked and one requiring a passkey.\n");
    
    printf("Controls:\n");
    printf("- Enter '1' to open the first door.\n");
    printf("- Enter '2' to open the second door.\n");
    printf("- Enter '3' to attempt unlocking the third door.\n");
    printf("- Enter '4' to inspect the current chamber.\n");
    printf("- Enter '5' to exit the game.\n");
    
    int choice = -1;
    int chamber = 1; // Tracks which chamber the player is currently in

    while (chamber == 1)
    {
        printf("\nChoose an action: ");
        scanf("%d", &choice);
        while (choice != -1)
        {
            if (choice == 1) // Open 1st door
            {
                first_room();
                choice = -1;
            }
            else if (choice == 2) // Open 2nd door
            {
                second_room();
                choice = -1;
            }
            else if (choice == 3) // Open 3rd door
            {
                third_room(name);
                return 0;
            }
            else if (choice == 4) // Describe chamber
            {
                printf("You inspect the chamber. The walls are damp and covered in scribbles, scribbles looking like that of a child.\n");
                printf("As you see around, the scenery around looks reminiscient of a kid fulfilling its imagination to the fullest.\n");
                choice = -1;
            }
            else if (choice == 5) break; // Exit game
        }
    }
}

void first_room()
{
    printf("You step into the first room, your heart racing.\n");
    printf("The room is dimly lit, and in the center, you see an electronic device glowing faintly.\n");
    printf("You approach it cautiously, ready to interact with it.\n");
    wordle();

    FILE* fp = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_datastorage.txt", "r");
    char a[MAX];
    int iter = 0;
    while(fgets(a, MAX, fp))
    {
        if(strcmp(a,"1\n")==0 || strcmp(a, "1")==0)
        {
            wordleState=1;
            break;
        }
        iter++;
    }
    printf("\nThe secret code to skip this room is abc\n");
    if(wordleState==1 && hangmanState==1) printf("To skip past both rooms, lmn is the code you need");
    fclose(fp);
}

void second_room()
{
    printf("You enter the second room. The atmosphere is heavy, and the faint sound of whispers fills the air.\n");
    printf("In the center of the room, there's a pedestal with an object resting on top.\n");
    printf("A puzzle awaits you...\n");
    (void) system("b24cm1018_b24cm1002_b24cm1053_b24cs1056_Hangmans.exe");

    FILE* fp = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_datastorage.txt", "r");
    char a[MAX];
    int iter = 0;
    while(fgets(a, MAX, fp))
    {
        if(strcmp(a,"2")==0 || strcmp(a,"2\n")==0)
        {
            hangmanState=1;
            break;
        }
        iter++;
    }
    if(wordleState==1 && hangmanState==1) printf("To skip past both rooms, lmn is the code you need");
    fclose(fp);
}

void third_room(char *name)
{
    if(wordleState==1 && hangmanState==1)
    {
        printf("You enter the keys, and the lock clicks open. The door creaks as it swings ajar.\n");
        Sleep(2000);
        printf("As you step inside, the room is shrouded in darkness, save for a faint flickering light in the distance.\n");
        Sleep(1000);
        printf("Suddenly, you hear rapid footsteps approaching. You grab a metal pipe nearby, your instincts on high alert.\n");
        Sleep(3000);
        printf("The door bursts open, revealing a masked figure. There's no escape. It's time to fight!\n");
        Sleep(3000);

        name[strcspn(name, "\n")] = 0; // appends \0
        Character *Me = malloc(sizeof(Character));
        initializeChar(Me, 250);// 3 for giving pistol 
        strcpy(Me->mname,name);
        for(int i=0;i<6;i++) Me->isowned[i]=1;

        Character *Enemy = malloc(sizeof(Character));
        strcpy(Enemy->mname,"Enemy");
        initializeChar(Enemy, 200);
        initializeOpp(Enemy);

        battle(Me,Enemy);

        system("cls");
        printf("It's finally over, looks like you got out in one piece(mostly...)\n");
        Sleep(2000);
        printf("You open the door in front of you. There is a long corridor. You traverse along it and reach the end. You see a door to your left\n");
        Sleep(2000);
        printf("You hear rumbling noises coming from within. A wrecking ball is rolling towards you!\n");
        Sleep(2000);
        system("cls");
        printf("Press 'A' 20 times in 5 seconds to  dodge the ball!\n");
        
        clock_t prev = clock(); // gets time at instant of calling 
        clock_t curr = clock();

        int state=0; // to check if won or not
        while(1)
        {
            char c;
            int count = 0;
            while(curr-prev < 5000) // time measured in ms
            {
                curr = clock();
                if((c= getch()) =='A' || (c == 'a')) count++; // drawback- only measures after a character is inputted
                if(count>=20)
                {
                    state=1;
                    printf("You just manage to slide by the wrecking ball as it passes you.\n");
                    break;
                }
            }
            break;
        }   

        if(state==0)
        {
            printf("You got crushed by the wrecking ball. Too bad, try again next time.\n");
            exit(0);
        }

        Sleep(2000);
        system("cls");
        printf("Your heart palpitating and your senses heightened, you enter the room from which the wrecking ball came.\n");
        Sleep(2000);
        printf("Just as you enter, a metal contraption seals the door behind you. Various doors in the room open and water starts\n");
        printf("gushing out of them. The room quickly fills up with water.\n");
        Sleep(4000);
        system("cls");
        printf("You see light creeping out from a window at the top. All you can do now is swim up to it and break it!\n");
        Sleep(2000);
        printf("You need to alternatively mash A and D 20 times in order to swim up.\n");
    
        prev = clock(); // gets time at instant of calling 
        curr = clock();
        state=0; // reset state to reuse for this minigame
        while(1)
        {
            char c,pc='d';
            int count = 0;
            while(curr-prev < 7000)
            {
                curr = clock();
                Sleep(200);
                pc='d';
                while((c=getch()) == 'A' || (c == 'a') && (pc == 'd' || pc =='D'))
                {
                    count++;
                    pc = c;
                    while((c=getch()) == 'D' || (c == 'd')&& (pc== 'a' || pc == 'A'))
                    {
                        count++;
                        pc = c;
                    }
                }
                if(count>=20)
                {
                    state=1;
                    printf("You swim up and successfully break the window.\n");
                    break;
                }
            }
            break;
        }
        if(state==0)
        {
            printf("\n");
            exit(0);
        }
        Sleep(3000);
        printf("You climb up and pass out as soon as you lay down on the ground. The memories of your wife flood your mind as you begin to remember those warm days with her and your son.\n");
        system("cls");
        Sleep(3000);
        printf("As you woke up, an unknown scenery greets your eyes. You wake up to a corridor whose end is veiled by darkness.\n You take a deep breath and move forward for finding out the truth behind your wife's murder.\n");
        (int) system("b24cm1018_b24cm1002_b24cm1053_b24cs1056_maze.exe");
        Sleep(3000);
        printf("Finally, you were able to escape the deady maze and the foes lying amongst it. Now, you observe another chamber where you see a table with two pistols lying on it, giving you a deadly premonition. \n");

        system("b24cm1018_b24cm1002_b24cm1053_b24cs1056_russianRoulette.exe");
        Sleep(3000);
        printf("\nAfter surving the game of death, you arrive at the end after facing all the hardships to meet the person who\nmurdered the love of your life and ruined your happy hamily.\n");

        initializeChar(Me, 250);// 3 for giving pistol 
        initializeChar(Enemy, 350);

        Weapon weaps[NO_OF_WEAPS] = {Fist, Hammer, Knife, Pistol, Katana, SMG};
        Enemy->mweap=weaps[1];
        strcpy(Enemy->mname,"Jason");

        battle(Me,Enemy);

        FILE* fp = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_datastorage.txt", "r");
        char a[MAX];
        int iter = 1;
        while(fgets(a, MAX, fp))
        {
            if(strcmp(a,"w")==0)
            {
                winState=1;
                break;
            }
            else if(strcmp(a,"l")==0)
            {
                winState=0;
                break;
            }
            iter++;
        }
        fclose(fp);

        char str[MAX];
        
        if(winState==1)
        {
            FILE* ef = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_EpilogueWin.txt", "r");
            int iter=0;
            while(fgets(str, MAX, ef)) printf("%s", str);
        }
        else
        {
            FILE* ef = fopen("b24cm1018_b24cm1002_b24cm1053_b24cs1056_EpilogueLose.txt", "r");
            int iter=0;
            while(fgets(str, MAX, ef)) printf("%s", str);
        }
    }
}