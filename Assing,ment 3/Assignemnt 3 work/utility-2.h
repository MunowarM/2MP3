#ifndef UTILITY_H
#define UTILITY_H

// Define constants
#define ARRAY_SIZE 20
#define MAX_STRING_LENGTH 200
#define LINE_LENGTH 100

// Positive words array
#define POSITIVE_INTENSIFIERS_SIZE 11
static char *positive_intensifiers[] = {
	"absolutely",
	"completely",
	"extremely",
	"really",
	"so",
	"totally",
	"very",
	"particularly",
	"exceptionally",
	"incredibly",
	"remarkably",
};

// Negative words array
#define NEGATIVE_INTENSIFIERS_SIZE 9
static char *negative_intensifiers[] = {
	"barely",
	"hardly",
	"scarcely",
	"somewhat",
	"mildly",
	"slightly",
	"partially",
	"fairly",
	"pretty much",
};

// Negation words array
#define NEGATIONS_SIZE 13
static char *negation_words[] = {
	"not",
	"isn't",
	"doesn't",
	"wasn't",
	"shouldn't",
	"won't",
	"cannot",
	"can't",
	"nor",
	"neither",
	"without",
	"lack",
	"missing",
};

// The boost from different amplifiers
#define INTENSIFIER 0.293
#define EXCLAMATION 0.292
#define CAPS 1.5
#define NEGATION -0.5


// Include necessary libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

// Define the structure for the data
typedef struct {
	char word[MAX_STRING_LENGTH];
	float value1;
	float value2;
	int intArray[ARRAY_SIZE];
} WordData;

// Structure to hold the sentiment analysis results
typedef struct {
    float pos;
    float neg;
    float neu;
    float compound;
} SentimentResult;

// Function prototypes
WordData *read_lexicon_file(const char *filename, int *word_count); // Reads lexicon file
SentimentResult calculate_sentiment_score(const char *sentence, WordData *lexicon, int word_count); // Calculates sentiment score for a sentence
WordData find_data(WordData *data, char *word);          // Searches for a word in the WordData array
int is_all_caps(const char* word);                       // Returns true if word is all caps

#endif