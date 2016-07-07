#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "TAD_paradigms.h"

int sum(int A, int B){
	if(A == infinity || B == infinity)
		return infinity;
	if(A > (infinity - B))
		return infinity;
	if(B > (infinity - A))
		return infinity;
	return A+B;
}

int Line_length(TypeWord *wordsList, int i, int j){
	int m = 0, length = 0, num_spaces = 0;

	// Add the length of each word in line.
	for(m = i; m < j; m++)
		length += wordsList[m].length;

	// Add the number of spaces between words.
	num_spaces = j - i - 1;
	length += num_spaces;
	return length;
}

double Line_cost(TypeWord *wordsList, int i, int j, int L, int H, int x, int k){
	int length = 0;
	double cost;

	// Verify the length of the line.
	length = Line_length(wordsList, i, j);
	if( length > L)
		return infinity;

	// Return the line cost.
	cost = k * (pow ((L - length), x));
	return cost;
}

double Bruteforce(TypeWord *wordsList, int *linebreaks_indexes, 
	int i, int L, int H, int x, int k, int num_words, int num_lines){
		int j = 0, m = 0, line_end = 0;
		double minimum_cost = infinity, total_cost = 0, line_i_to_j_cost = 0;

		// Recursion's stopping condition.
		if(num_lines > H)
			return infinity;		
		if(i == num_words ){	
			linebreaks_indexes[0] = num_words;
			return  k * (pow((H - num_lines), x));
		}

		// For each j in range [i+1, n], calculate the line cost when the line break is right after j.
		for(j = i + 1; j <= num_words; j++){
			int *break_index = (int*) malloc((num_words+1) * sizeof(int));
			for(m = 0; m <=num_words; m++){
				break_index[m] = 0;			
			}	
			
			// Calculate the line cost and the total cost.
			line_i_to_j_cost = Line_cost(wordsList, i, j, L, H, x, k);
			if(line_i_to_j_cost != infinity){
				total_cost = sum(line_i_to_j_cost, Bruteforce(wordsList, break_index,
					j, L, H, x, k, num_words, num_lines + 1));
			}
			else
				total_cost = infinity;	

			// Store the minimum cost and the sequence of line breaks that generated minimum cost.
			if(minimum_cost > total_cost){
				minimum_cost = total_cost;
				line_end = j - 1;
				for(m = 1; m <= num_words; m++){	
					linebreaks_indexes[m] = break_index[m - 1];
				}
				linebreaks_indexes[0] = line_end;
			}
			free(break_index);
		}
		return minimum_cost;
}

double Dynamic_programming(TypeWord *wordsList, int *linebreaks_indexes,	int i, int L, int H, 
	int x, int k, int num_words, int num_lines, int **memo, int*** memo_linebreaks){
		int j = 0, m = 0, line_end = 0;
		double minimum_cost = infinity, total_cost = 0, line_i_to_j_cost = 0;

		// Recursion's stopping condition.
		if(num_lines > H)
			return infinity;
		if(i == num_words){	
			linebreaks_indexes[0] = num_words;
			return  k * (pow((H - num_lines), x));
		}
		
		// Avoid repeated recursion calls, using Memoization.
		if(memo[i][num_lines] != -1){
			for(m = 0; m <= num_words; m++){	
				linebreaks_indexes[m] = memo_linebreaks[i][num_lines][m];	
			}
			return memo[i][num_lines];
		}

		// For each j in range [i+1, n], calculate the line cost when the break line is right after j.
		for(j = i + 1; j <= num_words; j++){
			int *break_index = (int*) malloc((num_words+1) * sizeof(int));
			for(m = 0; m <=num_words; m++){
				break_index[m] = 0;			
			}

			// Calculate the line cost and the total cost.
			line_i_to_j_cost = Line_cost(wordsList, i, j, L, H, x, k);			
			if(line_i_to_j_cost != infinity){
				total_cost = sum(line_i_to_j_cost, Dynamic_programming(wordsList, break_index, j, L, H, 
					x, k, num_words, num_lines + 1, memo, memo_linebreaks));
			}
			else
				total_cost = infinity;
					
			// Store the minimum cost and the sequence of line breaks that generated minimum cost.			
			if(minimum_cost > total_cost){
				minimum_cost = total_cost;
				line_end = j - 1;
				for(m = 1; m <= num_words; m++){	
					linebreaks_indexes[m] = break_index[m - 1];
				}
				linebreaks_indexes[0] = line_end;
			}
			free(break_index);
		}

		// Use Memoization to store the minimum cost and the sequence of break lines that generated
		// minimum cost, to avoid repeated recursion calls.
		memo[i][num_lines] = minimum_cost;
		for(m = 0; m <= num_words; m++){	
			memo_linebreaks[i][num_lines][m] = linebreaks_indexes[m];	
		}
		return minimum_cost;
}

