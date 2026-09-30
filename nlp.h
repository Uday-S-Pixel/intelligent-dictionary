#ifndef NLP_H
#define NLP_H

#include "prefix_autocomplete.h"

#define MAX_NLP_ENTRIES 2000

/*
 * Lightweight NLP extension.
 * The model stores context-word pairs and their observed counts.
 */
typedef struct
{
    char context[MAX_WORD_LENGTH];
    char word[MAX_WORD_LENGTH];
    int frequency;
} NlpEntry;

void loadNlpModel(const char* filename);
int getContextFrequency(const char* context, const char* word);
void rankContextSuggestions(Suggestion suggestions[], int suggestionCount,
                            const char* context);
void displayContextSuggestions(Suggestion suggestions[], int suggestionCount,
                               const char* context);

#endif
