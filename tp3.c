#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "TAD_paradigms.h"
#include "TAD_text.h"

int main(int argc, char *argv[]){
	if(argc != 4){
		printf("ERROR! THE PROGRAM MUST HAVE 3 ARGUMENTS.\n");
		exit(0);
	}	
	int i = 0, j = 0;
	int L = 0, H = 0, x = 0, k = 0, num_words = 0;
	TypeWord *wordsList;
	FILE *input, *output;
	char *paradigm;
	paradigm = argv[1];
	input = fopen(argv[2], "r");
	output = fopen(argv[3], "w");

	// Get values from the input file, including a list of words from the original text.
	wordsList = Get_words(input, &num_words, &L, &H, &x, &k);

	// Array to store the sequence of the positions that should have a line break in the justified text.
	int *linebreaks_indexes;
	linebreaks_indexes = (int*) malloc((num_words+1) *sizeof(int));
	for(j = 0; j <= num_words; j++){
		linebreaks_indexes[j] = -1;			
	}

	// Solution using brute-force paradigm. 
	if(strcmp(paradigm,"-b") == 0)
		fprintf(output, "%d", (int) Bruteforce(wordsList, linebreaks_indexes, 0, L, H, x, k, num_words, 0));

	// Solution using greedy paradigm.
	else if(strcmp(paradigm,"-g") == 0)
		fprintf(output, "%d", (int) Greedy(wordsList, linebreaks_indexes, L, H, x, k, num_words));

	// Solution using dynamic programming paradigm.
	else if(strcmp(paradigm,"-d") == 0){
		int **memo = NULL;
		int ***memo_linebreaks = NULL;
		Create_memo_array(&memo , &memo_linebreaks, num_words);
		fprintf(output, "%d", (int) Dynamic_programming(wordsList, linebreaks_indexes, 
			0, L, H, x, k, num_words, 0, memo, memo_linebreaks));
		Free_memo_array(memo , memo_linebreaks, num_words);
	}		

	// Print justified text in output file.
	Print_text(output, wordsList, linebreaks_indexes, num_words);

	// Desalocate the memory used dynamicly.
	for(i = 0; i < num_words; i++){
		free(wordsList[i].word);
	}
	free(wordsList);  
	free(linebreaks_indexes);
	fclose(input);
	fclose(output);
	return 0;
}