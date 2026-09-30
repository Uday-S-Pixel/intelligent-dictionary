#include <stdio.h>
#include <string.h>
#include "dictionary.h"

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
    if (newWord == NULL || *newWord == '\0')
    {
        return;
    }

    if (wordExists(filename, newWord))
    {
        printf("\"%s\" already exists in the dictionary.\n", newWord);
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
    printf("\"%s\" has been added to the dictionary.\n", newWord);
}

int deleteWordFromDictionary(
    TrieNode* root,
    const char* filename,
    const char* word
)
{
    if (!containsWord(root, word))
    {
        printf("\"%s\" was not found in the dictionary.\n", word);
        return 0;
    }

    if (!deleteWord(root, word))
    {
        return 0;
    }

    if (!saveDictionary(root, filename))
    {
        printf("Word removed from memory, but the file could not be updated.\n");
        return 0;
    }

    printf("\"%s\" has been deleted from the dictionary.\n", word);
    return 1;
}

static void saveWords(TrieNode* node, char* word, int level, FILE* file)
{
    if (node == NULL)
    {
        return;
    }

    if (node->isLeaf)
    {
        word[level] = '\0';
        fprintf(file, "%s\n", word);
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            word[level] = (char)('a' + i);
            saveWords(node->children[i], word, level + 1, file);
        }
    }
}

int saveDictionary(TrieNode* root, const char* filename)
{
    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        return 0;
    }

    char word[100];
    saveWords(root, word, 0, file);

    fclose(file);
    return 1;
}
