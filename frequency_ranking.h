#ifndef FREQUENCY_RANKING_H
#define FREQUENCY_RANKING_H

#include "prefix_autocomplete.h"

void rankSuggestions(Suggestion suggestions[], int suggestionCount);
void displayFrequency(TrieNode* root, const char* word);
void displayRanking(Suggestion suggestions[], int suggestionCount);

#endif
