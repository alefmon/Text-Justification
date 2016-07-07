#ifndef TEXT_H
#define TEXT_H

// Define a new struct that will be used to store the word and the word's length.
typedef struct{
	char *word;
	int length;
}TypeWord;

// The function splits the text into words and put them in a vector.
void Split_text(TypeWord *wordsList, char *text, int text_length);

// The function calculates the number of words in the text.
void Num_words_text(char *text, int text_length, int *num_words, int *longest_word_length);

// The function gets the values of L, H, x and k. In addition to that, the function returns a word 
// vector that contains all words from the text.
TypeWord* Get_words(FILE* input, int* num_words, int* L, int* H, int* x, int* k);

#endif
