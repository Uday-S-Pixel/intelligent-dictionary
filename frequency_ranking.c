```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequency_ranking.h"


// =====================================================
// FREQUENCY RECORD
// =====================================================

typedef struct
{
    char word[100];
    int frequency;

} WordFrequency;


// Array to store word frequencies
WordFrequency frequencyList[1000];

int frequencyCount = 0;


// =====================================================
// FIND WORD IN FREQUENCY LIST
// =====================================================

int findWord(const char* word)
{
    for (int i = 0; i < frequencyCount; i++)
    {
        if (strcmp(frequencyList[i].word, word) == 0)
        {
            return i;
        }
    }

    return -1;
}


// =====================================================
// ADD WORD TO FREQUENCY LIST
// =====================================================

void addWord(const char* word)
{
    int index = findWord(word);

    // Word already exists
    if (index != -1)
    {
        return;
    }

    // Add new word
    if (frequencyCount < 1000)
    {
        strcpy(frequencyList[frequencyCount].word, word);
        frequencyList[frequencyCount].frequency = 0;

        frequencyCount++;
    }
}


// =====================================================
// INCREASE WORD FREQUENCY
// =====================================================

void increaseFrequency(const char* word)
{
    int index = findWord(word);

    // If word is not present, add it
    if (index == -1)
    {
        addWord(word);
        index = frequencyCount - 1;
    }

    frequencyList[index].frequency++;
}


// =====================================================
// GET WORD FREQUENCY
// =====================================================

int getFrequency(const char* word)
{
    int index = findWord(word);

    if (index == -1)
    {
        return 0;
    }

    return frequencyList[index].frequency;
}


// =====================================================
// COMPARE WORDS FOR RANKING
// =====================================================

int compareFrequency(const void* a, const void* b)
{
    const WordFrequency* wordA = (const WordFrequency*)a;
    const WordFrequency* wordB = (const WordFrequency*)b;

    // Higher frequency comes first
    if (wordA->frequency != wordB->frequency)
    {
        return wordB->frequency - wordA->frequency;
    }

    // If frequency is same,
    // alphabetical order
    return strcmp(wordA->word, wordB->word);
}


// =====================================================
// RANK WORDS
// =====================================================

void rankWords(void)
{
    qsort(
        frequencyList,
        frequencyCount,
        sizeof(WordFrequency),
        compareFrequency
    );
}


// =====================================================
// DISPLAY FREQUENCY
// =====================================================

void displayFrequency(void)
{
    printf("\n====================================\n");
    printf("WORD FREQUENCY\n");
    printf("====================================\n");

    for (int i = 0; i < frequencyCount; i++)
    {
        printf(
            "%s : %d\n",
            frequencyList[i].word,
            frequencyList[i].frequency
        );
    }
}


// =====================================================
// DISPLAY RANKING
// =====================================================

void displayRanking(void)
{
    rankWords();

    printf("\n====================================\n");
    print
```
