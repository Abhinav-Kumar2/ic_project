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
	printf("Each guess must be a valid five-letter word.\nThe color of a tile will change to show you how close your guess was.\nIf the tile turns green, the letter is in the word, and it is in the correct spot.\nIf the tile turns yellow, the letter is in the word, but it is not in the correct spot.\nIf the tile turns gray, the letter is not in the word.");
	wordgen();
	float sanity = 1;
	char entered[6];
	char given[6];
	int lives = 5;
	srand(time(NULL));
	int num = rand();
	int index = num % 18;
	strcpy(given, words[index].word);
	while (strcmp(entered, given) && lives != 0) {
		printf("\nEnter a word:");
		scanf("%s", entered);
		while (strlen(entered)!=5) {
			printf("\nInvalid length.\nEnter a word:");
			scanf("%s", entered);
		}
		int newr = rand();
		int newrr = newr % 5;	
		float x = (float)newr / (float)(RAND_MAX / 1);
		if (x > sanity && strcmp(entered,given)!=0) { entered[newrr] = trp[newrr]; }
		printf("\033[F\033[K");
		//printf("\ngiven:%s entered:%s\n",given,entered);
		check(entered, given);
		if(strcmp(entered,given))lives--;
	}
	if (lives == 0) {
		printf("\nAs expected, you couldn't guess a simple damn word... The word was %s. It means %s", given,words[index].meaning);
	}
	else {
		printf("\nHuh, don't get too haughty. You just guessed one word. Let me enlighten you with its meaning. It means %s", words[index].meaning);
	}
    return 0;
}

