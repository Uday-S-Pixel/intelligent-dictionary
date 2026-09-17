#ifndef PREFIX_AUTOCOMPLETE_H
#define PREFIX_AUTOCOMPLETE_H

#include "trie.h"

TrieNode* findPrefixNode(TrieNode* root, const char* prefix);

void autocompleteHelper(TrieNode* node, char* word, int level);

void autocomplete(TrieNode* root, const char* prefix);

#endif
