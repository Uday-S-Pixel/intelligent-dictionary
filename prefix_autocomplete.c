#include <stdio.h>
#include <string.h>
#include "trie.h"


// =====================================================
// WORD + FREQUENCY STRUCTURE
// =====================================================

typedef struct
{
    char word[100];
    int frequency;

} WordFrequency;


// Maximum number of suggestions
#define MAX_SUGGESTIONS 1000


// Array to store autocomplete suggestions
WordFrequency suggestions[MAX_SUGGESTIONS];

int suggestionCount = 0;


// =====================================================
// PREFIX SEARCH
// =====================================================

TrieNode* PrefixSearch(TrieNode* root, const char* prefix)
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


// =====================================================
// GET FREQUENCY
// =====================================================

// For now, this function returns the frequency
// of a word.
//
// Later, you can connect this function to your
// Frequency & Ranking module.

int getFrequency(const char* word)
{
    /*
       Frequency module will provide the
       actual frequency of the word.

       Temporary value:
       return 0;
    */

    return 0;
}


// =====================================================
// AUTO-COMPLETE HELPER
// =====================================================

void AutoCompleteHelper(
    TrieNode* node,
    char* word,
    int level
)
{
    // Complete word found
    if (node->isLeaf)
    {
        word[level] = '\0';

        // Store word in array
        if (suggestionCount < MAX_SUGGESTIONS)
        {
            strcpy(
                suggestions[suggestionCount].word,
                word
            );

            // Store frequency
            suggestions[suggestionCount].frequency =
                getFrequency(word);

            suggestionCount++;
        }
    }


    // Search all 26 possible characters
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            word[level] = 'a' + i;

            AutoCompleteHelper(
                node->children[i],
                word,
                level + 1
            );
        }
    }
}


// =====================================================
// DISPLAY SUGGESTIONS
// =====================================================

void DisplaySuggestions()
{
    printf("\n");
    printf("====================================\n");
    printf("AUTO-COMPLETE SUGGESTIONS\n");
    printf("====================================\n");

    for (int i = 0; i < suggestionCount; i++)
    {
        printf(
            "%d. %s  (frequency: %d)\n",
            i + 1,
            suggestions[i].word,
            suggestions[i].frequency
        );
    }
}


// =====================================================
// AUTO-COMPLETE
// =====================================================

void AutoComplete(
    TrieNode* root,
    const char* prefix
)
{
    // Reset array for new search
    suggestionCount = 0;

    // Find prefix node
    TrieNode* prefixNode =
        PrefixSearch(root, prefix);

    if (prefixNode == NULL)
    {
        printf(
            "No words found for prefix \"%s\".\n",
            prefix
        );

        return;
    }

    // Array used to construct words
    char word[100];

    int level = 0;

    // Copy prefix
    while (prefix[level] != '\0')
    {
        word[level] = prefix[level];

        level++;
    }

    // Find all matching words
    AutoCompleteHelper(
        prefixNode,
        word,
        level
    );

    // Display stored suggestions
    DisplaySuggestions();
}
