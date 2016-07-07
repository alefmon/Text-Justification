#ifndef PARADIGMS_H
#define PARADIGMS_H
#include "TAD_text.h"

#define infinity INT_MAX

//The function calculates A+B.
int sum(int A, int B);

// The function gets the length of the line (i,j).
int Line_length(TypeWord *wordsList, int i, int j);

// The function calculates the cost of the line(i,j)
double Line_cost(TypeWord *wordsList, int i, int j, int L, int H, int x, int k);

// The funtion prints the justified text in the output file.
void Print_text(FILE* output, TypeWord *wordsList, int *linebreaks_indexes, int num_words);

// The function solves the text justification problem using the brute-force paradigm.
double Bruteforce(TypeWord *wordsList, int *linebreaks_indexes, 
	int i, int L, int H, int x, int k, int num_words, int num_lines);

// The function solves the text justification problem using dynamic programming.
double Dynamic_programming(TypeWord *wordsList, int *linebreaks_indexes, int i, int L, int H, 
	int x, int k, int num_words, int num_lines, int **memo, int*** memo_linebreaks);

// The function solves the text justification problem using the greedy heuristic.
double Greedy(TypeWord *wordsList, int *linebreaks_indexes, int L, int H, int x, int k, int num_words);

// The function allocates memory for the new memoization array.
void Create_memo_array(int*** memo , int**** memo_linebreaks, int num_words);

// The function desallocates the memory used in the memoization techinique.
void Free_memo_array(int** memo , int*** memo_linebreaks, int num_words);


#endif