void Create_memo_array(int*** memo , int**** memo_linebreaks, int num_words){
	int i = 0, j = 0, m = 0;
	*memo = (int**) malloc((num_words + 1) *sizeof(int*));
	*memo_linebreaks = (int***) malloc((num_words + 1) *sizeof(int**));
	for(j = 0; j <= num_words; j++){
		(*memo)[j] = (int*) malloc((num_words + 1) *sizeof(int));
		(*memo_linebreaks)[j] = (int**) malloc((num_words + 1) *sizeof(int*));			
	}
	for(i = 0; i <= num_words; i++){
		for(j = 0; j <= num_words; j++){
			(*memo)[i][j] = -1;	
			(*memo_linebreaks)[i][j] = (int*) malloc((num_words + 1) *sizeof(int));	
			for(m = 0; m <= num_words; m++)
				(*memo_linebreaks)[i][j][m] = 0;
		}
	}
}

void Free_memo_array(int** memo , int*** memo_linebreaks, int num_words){
	int i = 0, j = 0;	
	for(i = 0; i <= num_words; i++){
		for(j = 0; j <= num_words; j++){
			free (memo_linebreaks[i][j]);	
		}
	}
	for(j = 0; j <= num_words; j++){
		free (memo[j]);
		free (memo_linebreaks[j]);			
	}	
	free (memo);
	free (memo_linebreaks);
}

double Greedy(TypeWord *wordsList, int *linebreaks_indexes, int L, int H, int x, int k, int num_words){
	int j = 0, line_capacity = 0, line_beginning = 0, line_end = 0, num_lines = 0, line_cost = 0;
	double total_cost = 0;
	
	// Create new lines to store all words from the vector.
	while(j < num_words){
		// While is possible, add words in the new line.
		while(j < num_words){
			if(line_capacity + wordsList[j].length <= L){
				line_capacity += wordsList[j].length + 1;
				j++;
			}
			else
				break;	
		}

		// When is not possible anymore, store the beggining and the end of the line, then go to the next line.
		line_end = j - 1;
		linebreaks_indexes[num_lines] = line_end;
		num_lines++;

		// Add the cost of the created line to the total cost.
		line_cost = Line_cost(wordsList, line_beginning, line_end + 1, L, H, x, k);
		total_cost = sum(total_cost, line_cost);
		line_capacity = 0;
		line_beginning = j;
	}
	
	// Return total cost of the function.
	if(num_lines > H)
		return infinity;	
	total_cost = sum(total_cost, k * (pow((H - num_lines), x)));
	return total_cost;
}

void Print_text(FILE* output, TypeWord *wordsList, int *linebreaks_indexes, int num_words){
	int i = 0, j = 0, line_beginning = 0, line_end = 0;

	// Print each line, until function prints the last word of the text.
 	while(linebreaks_indexes[i] < num_words && linebreaks_indexes[i] != -1){
		if(i != 0)
			line_beginning = linebreaks_indexes[i - 1] + 1;
		line_end = linebreaks_indexes[i];
		j = line_beginning;
		fprintf(output, "\n");
		while(j <= line_end){
			if(j != line_beginning)
	  			fprintf(output, " ");
			fprintf(output, "%s", wordsList[j].word);
			j++;
		}
		i++;
	}
}
