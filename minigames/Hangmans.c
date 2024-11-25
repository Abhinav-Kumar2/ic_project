#include <stdio.h>
#include <time.h> // For randomizing the word chosen using srand
#include <stdlib.h>
#include <string.h>
#include "Hangman_Word.h" // Include the header file with word list

// Function to draw the hangman
void Hangman(int mistakes, char* man, int gameLost) {
    char* RED = "\033[1;31m";
    char* WHITE = "\033[0m";
    
    // If the game is lost, set hangman to red
    if (gameLost) {
        printf("%s", RED); // Apply red color
    }

    printf("\tTimes you have messed up: %d\n", mistakes);

    // initializing all symbols for making the hangman
    mistakes == 6 ? (man[6] = '\\') : mistakes == 5 ? (man[5] = '/') : mistakes == 4 ? (man[4] = '\\') : mistakes == 3 ? (man[3] = '|') : mistakes == 2 ? (man[2] = '/') : mistakes == 1 ? (man[1] = ')', man[0] = '(') : 0;

    printf("\t _________\n"
           "\t|         |\n"
           "\t|        %c %c\n"
           "\t|        %c%c%c\n"
           "\t|        %c %c\n"
           "\t|             \n"
           "\t|             \n", 
           man[0], man[1], man[2], man[3], man[4], man[5], man[6]);
    
    // WHITE color to default
    if (gameLost) {
        printf("%s", WHITE);
    }
}

// Showing the progress of the words after every guess, prints _ if not guessed and that letter if guessed
void currentStatus(char* Chosen_Word, char* letterGuessed, int lengthOfWord) {
    printf("Current Progress: ");
    for (int f = 0; f < lengthOfWord; f++) {
        if (letterGuessed[f]) {
            printf("%c ", Chosen_Word[f]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Printing the letters that do not appear in the word
void wrong_guess(char* wrongGuesses, int mistakes) {
    printf("Wrong Guesses: ");
    for (int f = 0; f < mistakes; f++) {
        printf("%c ", wrongGuesses[f]);
    }
    printf("\n");
}

int main() {
    char* RED = "\033[1;31m";
    char* GREEN = "\033[1;32m";
    char* WHITE = "\033[0m";

    printf("Welcome to Hangman!\n");
    printf("I'm sure you've played this game at least once before.\n");
    printf("However, this time it's different. The stakes are high!\n");
    printf("Your son is in danger! You must guess the correct word or your dear son will meet a tragic end...\n");
    printf("\n\n\t These are the rules: ");
    printf("\n\t - You cannot make more than 6 mistakes. Every time you mess up, the noose around your son tightens.");
    printf("\n\t   If you lose, you will witness your son die before your eyes. What a tragedy...\n");
    printf("\n\t   PS: The word you guess will provide a clue to help uncover my identity.");

    srand(time(NULL)); 
    int randomWordIndex = rand() % NO_OF_WORDS; // Index of a random word chosen
    char *Chosen_Word = listofWords[randomWordIndex]; // Pointer to the chosen word
    int lengthOfWord = strlen(Chosen_Word); 

    char letterGuessed[MAX_LETTER_IN_A_WORD] = {0}; // Array to track correctly guessed letters
    char wrongGuesses[10] = {0}; // Array for wrong guesses
    int correct_guess_no = 0;
    int mistakes = 0;
    char man[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '}; // Array to represent the hangman
    char guess[16];

    // Main game loop
    while (correct_guess_no < lengthOfWord && mistakes < 6) {
        printf("\nYour progress in saving your son: %d\n", correct_guess_no);
        currentStatus(Chosen_Word, letterGuessed, lengthOfWord);
        wrong_guess(wrongGuesses, mistakes);
        printf("Enter a guessed letter: ");
        fgets(guess, sizeof(guess), stdin);
        
        char letterEntered = guess[0];
        printf("Letter Entered: %c\n", letterEntered);

        int round_count = 0;

        for (int f = 0; f < lengthOfWord; f++) {
            if (letterGuessed[f] == 1) { 
                continue; // Skip already guessed letters
            }

            if (letterEntered == Chosen_Word[f]) {
                letterGuessed[f] = 1; // Mark the newly guessed letter as guessed
                correct_guess_no++;
                round_count++;
            }
        }

        // Check if the letter was a wrong guess
        if (round_count == 0) {
            wrongGuesses[mistakes] = letterEntered; // Save the wrong guess
            mistakes++;
            Hangman(mistakes, man, 0); // Update hangman drawing
        } else {
            printf("Ooh, that's quite a good guess.\n");
        }
    }

    if (correct_guess_no == lengthOfWord) {
        // Winning message with green text
        printf("%sCongrats! You have saved your son! The word was %s.%s\n", GREEN, Chosen_Word, WHITE);
        printf("The voice from the speaker says, \"I know you may want to meet your son now, but things are not that simple...\"\n");
        printf("\"Unfortunately, you can't meet him right now.\"\n");
        printf("As his words echo in your mind, the lights go out in the room where your son is.\n");
    } else {
        // Losing message with red text and hangman in red
        printf("%sOops, you lost! The word was: %s\n", RED, Chosen_Word);
        Hangman(mistakes, man, 1); // Display the red hangman when you lose
        printf("%s\"Too bad, you couldn't use your sharp mind at such a crucial moment in your life.\"\n", RED);
        printf("\"Well, it's too late now...\" Your throat dries as you hear your son's last breath.\n%s", WHITE);
    }

    return 0;
}
