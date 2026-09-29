#include <stdio.h>
#include <string.h>
#include "trie.h"
void loadDictionary(TrieNode* root, const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dictionary file not found.\n");
        printf("A new dictionary will be created.\n");
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
int wordExists(const char* filename, const char* newWord)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        return 0;
    }
    char word[100];
    while (fscanf(file, "%99s", word) == 1)
    {
        if (strcmp(word, newWord) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
void addWordToDictionary(
    TrieNode* root,
    const char* filename,
    const char* newWord
)
{
    if (wordExists(filename, newWord))
    {
        printf(
            "\"%s\" already exists in the dictionary.\n",
            newWord
        );
        return;
    }
    FILE* file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Error: Could not open dictionary file.\n");
        return;
    }
    fprintf(file, "%s\n", newWord);
    fclose(file);
    Insert(root, newWord);
    printf(
        "\"%s\" has been added to the dictionary.\n",
        newWord
    );
}
