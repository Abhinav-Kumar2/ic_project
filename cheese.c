#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 5
#define MAX_WORD_LENGTH 20

void typingSpeedGame(float *timeTaken);

int main() {
    float times[MAX_WORDS];

    printf("Welcome to the Typing Speed Game!\n");
    printf("Type the words as fast as you can when they appear.\n\n");

    for (int i = 0; i < MAX_WORDS; i++) {
        typingSpeedGame(&times[i]);
    }

    float sum = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        sum += times[i];
    }

    printf("Your total time is %.2f seconds!\n", sum);

    return 0;
}

void typingSpeedGame(float *timeTaken) {
    const char *words[MAX_WORDS] = {"programming", "reaction", "keyboard", "computer", "speed"};
    srand(time(NULL));
    const char *chosenWord = words[rand() % MAX_WORDS];
    printf("Type the following word: %s\n", chosenWord);

    clock_t startTime = clock();
    char userInput[MAX_WORD_LENGTH];
    scanf("%s", userInput);
    clock_t endTime = clock();

    *timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    if (strcmp(userInput, chosenWord) == 0) {
        printf("Correct! You took %.2f seconds.\n", *timeTaken);
    } else {
        printf("Incorrect. The correct word was: %s\n", chosenWord);
    }
}

