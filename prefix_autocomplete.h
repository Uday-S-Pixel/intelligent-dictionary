#ifndef PREFIX_AUTOCOMPLETE_H
#define PREFIX_AUTOCOMPLETE_H
#include "trie.h"
#define MAX_SUGGESTIONS 1000
#define MAX_WORD_LENGTH 100
typedef struct
{
    char word[MAX_WORD_LENGTH];
    int frequency;
} Suggestion;
TrieNode* findPrefixNode(TrieNode* root, const char* prefix);
void autocompleteHelper(TrieNode* root, TrieNode* node, char* word, int level,
                        Suggestion suggestions[], int* suggestionCount, int maxSuggestions);
int collectSuggestions(TrieNode* root, const char* prefix,
                       Suggestion suggestions[], int maxSuggestions);
void autocomplete(TrieNode* root, const char* prefix);
#endif
