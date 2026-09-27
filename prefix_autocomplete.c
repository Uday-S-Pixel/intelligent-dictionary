#include <stdio.h>
#include <string.h>
#include "prefix_autocomplete.h"
#include "trie.h"

typedef struct
{
    char word[100];
    int frequency;

} WordFrequency;

#define MAX_SUGGESTIONS 1000

WordFrequency suggestions[MAX_SUGGESTIONS];

int suggestionCount = 0;


// PREFIX SEARCH

TrieNode* findPrefixNode(TrieNode* root, const char* prefix)
{
    TrieNode* current = root;

    while (*prefix != '\0')
    {
        int i = *prefix - 'a';

        if (current->children[i] == NULL)
        {
            return NULL;
        }

        current = current->children[i];

        prefix++;
    }

    return current;
}


// AUTO-COMPLETE HELPER

void autocompleteHelper(
    TrieNode* root,
    TrieNode* node,
    char* word,
    int level
)
{
    if (node->isLeaf)
    {
        word[level] = '\0';

        if (suggestionCount < MAX_SUGGESTIONS)
        {
            strcpy(
                suggestions[suggestionCount].word,
                word
            );

            suggestions[suggestionCount].frequency =
                getFrequency(root, word);

            suggestionCount++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            word[level] = 'a' + i;

            autocompleteHelper(
                root,
                node->children[i],
                word,
                level + 1
            );
        }
    }
}


// DISPLAY SUGGESTIONS

void DisplaySuggestions()
{
    printf("\n");
    printf("====================================\n");
    printf("AUTO-COMPLETE SUGGESTIONS\n");
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


// AUTO-COMPLETE

void autocomplete(
    TrieNode* root,
    const char* prefix
)
{
    suggestionCount = 0;

    TrieNode* prefixNode =
        findPrefixNode(root, prefix);

    if (prefixNode == NULL)
    {
        printf(
            "No words found for prefix \"%s\"\n",
            prefix
        );

        return;
    }

    char word[100];

    int level = 0;

    while (prefix[level] != '\0')
    {
        word[level] = prefix[level];

        level++;
    }

    autocompleteHelper(
        root,
        prefixNode,
        word,
        level
    );

    DisplaySuggestions();
}