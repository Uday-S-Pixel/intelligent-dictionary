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

void Insert(TrieNode* root, const char* word){ 
    // word is a pointer to the first character of the string.
    // const means we do not modify the original string.

    // current keeps track of the node we are currently at.
    TrieNode* current = root; 
 
    while(*word != '\0'){ 

    // Convert the current character into an index from 0 to 25.
    // For example: 'a' - 'a' = 0, 'b' - 'a' = 1, 'c' - 'a' = 2.
    int i = *word - 'a'; 
 
    // If there is no node for this character from the current node,
    // create a new node.
    if(current -> children[i] == NULL){ 
      current -> children[i] = createNode(); 
    } 

    // Move current to the node corresponding to this character.
    current = current -> children[i]; 
 
    // Move word to the next character in the string.
    word++; 
    } 

    // We have reached the end of the word,
    // so mark this node as the end of a complete word.
    current -> isLeaf = true; 
}


bool Search(TrieNode* root, const char* word) {

  // current keeps track of the node we are currently at.
  TrieNode* current = root; 
 
  while(*word != '\0'){ 

  // Convert the current character into an index from 0 to 25.
  // For example: 'a' - 'a' = 0, 'b' - 'a' = 1, 'c' - 'a' = 2.
  int i = *word - 'a'; 
 
  // If there is no node for this character,
  // the word does not exist in the Trie.
  if(current -> children[i] == NULL){ 
    return false; 
  } 

  // Move current to the node corresponding to this character.
  current = current -> children[i]; 

  // Move word to the next character in the string.
  word++; 
    } 

  // If isLeaf is true, a complete word ends at this node.
  // Otherwise, the given word is only a prefix of another word.
  return current -> isLeaf; 
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
