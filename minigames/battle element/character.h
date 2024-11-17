#define NO_OF_WEAPS 6

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


typedef struct {
    char mname[10];
    int boost;
} Weapon;

typedef struct {
    char mname[10];
    int mhp; //maxhp
    int chp; //currenthp
    int sanity;
    int shieldon;
    Weapon mweap;
    int isowned[NO_OF_WEAPS];
} Character;


//below are the weapons that exist in the game, to be updated
Weapon Fist = {.mname="Fist",.boost=1};
Weapon Hammer = {.mname="Hammer",.boost=2};
Weapon Knife = {.mname="Knife",.boost=3};
Weapon Pistol = {.mname="Pistol",.boost=6};
Weapon Katana = {.mname="Katana",.boost=5};
Weapon SMG = {.mname="SMG",.boost=9};

void initialize(Character* c){
    c->mhp=300; //modifications can be made to vary the maximum hp from character to character
    c->sanity=1;
    c->shieldon=0;
    c->mweap=Fist;
    c->isowned[0]=1;
    c->chp=c->mhp;
}

void equip(Character* charac){
    int choice=0;
    Weapon weaps[NO_OF_WEAPS]={Fist,Hammer,Knife,Pistol,Katana,SMG};
    while(1){
        for(int i=0;i<NO_OF_WEAPS;i++){
            if(charac->isowned[i] ==1) printf("Enter %d to use %s\n",i,weaps[i].mname);
        }
        scanf("%d",&choice);
        if((choice>=0 && choice<NO_OF_WEAPS)&&charac->isowned[choice]==1){break;}
        if(charac->isowned[choice]!=1) {printf("You do not own this weapon\n");}
    }
    charac->mweap=weaps[choice];
    printf("Equipped %s\n",weaps[choice].mname);
}

void atk(Character* attacker, Character* attacked){
    int dmg=rand()%20;
    float rn=(rand()%10) *1.0 /10;
    if(rn<0.3){
        printf("Critical hit!\n");
        dmg*=2.5;
    }
    if(attacked->shieldon==1){dmg/=4;}
    dmg=dmg*attacker->mweap.boost;
    attacked->chp-=dmg;
    printf("%s attacked %s with %s and dealt %d damage\n",attacker->mname,attacked->mname,attacker->mweap.mname,dmg);
    attacker->shieldon=0;
    if(attacked->chp<=0){
        attacked->chp=0;
        printf("%s died.\n",attacked->mname);}
}

void defend(Character* c){
    c->shieldon=1;
}


void showhealth(int current_health, int max_health) {
    int bar_width = 20; // Width of the health bar in characters
    int filled_length = (current_health * bar_width) / max_health; // Calculate filled portion

    printf("Health: [");
    for (int i = 0; i < bar_width; i++) {
        if (i < filled_length) {
            printf("█"); // Filled part
        } else {
            printf("-"); // Empty part
        }
    }
    printf("] %d/%d\n\n", current_health, max_health); // Display current/max health
}

void battle(Character* p1,Character* p2){
    printf("You're about to enter a fight.\n");
    equip(p1);
    int turn=0;
    int choice;
    while(p1->chp>0 && p2->chp>0){
    if(turn%2==0){
    printf("%s's ",p1->mname);
    showhealth(p1->chp,p1->mhp);
    printf("%s's ",p2->mname);
    showhealth(p2->chp,p2->mhp);
        printf("Enter 1 to attack, enter 2 to defend, enter 3 to change equipped weapon\n");
        scanf("%d",&choice);
        if(choice==1) {atk(p1,p2);}
        else if (choice ==2) defend(p1);
        else {
            equip(p1);
        }
        }
    else if(choice!=3){
        atk(p2,p1);
    }
    turn++;
    }
    
}
