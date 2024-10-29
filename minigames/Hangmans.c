#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void draw(int mistakes, char* body) {
    printf("\tMistakes: %d\n", mistakes);
    switch(mistakes) {
        case 6: body[6] = '\\'; break;
        case 5: body[5] = '/'; break;
        case 4: body[4] = '\\'; break;
        case 3: body[3] = '|'; break;
        case 2: body[2] = '/'; break;
        case 1: body[1] = ')'; body[0] = '('; break;
        default: break;
    }

    printf("\t _________\n"
           "\t|         |\n"
           "\t|        %c %c\n"
           "\t|        %c%c%c\n"
           "\t|        %c %c\n"
           "\t|             \n"
           "\t|             \n", 
           body[0], body[1], body[2], body[3], body[4], body[5], body[6]);
}

void display_progress(char* guessWord, char* letterGuessed, int lengthOfWord) {
    printf("Current Progress: ");
    for (int i = 0; i < lengthOfWord; i++) {
        if (letterGuessed[i]) {
            printf("%c ", guessWord[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

void display_wrong_guesses(char* wrongGuesses, int wrongCount) {
    printf("Wrong Guesses: ");
    for (int i = 0; i < wrongCount; i++) {
        printf("%c ", wrongGuesses[i]);
    }
    printf("\n");
}

int main() {
    char listofWords[][10] = {
        "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine", "ten"
    };

    printf("Welcome to the world of Hangman!");
    printf("\n\n\t Rules: ");
    printf("\n\t - Maximum 6 mistakes are allowed.");
    printf("\n\t - All alphabet characters are in lower case.\n");

    srand(time(NULL)); 
    int randomWordIndex = rand() % 10; 
    char *guessWord = listofWords[randomWordIndex];
    int lengthOfWord = strlen(guessWord);

    char letterGuessed[10] = {0};
    char wrongGuesses[10] = {0};
    int numCorrect = 0;
    int mistakes = 0;
    char body[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
    char guess[16];

    while (numCorrect < lengthOfWord && mistakes < 6) {
        printf("\nNumber Correct So Far: %d\n", numCorrect);
        display_progress(guessWord, letterGuessed, lengthOfWord);
        display_wrong_guesses(wrongGuesses, mistakes);
        printf("Enter a guess letter (or type 'quit' to exit): ");
        fgets(guess, sizeof(guess), stdin);
        
        if (strncmp(guess, "quit", 4) == 0) {
            printf("Thanks for playing!\n");
            return 0;
        }
        
        char letterEntered = guess[0];
        printf("Letter Entered: %c\n", letterEntered);

        int correctThisRound = 0;

        for (int loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
            if (letterGuessed[loopIndex] == 1) {
                continue;
            }

            if (letterEntered == guessWord[loopIndex]) {
                letterGuessed[loopIndex] = 1;
                numCorrect++;
                correctThisRound++;
            }
        }

        // Check if the letter was a wrong guess
        if (correctThisRound == 0) {
            wrongGuesses[mistakes] = letterEntered;  // Save the wrong guess
            mistakes++;
            draw(mistakes, body);
        } else {
            printf("Good guess!\n");
        }
    }

    if (numCorrect == lengthOfWord) {
        printf("Congratulations! You've guessed the word: %s\n", guessWord);
    } else {
        printf("You've been hanged! The word was: %s\n", guessWord);
    }

    return 0;
}
