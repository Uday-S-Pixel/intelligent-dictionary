#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "trie.h"

static int getIndex(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = (char)(ch - 'A' + 'a');
    }

    if (ch < 'a' || ch > 'z')
    {
        return -1;
    }

    return ch - 'a';
}

TrieNode* createNode(void)
{
    TrieNode* node = malloc(sizeof(TrieNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->isLeaf = false;
    node->frequency = 0;

    for (int i = 0; i < 26; i++)
    {
        node->children[i] = NULL;
    }

    return node;
}

void Insert(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL || *word == '\0')
    {
        return;
    }

    TrieNode* current = root;

    while (*word != '\0')
    {
        int i = getIndex(*word);

        if (i == -1)
        {
            return;
        }

        if (current->children[i] == NULL)
        {
            current->children[i] = createNode();

            if (current->children[i] == NULL)
            {
                return;
            }
        }

        current = current->children[i];
        word++;
    }

    current->isLeaf = true;
}

bool Search(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL || *word == '\0')
    {
        return false;
    }

    TrieNode* current = root;

    while (*word != '\0')
    {
        int i = getIndex(*word);

        if (i == -1 || current->children[i] == NULL)
        {
            return false;
        }

        current = current->children[i];
        word++;
    }

    if (current->isLeaf)
    {
        current->frequency++;
        return true;
    }

    return false;
}

bool containsWord(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL || *word == '\0')
    {
        return false;
    }

    TrieNode* current = root;

    while (*word != '\0')
    {
        int i = getIndex(*word);

        if (i == -1 || current->children[i] == NULL)
        {
            return false;
        }

        current = current->children[i];
        word++;
    }

    return current->isLeaf;
}

int getFrequency(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL || *word == '\0')
    {
        return 0;
    }

    TrieNode* current = root;

    while (*word != '\0')
    {
        int i = getIndex(*word);

        if (i == -1 || current->children[i] == NULL)
        {
            return 0;
        }

        current = current->children[i];
        word++;
    }

    if (current->isLeaf)
    {
        return current->frequency;
    }

    return 0;
}

static bool deleteHelper(TrieNode* node, const char* word, int level)
{
    if (word[level] == '\0')
    {
        if (!node->isLeaf)
        {
            return false;
        }

        node->isLeaf = false;
        node->frequency = 0;

        for (int i = 0; i < 26; i++)
        {
            if (node->children[i] != NULL)
            {
                return false;
            }
        }

        return true;
    }

    int i = getIndex(word[level]);

    if (i == -1 || node->children[i] == NULL)
    {
        return false;
    }

    TrieNode* child = node->children[i];
    bool deleteChild = deleteHelper(child, word, level + 1);

    if (deleteChild)
    {
        free(child);
        node->children[i] = NULL;
    }

    if (node->isLeaf)
    {
        return false;
    }

    for (int j = 0; j < 26; j++)
    {
        if (node->children[j] != NULL)
        {
            return false;
        }
    }

    return true;
}

bool deleteWord(TrieNode* root, const char* word)
{
    if (root == NULL || word == NULL || *word == '\0')
    {
        return false;
    }

    if (!containsWord(root, word))
    {
        return false;
    }

    deleteHelper(root, word, 0);
    return true;
}

void freeTrie(TrieNode* root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < 26; i++)
    {
        freeTrie(root->children[i]);
    }

    free(root);
}
