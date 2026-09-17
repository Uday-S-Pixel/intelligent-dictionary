#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct TrieNode {
    struct TrieNode* children[26];
    bool isLeaf;
} TrieNode;

TrieNode* createNode(void);

void Insert(TrieNode* root, const char* word);

bool Search(TrieNode* root, const char* word);

#endif
