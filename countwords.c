#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
/*
	Name: Luciano Caminata
	PID: 4734845
	"I certify that this program is entirely my own work and none of it is the work of another person."

	This program is set up to read from either an input file or user input and return the total amount of words found on input. If -l is on the command line the longest word is also output, -s would return the shortest word. 
*/
void findInput(int size, char *list[]);
int totalWords(char* input);
char* inputText(FILE *file);
void getMax(char* input);
void getMin(char* input);
void getOp(int size, char *arg[], char* input);

int main(int argc, char *argv[]) {
	findInput(argc, argv);
	return 0;
}

/*
	Will determine whether there is an input file or not and take the input of the file or of the terminal. Calls the method to find the total amount of words as well as the operation method to see if the user wishes to find the longest or shortest words on the input. 
*/
void findInput(int size, char *list[]) {
	char* inputFile = list[size - 1];
	if((strcmp(inputFile, "-l")) == 0 || (strcmp(inputFile, "-s")) == 0 || (strcmp(inputFile, " ")) == 0 || size == 1) {
		printf("No file found. Please input a sentence.\n");
		char input[100];
		scanf("%[^\n]%*c", input);
		printf("Input: %s\n", input);
		printf("Total Words: %d\n", totalWords(input) + 1);
		getOp(size, list, input);
	} else {
		char* input;
		FILE *file = fopen(inputFile, "r");
		input = inputText(file);
		printf("Input: %s", input);
		printf("Total Words: %d\n", totalWords(input));
		getOp(size, list, input);
	}
}

/*
	Checks the command line to see whether or not the user wishes to ask the program to find the longest & shortest words.
*/
void getOp(int size, char *arg[], char* input) {
	int c, error = 0;
	while((c = getopt(size, arg, "sl")) != -1) {
		switch(c) {
			case 's':
				getMin(input);
				break;
			case 'l':
				getMax(input);
				break;
			case '?':
				error = 1;
				break;
		}
	}
	if(error) {
		printf("Cannot recognize command line argument.\n");
	}
}

/*
	returns the total amount of words found on the input.
*/
int totalWords(char* input) {
	int count = 0;
	int i;
	for(i = 0; i < strlen(input); i++) {
		if(!isalnum(input[i])) {
			count++;
		}
	}
	return count;
}

/*
	Allocates the space needed for the char array to take in the input text. 
*/
char* inputText(FILE *file) {
	int c, size = 0;
	size_t space = 1;
	char* temp = malloc(space);
	while((c = getc(file)) != EOF) {
		temp[size++] = (char)c;
		space++;
		temp = realloc(temp, space);
	}
	return temp;
}

/*
	Finds the longest word.
*/
void getMax(char* input) {
	char maxWord[strlen(input)], word[strlen(input)];
	int i, length = 0, check = 0;
	for(i = 0; i < strlen(input); i++) {
		while(i < strlen(input) && !isspace(input[i]) &&isalnum(input[i])) {
			word[length++] = input[i++];
		}
		if(length != 0) {
			word[length] = '\0';
			if(!check) {
				check = !check;
				strcpy(maxWord, word);
			}
			if(strlen(word) > strlen(maxWord)) {
				strcpy(maxWord, word);
			}
			length = 0;
		}
	}
	printf("Longest word: %s\n", maxWord);
}

/*
	Finds the shortest word.
*/
void getMin(char* input) {
	char minWord[strlen(input)], word[strlen(input)];
	int i, length = 0, check = 0;
	for(i = 0; i < strlen(input); i++) {
		while(i < strlen(input) && !isspace(input[i]) &&isalnum(input[i])) {
			word[length++] = input[i++];
		}
		if(length != 0) {
			word[length] = '\0';
			if(!check) {
				check = !check;
				strcpy(minWord, word);
			}
			if(strlen(word) < strlen(minWord)) {
				strcpy(minWord, word);
			}
			length = 0;
		}
	}
	printf("Shortest word: %s\n", minWord);
}
