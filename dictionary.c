#include <stdio.h>
#include "trie.h"

void loadDictionary(TrieNode* root, const char* filename)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open dictionary file.\n");
        return;
    }

    char word[100];

    while (fscanf(file, "%99s", word) == 1)
    {
        Insert(root, word);
    }

    fclose(file);

    printf("Dictionary loaded successfully.\n");
}