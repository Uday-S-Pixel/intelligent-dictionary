#include <stdio.h>

#include "trie.h"
#include "dictionary.h"
#include "prefix_autocomplete.h"
#include "dynamic_input.h"

int main()
{
    TrieNode* root = createNode();

    loadDictionary(root, "dictionary.txt");

    dynamicInput(root);

    return 0;
}
