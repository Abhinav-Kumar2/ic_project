#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 50
#define MAX_WORD_LENGTH 20
#define WORDS_TO_TYPE 3
#define TIME_LIMIT 20.0

void typingSpeedGame(float* timeTaken);
int getInputWithinTime(char* input, int maxLength, float remainingTime);

int main() {
    float times[1];  // Holds total time for a single round
    printf("Welcome to the Typing Speed Game!\n");
    printf("You need to type 3 words correctly within 20 seconds!\n\n");

    // Start the typing speed game
    typingSpeedGame(&times[0]);

    return 0;
}

void typingSpeedGame(float* timeTaken) {
    const char* words[MAX_WORDS] = {
        "adventure", "bloom", "citrus", "drift", "ember", "flourish",
        "galaxy", "harmony", "illuminate", "jolt", "kinetic", "luminous",
        "meadow", "nebula", "oasis", "ponder", "quasar", "radiant",
        "serendipity", "tranquil", "universe", "vortex", "wanderlust",
        "xenon", "yearn", "zenith", "azure", "blossom", "cascade",
        "dazzle", "euphoria", "fable", "glimmer", "haze", "infinity",
        "juggle", "kaleidoscope", "luminescent", "mirage", "nectar",
        "opulent", "pulse", "quench", "ripple", "solstice", "twilight",
        "unveil", "velvet", "whimsy", "zephyr"
    };

    clock_t startTime = clock();
    float totalElapsedTime = 0.0;

    for (int i = 0; i < WORDS_TO_TYPE; i++) {
        const char* chosenWord = words[rand() % MAX_WORDS];
        printf("Type the following word: %s\n", chosenWord);
        char userInput[MAX_WORD_LENGTH];
        float remainingTime = TIME_LIMIT - totalElapsedTime;

        // If time's already up, exit
        if (remainingTime <= 0) {
            printf("\nTime's up! You took too long.\n");
            return;
        }

        int result = getInputWithinTime(userInput, MAX_WORD_LENGTH, remainingTime);
        if (result == -1) {  // Time ran out
            printf("\nTime's up! You took too long.\n");
            return;
        }

        clock_t wordEndTime = clock();
        float wordTime = (double)(wordEndTime - startTime) / CLOCKS_PER_SEC;
        totalElapsedTime += wordTime;
        startTime = wordEndTime;  // Reset start time for the next word

        // Check if the word is correct
        if (strcmp(userInput, chosenWord) != 0) {
            printf("Incorrect. The correct word was: %s\n", chosenWord);
            return;
        }

        // Check total elapsed time
        if (totalElapsedTime > TIME_LIMIT) {
            printf("\nTime's up! You took too long.\n");
            return;
        }
    }

    *timeTaken = totalElapsedTime;
    printf("You typed all words correctly in %.2f seconds!\n", *timeTaken);
}

int getInputWithinTime(char* input, int maxLength, float remainingTime) {
    clock_t startTime = clock();
    float elapsedTime = 0;
    printf("You have %.2f seconds remaining...\n", remainingTime);
    fflush(stdout);

    while (elapsedTime < remainingTime) {
        // Try to get input from user
        if (fgets(input, maxLength, stdin) != NULL) {
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] == '\n') {
                input[len - 1] = '\0';  // Remove newline character
            }
            return 0;  // Success
        }

        // Update elapsed time
        clock_t currentTime = clock();
        elapsedTime = (float)(currentTime - startTime) / CLOCKS_PER_SEC;
        remainingTime -= elapsedTime;

        // Show remaining time
        printf("\rYou have %.2f seconds remaining...\n", remainingTime);
        fflush(stdout);

        // Reset startTime for accurate elapsed time calculation
        startTime = currentTime;
    }
    return -1;  // Time's up
}

