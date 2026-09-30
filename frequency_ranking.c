#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency_ranking.h"

static int compareFrequency(const void* a, const void* b)
{
    const Suggestion* suggestionA = (const Suggestion*)a;
    const Suggestion* suggestionB = (const Suggestion*)b;

    if (suggestionA->frequency != suggestionB->frequency)
    {
        return suggestionB->frequency - suggestionA->frequency;
    }

    return strcmp(suggestionA->word, suggestionB->word);
}

void rankSuggestions(Suggestion suggestions[], int suggestionCount)
{
    if (suggestions == NULL || suggestionCount <= 1)
    {
        return;
    }

    qsort(
        suggestions,
        suggestionCount,
        sizeof(Suggestion),
        compareFrequency
    );
}

void displayFrequency(TrieNode* root, const char* word)
{
    printf("%s : %d\n", word, getFrequency(root, word));
}

void displayRanking(Suggestion suggestions[], int suggestionCount)
{
    printf("\n====================================\n");
    printf("WORD RANKING\n");
    printf("====================================\n");

    for (int i = 0; i < suggestionCount; i++)
    {
        printf(
            "%d. %s (frequency: %d)\n",
            i + 1,
            suggestions[i].word,
            suggestions[i].frequency
        );
    }
}
