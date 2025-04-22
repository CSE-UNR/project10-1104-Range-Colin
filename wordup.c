//Colin Range
//Project 10

#include <stdio.h>
#define str_cap 6
#define maxGuess 6
#define readWord "mystery.txt"

void getWord(char word[]);
void userGuess(char guess[], int round);
int allLetters(char guess[]);
void checkGuess(char guess[], char word[], char disp[][str_cap], char feedback[][str_cap], int round);
void dispGuess(char disp[][str_cap], char feedback[][str_cap], int round);
int correct(char guess[], char word[]);

int main(){
	char guess[str_cap];
	char word[str_cap];
	char disp[maxGuess][str_cap];
	char feedback[maxGuess][str_cap];
	
	int guessNum = 0;
	int win = 0;
	
	
	getWord(word);
	
	while (guessNum < maxGuess && !win){
		userGuess(guess, guessNum);
		
		while (!allLetters(guess)){
			printf("Your guess must be 5 letters long.\nPlease try again: ");
			userGuess(guess, guessNum);
		}
		
	checkGuess(guess, word, disp, feedback, guessNum);
	dispGuess(disp, feedback, guessNum + 1);
	
	win = correct(guess, word);
	guessNum++;
	
	}

	if (win){
		printf("You guessed it!\n");
	}else{
		printf("You lost, better luck next time!\n");
	}
	
	return 0;
}

void getWord(char word[]){
	FILE *file = fopen("mystery.txt", "r");
	if (file == NULL){
		printf("Error opening mystery.txt\n");
		return;
	}
	
	fscanf(file, "%s", word);
	fclose(file);
}

void userGuess(char guess[], int round){
	printf("GUESS %d! Enter your guess: ", round + 1);
	scanf("%s", guess);
	
	for(int i = 0; i<5; i++){
		if(guess[i] >= 'A' && guess[i] <= 'Z'){
			guess[i] = guess[i] + 32;
		}
	}
	guess[5] = '\0';
}
	
int allLetters(char guess[]){
	for(int i = 0; i < 5; i++){
		if((guess[i] < 'a' || guess[i] > 'z') && (guess[i] < 'A' || guess[i] > 'Z')){
			return 0;
		}
	}
	if(guess[str_cap - 1] != '\0'){
		return 0;
	}
	
	return 1;	
}

void checkGuess(char guess[], char word[], char disp[][str_cap], char feedback[][str_cap], int round){

	for (int i = 0; i < 5; i++){
		if (guess[i] == word[i]) {
			disp[round][i] = guess[i] - 32;
			feedback[round][i] = ' ';
		} else {
			disp[round][i] = guess[i];
			feedback[round][i] = ' ';
		}
	}
	
	for (int i = 0; i < 5; i++) {
		
		int isCapital =(disp[round][i] >= 'A' && disp[round][i] <= 'Z'); 
		
		
		if (isCapital == 0){
			for (int j = 0; j < 5; j++) {
				if(guess[i] == word[j]){
					feedback[round][i] = '^';
					break;
			}
		}
	}
}
	
	disp[round][5] = '\0';
	feedback[round][5] = '\0';
}

void dispGuess(char disp[][str_cap], char feedback[][str_cap], int round){
	printf("\n");
	for(int i = 0; i < round; i++) {
		printf("%s\n", disp[i]);
		printf("%s\n", feedback[i]);
	}
	printf("\n");
}

int correct(char guess[], char word[]){
	for(int i = 0; i < 5; i++) {
		if(guess[i] != word[i]){
			return 0;
		}
	}
	return 1;
}
