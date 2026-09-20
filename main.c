// only for testing purpose 
#include <stdio.h>

#include "trie.h"
#include "dictionary.h"
#include "prefix_autocomplete.h"

int main()
{
    TrieNode* root = createNode();

    loadDictionary(root, "dictionary.txt");

    autocomplete(root, "app");

    return 0;
}
