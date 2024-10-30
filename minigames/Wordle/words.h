#pragma once
#include <stdio.h>
#include<string.h>

typedef struct {
    char word[6]; 
    char meaning[100]; 
}Word;
Word words[18];

char trp[6] = {'x','/','4','~','=','}'};
void wordgen(){
	FILE* fptr;
	fptr=fopen("words.txt","r");
    char line [160];
    int w=0;
    if(fptr!=NULL){
        while(fgets(line,sizeof line,fptr)!= NULL && w<18) /* read a line from a file */ {
        line[strcspn(line,"\n")]=0;
        char eword[6]={0};
        char emeaning[70]={0};
        int status=0;
        //printf("%c",line[strlen(line)-1]);
        for(int i=0;i<strlen(line);i++){
            //printf("%c %d",line[i],line[i]!=':');
            if(line[i]!=':'){
                if(status==0) strncat(eword,&line[i],1);
                else strncat(emeaning,&line[i],1);
            }
            else{
                status=1;
            }
        } 
        strcpy(words[w].word,eword);
        strcpy(words[w].meaning,emeaning);
        words[w].word[5] = '\0'; // Ensure null-termination
        words[w].meaning[70] = '\0'; // Ensure null-termination
      w++;
    }
    

	fclose(fptr);
    }
}
