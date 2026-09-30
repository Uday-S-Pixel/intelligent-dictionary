#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prefix_autocomplete.h"
#include "frequency_ranking.h"

TrieNode* findPrefixNode(TrieNode* root, const char* prefix)
{
    if (root == NULL || prefix == NULL)
    {
        return NULL;
    }

    TrieNode* current = root;

    while (*prefix != '\0')
    {
        char ch = *prefix;

        if (ch >= 'A' && ch <= 'Z')
        {
            ch = (char)(ch - 'A' + 'a');
        }

        if (ch < 'a' || ch > 'z')
        {
            return NULL;
        }

        int i = ch - 'a';

        if (current->children[i] == NULL)
        {
            return NULL;
        }

        current = current->children[i];
        prefix++;
    }

    return current;
}

void autocompleteHelper(
    TrieNode* root,
    TrieNode* node,
    char* word,
    int level,
    Suggestion suggestions[],
    int* suggestionCount,
    int maxSuggestions
)
{
    if (node == NULL || *suggestionCount >= maxSuggestions)
    {
        return;
    }

    if (node->isLeaf)
    {
        word[level] = '\0';

        strcpy(suggestions[*suggestionCount].word, word);
        suggestions[*suggestionCount].frequency = getFrequency(root, word);
        (*suggestionCount)++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            word[level] = (char)('a' + i);

            autocompleteHelper(
                root,
                node->children[i],
                word,
                level + 1,
                suggestions,
                suggestionCount,
                maxSuggestions
            );
        }
    }
}

int collectSuggestions(
    TrieNode* root,
    const char* prefix,
    Suggestion suggestions[],
    int maxSuggestions
)
{
    if (root == NULL || prefix == NULL || suggestions == NULL || maxSuggestions <= 0)
    {
        return 0;
    }

    TrieNode* prefixNode = findPrefixNode(root, prefix);

    if (prefixNode == NULL)
    {
        return 0;
    }

    char word[MAX_WORD_LENGTH];
    int level = 0;

    while (prefix[level] != '\0' && level < MAX_WORD_LENGTH - 1)
    {
        char ch = prefix[level];

        if (ch >= 'A' && ch <= 'Z')
        {
            ch = (char)(ch - 'A' + 'a');
        }

        word[level] = ch;
        level++;
    }

    word[level] = '\0';

    int suggestionCount = 0;

    autocompleteHelper(
        root,
        prefixNode,
        word,
        level,
        suggestions,
        &suggestionCount,
        maxSuggestions
    );

    return suggestionCount;
}

void autocomplete(TrieNode* root, const char* prefix)
{
    Suggestion suggestions[MAX_SUGGESTIONS];
    int suggestionCount = collectSuggestions(
        root,
        prefix,
        suggestions,
        MAX_SUGGESTIONS
    );

    if (suggestionCount == 0)
    {
        printf("No words found for prefix \"%s\".\n", prefix);
        return;
    }

    rankSuggestions(suggestions, suggestionCount);

    printf("\n====================================\n");
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
