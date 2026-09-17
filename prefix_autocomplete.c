```c
#include <stdio.h>
#include "trie.h"


// =====================================================
// PREFIX SEARCH
// =====================================================

// Find the Trie node corresponding to a prefix
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


// =====================================================
// AUTOCOMPLETE
// =====================================================

// Recursively find all words below the prefix node
void autocompleteHelper(TrieNode* node, char* word, int level)
{
    // If this node represents a complete word
    if (node->isLeaf)
    {
        word[level] = '\0';

        printf("%s\n", word);
    }


    // Check all 26 possible characters
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            word[level] = 'a' + i;

            autocompleteHelper(
                node->children[i],
                word,
                level + 1
            );
        }
    }
}


// Main autocomplete function
void autocomplete(TrieNode* root, const char* prefix)
{
    // Find the node corresponding to the prefix
    TrieNode* prefixNode = findPrefixNode(root, prefix);

    // Prefix does not exist
    if (prefixNode == NULL)
    {
        printf("No words found for prefix \"%s\"\n", prefix);

        return;
    }


    // Array used to construct complete words
    char word[100];

    int level = 0;


    // Copy prefix into word array
    while (prefix[level] != '\0')
    {
        word[level] = prefix[level];

        level++;
    }


    printf("\nSuggestions for \"%s\":\n", prefix);

    // Find all words starting with this prefix
    autocompleteHelper(
        prefixNode,
        word,
        level
    );
}
```
