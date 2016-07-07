#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "TAD_text.h"

void Split_text(TypeWord *wordsList, char *text, int text_length){
	int i = 0, j = 0, m = 0;
	// Store all the words from the text into the vector.
	while(i < text_length){
		if(!isblank(text[i]) && text[i] != '\0' && text[i] != EOF && text[i] != '\n'){
			wordsList[j].word[m] = text[i];
			m++;
		}
		else{
			wordsList[j].length = m;
			j++;
			m = 0;
		}
		i++; 
	}
}

void Num_words_text(char *text, int text_length, int *num_words, int *longest_word_length){
	int i = 0, count = 0;

	// Count the number of words in the text, by calculating the number of spaces between words.
	while(i <= text_length){
		if(isblank(text[i]) || text[i] == '\0' || text[i] == EOF){
			(*num_words)++;
			if(count > (*longest_word_length))
				*longest_word_length = count;		
			count = 0;
		}			
		count++;
		i++; 
	}

	// Verify the size of the longest word from the text.
	if(count > (*longest_word_length))
		*longest_word_length = count;
}

TypeWord* Get_words(FILE* input, int* num_words, int* L, int* H, int* x, int* k){
	int text_length = 0, longest_word_length = 0, i = 0, j = 0;
	char line1[1000];
	char line2[1000];

	// Get L and H values.
	fgets(line1, 1000, input);
	sscanf (line1,"%d %d", L, H);

	// Get x and k values.
	fgets(line2, 1000, input);
	sscanf (line2,"%d %d", x, k);

	// Get text's length.
	long int cursor_position = 0;
	cursor_position = ftell(input);
	fseek(input, 0, SEEK_END);
	text_length = ftell(input) - cursor_position;
	fseek(input, cursor_position, 0);

	// Get the text.
	char text[text_length + 2];
	fgets(text, text_length + 1, input);

	// Get the number of words in the text.
	Num_words_text(text, text_length, num_words, &longest_word_length);

	// Create a words vector to store all the words from the text.
	TypeWord *wordsList = (TypeWord*) malloc((*num_words)*sizeof(TypeWord));  
	for(i = 0; i < (*num_words); i++){
		wordsList[i].word = (char*) malloc((longest_word_length + 1)*sizeof(char));
		for(j = 0; j <= longest_word_length; j++)
			wordsList[i].word[j] = 0;
	}

	// Split the text into words and put them into the vector "wordsList" .
	Split_text(wordsList, text, text_length);

	return wordsList;
}
