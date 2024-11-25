#include "words.h"
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include<time.h>
#include<ctype.h>


void green() {
	printf("\033[0;32m");
}

void yellow() {
	printf("\033[0;33m");
}
void white() {
	printf("\033[0;37m");
}

void check(char* entered, char* given) {
	int states[5] = { 0 };
	for (int i = 0; i < 5; i++) {
		int m = 0;
		white();
		if (tolower(entered[i]) == given[i]) {
			states[i] = 1;
			green();
			printf("%c", tolower(entered[i]));
			white();
			continue;
		}
		else {
			for (int j = 0; j < 5; j++) {
				if (tolower(entered[i]) == given[j] && given[j] != entered[j] && states[j]==0) {
					states[j] = 1;
					m = 1;
					yellow(); 
					printf("%c", tolower(entered[i]));
					white();
					break;
				}
			}
		}
		if(m==0) printf("%c", tolower(entered[i]));
	}
}

int main() {
	printf("\"Welcome to this place of mine! I like to call it the detective's prison! I had to work quite hard to catch you.\"\n");
	printf("I am sure you must be wondering quite a bit on why I brought you here. You'll get your reasons in some time for sure!\n");
	printf("\nTill then, we can start off things with your favorite passtime! Wordle!!!\n");
	printf("\nHere are the rules for the game - You have to guess a five letter word that would be a key to progress further ahead!\n");
	printf("You will type the word you want to guess on the screen in front of you. You will have five chances to guess. \n");
	printf("If one of your guessed letter exists in the word but at a different position, then your letter will turn yellow.\n");
	printf("Whereas if your letter is in the word and at the position you guessed, it will highlight green! Good Luck!\n");
	printf("\nGuess here:");
	float sanity = 1;
	char entered[6];
	char given[6];
	int lives = 5;
	srand(time(NULL));
	int num = rand();
	int index = num % 18;
	strcpy(given, words[index].word);
	while (strcmp(entered, given) && lives != 0) {
		printf("\n");
		scanf("%s", entered);
		while (strlen(entered)!=5) {
			printf("\nInvalid length.\n");
			scanf("Enter a word: %s", entered);
		}
		int newr = rand();
		int newrr = newr % 5;	
		float x = (float)newr / (float)(RAND_MAX / 1);
		if (x > sanity && strcmp(entered,given)!=0) { entered[newrr] = trp[newrr]; }
		printf("\033[F\033[K");
		check(entered, given);
		if(strcmp(entered,given))lives--;
	}
	if (lives == 0) {
		printf("\nYou spend your mornings awayon these game and you couldn't even guess a simple word?!! The word %s. It means %s", given,words[index].meaning);
	}
	else {
		printf("\nAs expected, the great detective guessed the correct word! Let me enlighten you with its meaning. It means %s", words[index].meaning);
	}
    return 0;
}
