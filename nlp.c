#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nlp.h"

static NlpEntry nlpEntries[MAX_NLP_ENTRIES];
static int nlpEntryCount = 0;

static void toLowerString(char* text)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
}

void loadNlpModel(const char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("NLP model file not found. Context ranking will use frequency only.\n");
        return;
    }

    char context[MAX_WORD_LENGTH];
    char word[MAX_WORD_LENGTH];
    int frequency;

    while (nlpEntryCount < MAX_NLP_ENTRIES &&
           fscanf(file, "%99s %99s %d", context, word, &frequency) == 3)
    {
        toLowerString(context);
        toLowerString(word);

        strcpy(nlpEntries[nlpEntryCount].context, context);
        strcpy(nlpEntries[nlpEntryCount].word, word);
        nlpEntries[nlpEntryCount].frequency = frequency;
        nlpEntryCount++;
    }

    fclose(file);
}

int getContextFrequency(const char* context, const char* word)
{
    if (context == NULL || word == NULL)
    {
        return 0;
    }

    for (int i = 0; i < nlpEntryCount; i++)
    {
        if (strcmp(nlpEntries[i].context, context) == 0 &&
            strcmp(nlpEntries[i].word, word) == 0)
        {
            return nlpEntries[i].frequency;
        }
    }

    return 0;
}

static int contextScore(const Suggestion* suggestion, const char* context)
{
    int contextualFrequency = getContextFrequency(context, suggestion->word);

    /*
     * Frequency remains the base signal.
     * Context is an additional signal, so a word does not need
     * a context entry in order to appear in the suggestions.
     */
    return suggestion->frequency + (contextualFrequency * 10);
}

static const char* currentContext = NULL;

static int compareContextSuggestions(const void* a, const void* b)
{
    const Suggestion* suggestionA = (const Suggestion*)a;
    const Suggestion* suggestionB = (const Suggestion*)b;

    int scoreA = contextScore(suggestionA, currentContext);
    int scoreB = contextScore(suggestionB, currentContext);

    if (scoreA != scoreB)
    {
        return scoreB - scoreA;
    }

    if (suggestionA->frequency != suggestionB->frequency)
    {
        return suggestionB->frequency - suggestionA->frequency;
    }

    return strcmp(suggestionA->word, suggestionB->word);
}

void rankContextSuggestions(Suggestion suggestions[], int suggestionCount,
                            const char* context)
{
    if (suggestions == NULL || suggestionCount <= 1 || context == NULL)
    {
        return;
    }

    currentContext = context;

    qsort(
        suggestions,
        suggestionCount,
        sizeof(Suggestion),
        compareContextSuggestions
    );

    currentContext = NULL;
}

void displayContextSuggestions(Suggestion suggestions[], int suggestionCount,
                               const char* context)
{
    printf("\n====================================\n");
    printf("NLP CONTEXT-AWARE SUGGESTIONS\n");
    printf("====================================\n");
    printf("Context: %s\n\n", context);

    for (int i = 0; i < suggestionCount; i++)
    {
        int contextualFrequency = getContextFrequency(context, suggestions[i].word);
        int score = suggestions[i].frequency + (contextualFrequency * 10);

        printf(
            "%d. %s (frequency: %d, context: %d, score: %d)\n",
            i + 1,
            suggestions[i].word,
            suggestions[i].frequency,
            contextualFrequency,
            score
        );
    }
}
