#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "trie.h"

void loadDictionary(TrieNode* root, const char* filename);
int wordExists(const char* filename, const char* newWord);
void addWordToDictionary(TrieNode* root, const char* filename, const char* newWord);
int deleteWordFromDictionary(TrieNode* root, const char* filename, const char* word);
int saveDictionary(TrieNode* root, const char* filename);

#endif
