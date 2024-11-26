#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void russianRoulette(int);

int main()
{
    int choice,state=0;

    printf("Welcome to the game of Russian Roulette. In this game, You will be handed a revolver gun with 6 chambers. Only 2 of the chambers will by empty.\n");
    printf("You may risk your life and save Benedict's's life by pointing the revolver to your head. Alternatively, you may save your life but risk Benedict's life by pointing the revolver towards your son.\n");

    printf("What do you choose? Will you point the gun to your head or to Benedict's head?\n");

    while(1)
    {
        printf("Write 1 to shoot yourself or write 2 to shoot the other person.\n");

        scanf("%d", &choice);

        if((choice == 1) || (choice == 2))
        {
            russianRoulette(choice);
            break;
        }
        else
        {
            printf("Invalid Input. Try again\n");
        }
    }
}

void russianRoulette(int choice) // vicArr is input as we dont know who is dead till now.
{
    int ra=0,rb=0,rc=0; // variables for empty chambers. rc is chosen chamber
    while((ra==rb) || (ra ==0 || rb==0))
    {
        srand(time(NULL));
        ra = rand() % 7; // mod7 to generate values b/w 1 to 6
        rb = rand() % 7;
        rc = rand() % 7;
    }

    if(choice == 1)
    {
        if((rc == ra) || (rc == rb))
        {
            printf("A bullet from the revolver pierces your skull.");
            // set status to 0 (dead)
        }
        else
        {
            printf("You lucked out and are still alive and kicking.");
        }    
    }
    else if(choice == 2)
    {
        if((rc == ra) || (rc == rb))
        {
            printf("A bullet from the revolver pierces Benedict's skull.");
            // set status to 0 (dead)
        }
        else
        {
            printf("You and Benedict both lucked out and are still alive and kicking.");
        } 
    }

}