#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "trie.h"

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

int main(){
  TrieNode* root = createNode();
  Insert(root,"cat");
  Insert(root,"car");
  Insert(root,"cafe");
 
  printf("cat: %d\n", Search(root, "cat"));
  printf("car: %d\n", Search(root, "car"));
  printf("cafe: %d\n", Search(root, "cafe"));

  return 0;
}
