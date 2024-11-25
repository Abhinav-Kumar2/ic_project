#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void display_intro(); //showing the start of the game
void display_inventory(); //showing all the clues and testimonies that have been shown
void examine_clue(int clue_number); //observing the clues collected by police
void interrogation(); //witnesses testimony
void go_to_hidden_room(); //going to a hidden room in the house
void discover_secret_location();
void add_to_inventory(char item[]); //function to add examined clue to the inventory

int clue_found[9] = {0}; 
char inventory[10][50]; //10 or so clues
int inventory_count = 0;

int all_clues_collected() { //function is to see if the clues are collected to ensure progression to next stage
    for (int i = 0; i < 9; i++) {
        if (clue_found[i] == 0) {
            return 0; 
        }
    }
    return 1;
}

int main() {
    int choice;

    display_intro();

    while (1) {
        printf("\n--- Investigation Menu ---\n1. View Case Evidence\n2. Examine a Clue\n3. Interrogate a Witness\n");

        // Only show these options if all clues are collected
        if (all_clues_collected()) {
            printf("4. Go to the Hidden Room\n5. Search for Secret Location\n");
        } else {
            printf("4. Go to the Hidden Room (Locked)\n5. Search for Secret Location (Locked)\n");
        }

        printf("6. Quit\nChoose an action: ");
        scanf("%d", &choice);

        if (choice == 1) {
            display_inventory();
        }
        else if (choice == 2) {
            int clue_number;
            printf("Enter Clue Number (1-9): ");
            scanf("%d", &clue_number);
            examine_clue(clue_number);
        }
        else if (choice == 3) {
            interrogation();
        }
        else if (choice == 4) {
            if (all_clues_collected()) {
                go_to_hidden_room();
            } else {
                printf("You need to collect all clues first to go to the Hidden Room.\n");
            }
        }
        else if (choice == 5) {
            if (all_clues_collected()) {
                discover_secret_location();
                break;
            } else {
                printf("You need to collect all clues first to discover the Secret Location.\n");
            }
        }
        else if (choice == 6) {
            printf("Goodbye, Detective. May you find peace.\n");
            return 0;
        }
        else {
            printf("Invalid choice. Please select an option from the menu.\n");
        }
    }

    return 0;
}

void display_intro() {
    printf("Welcome to The Weight Of Love!\nYou are a world famous detective, investigating the murder of your beloved wife.\nDespite the pain, you know you must press forward to uncover the truth-not just for justice, but for the sake of your only attachment to this world. Your sons..\n");
}

void display_inventory() {
    printf("\n--- Collected Evidence ---\n");
    if (inventory_count == 0) {
        printf("You haven't collected any evidence yet.\n");
    } else {
        for (int i = 0; i < inventory_count; i++) {
            printf("%d. %s\n", i + 1, inventory[i]); // Showing the entire list of the inventory
        }
    }
}

void add_to_inventory(char item[]) { // Adding the examined evidence to the inventory
    if (inventory_count < 10) {
        strcpy(inventory[inventory_count], item);
        inventory_count++;
    } else {
        printf("Inventory is full.\n");
    }
}

void examine_clue(int clue_number) {
    if (clue_number < 1 || clue_number > 9) {
        printf("Invalid clue number.\n");
        return;
    }

    if (clue_found[clue_number - 1]) {
        printf("You have already examined this clue.\n");
        return;
    }

    clue_found[clue_number - 1] = 1;

    FILE *file = fopen("clues.txt", "r");

    char clue_line[255];
    int current_clue = 1;
    while (fgets(clue_line, sizeof(clue_line), file)) {
        if (current_clue == clue_number) {
            printf("\nExamining: %s", clue_line);
            add_to_inventory(clue_line);
            break;
        }
        current_clue++;
    }

    fclose(file);
}

void interrogation() {
    int witness_choice;
    char *witnesses[] = {"Neighbor", "Aunt-in-Law", "Victim's Brother"};

    printf("\n--- Interrogation ---\n1. Neighbor\n2. Family Friend\n3. Victim's Brother\nChoose a witness to interrogate: ");
    scanf("%d", &witness_choice);

    if (witness_choice == 1) {
        printf("Neighbor: 'I saw a figure by the fence that night when I came out to get my bucket I left out while washing clothes, but I thought it was nothing.'\n");
        add_to_inventory("Neighbor's Testimony");
    }
    else if (witness_choice == 2) {
        printf("Family Friend: 'Alice mentioned that she was worried for Jason as they had a big fight between them a few days prior to the grisly murder.'\n");
        add_to_inventory("Aunt-in-law's Testimony");
    }
    else if (witness_choice == 3) {
        printf("Victim's Brother: 'I could see that my sister was anxious about something. She kept chewing on her nails, which is a sign of anxiety for her.'\n");
        add_to_inventory("Victim's Brother's Testimony");
    }
    else {
        printf("Invalid witness choice.\n");
    }
}

void go_to_hidden_room() {
    printf("\n--- Hidden Room ---\nYou unlock the basement room using the rusted key.\nInside, you find old documents and an estate map.\nThe map shows a location marked with a red 'X' at a remote area.\nBeneath it, a note reads: 'You must pay for your actions done in the past.'\n");
    printf("You wonder if this note was left for you or for her. Either way, you are closer to the truth now.\n");
    add_to_inventory("Estate Map");
}

void discover_secret_location() {
    printf("\n--- Secret Location ---\nWith the clues gathered, you follow the map to the secret location.\nAt that location, you find a house resembling the house that you and your wife had built over the years before you moved due to your son and anger overwhelms your mind as you can feel that the murderer is mocking you. Laughing at your sorry plight.\n");
    printf("You take a deep breath, resolve your mind with unwavering determination and step inside the house to face the murderer behind your wife.\n");
}
