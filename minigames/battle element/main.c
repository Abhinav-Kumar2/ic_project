#include"character.h"

int main(){
    char ename[10];
    fgets(ename,10,stdin);
    ename[strcspn(ename, "\n")] = 0;
    Character Me;
    strcpy(Me.mname,ename);
    Character Enemy;
    strcpy(Enemy.mname,"Enemy");
    initialize(&Me);
    initialize(&Enemy);

  // the three lines below are just for demonstration. Varying them from 0 and 1 will change the ownership status of the ith weapon. actually throughout the game we will have to update the "isowned" array to store info whether a weapon is owned or no
    Me.isowned[1]=1;
    Me.isowned[3]=1;
    Me.isowned[2]=1;
    battle(&Me,&Enemy);
    int closer; //to avoid sudden terminal closing. can be removed once integrated with main game
    scanf("%d",&closer); //same as above
    return 0;
}
