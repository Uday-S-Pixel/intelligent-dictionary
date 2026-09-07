#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// typedef creates an alias for the struct data type
typedef struct TrieNode {

    // Array of 26 pointers.
    // Each pointer can point to another TrieNode.
    // One position is used for each lowercase letter (a-z).
    struct TrieNode* children[26];

    // Tells us whether a complete word ends at this node.
    bool isLeaf;

} TrieNode;


TrieNode* createNode() {

    // Allocate memory for one TrieNode
    TrieNode* node = malloc(sizeof(TrieNode));

    // Initially, no word ends at this node
    node->isLeaf = false;

    // Initially, this node has no child nodes.
    // Set all 26 child pointers to NULL.
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }

    return node;
}
