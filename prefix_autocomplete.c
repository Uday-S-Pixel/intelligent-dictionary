#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct TrieNode {

    struct TrieNode* children[26];

    bool isLeaf;

} TrieNode;


// Create a new Trie node
TrieNode* createNode() {

    TrieNode* node = malloc(sizeof(TrieNode));

    node->isLeaf = false;

    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }

    return node;
}


// Insert a word into the Trie
void Insert(TrieNode* root, const char* word) {

    TrieNode* current = root;

    while (*word != '\0') {

        int i = *word - 'a';

        if (current->children[i] == NULL) {
            current->children[i] = createNode();
        }

        current = current->children[i];

        word++;
    }

    current->isLeaf = true;
}


// Search for an exact word
bool Search(TrieNode* root, const char* word) {

    TrieNode* current = root;

    while (*word != '\0') {

        int i = *word - 'a';

        if (current->children[i] == NULL) {
            return false;
        }

        current = current->children[i];

        word++;
    }

    return current->isLeaf;
}


// =====================================================
// YOUR MODULE: PREFIX SEARCH
// =====================================================

// Find the Trie node corresponding to a prefix
TrieNode* findPrefixNode(TrieNode* root, const char* prefix) {

    TrieNode* current = root;

    while (*prefix != '\0') {

        int i = *prefix - 'a';

        if (current->children[i] == NULL) {
            return NULL;
        }

        current = current->children[i];

        prefix++;
    }

    return current;
}


// =====================================================
// YOUR MODULE: AUTOCOMPLETE
// =====================================================

// Recursively find all words below the prefix node
void autocompleteHelper(TrieNode* node, char* word, int level) {

    // If this node represents a complete word
    if (node->isLeaf) {

        word[level] = '\0';

        printf("%s\n", word);
    }


    // Check all 26 possible characters
    for (int i = 0; i < 26; i++) {

        if (node->children[i] != NULL) {

            word[level] = 'a' + i;

            autocompleteHelper(
                node->children[i],
                word,
                level + 1
            );
        }
    }
}


// Main autocomplete function
void autocomplete(TrieNode* root, const char* prefix) {

    // Find the node corresponding to the prefix
    TrieNode* prefixNode = findPrefixNode(root, prefix);

    // Prefix does not exist
    if (prefixNode == NULL) {

        printf("No words found for prefix \"%s\"\n", prefix);

        return;
    }


    // Array used to construct complete words
    char word[100];

    int level = 0;


    // Copy prefix into word array
    while (prefix[level] != '\0') {

        word[level] = prefix[level];

        level++;
    }


    printf("\nSuggestions for \"%s\":\n", prefix);

    // Find all words starting with this prefix
    autocompleteHelper(
        prefixNode,
        word,
        level
    );
}


// =====================================================
// MAIN
// =====================================================

int main() {

    TrieNode* root = createNode();


    // Words inserted by Person 1
    Insert(root, "cat");
    Insert(root, "car");
    Insert(root, "cafe");

    // Additional words for testing autocomplete
    Insert(root, "care");
    Insert(root, "card");
    Insert(root, "cart");
    Insert(root, "dog");


    // Exact search
    printf("cat: %d\n", Search(root, "cat"));
    printf("car: %d\n", Search(root, "car"));
    printf("cafe: %d\n", Search(root, "cafe"));


    // Prefix search + autocomplete
    autocomplete(root, "ca");

    autocomplete(root, "car");

    autocomplete(root, "do");

    autocomplete(root, "xyz");


    return 0;
}
