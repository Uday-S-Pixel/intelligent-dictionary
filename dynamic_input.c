#include <stdio.h>
#include <conio.h>

#include "trie.h"
#include "prefix_autocomplete.h"

void dynamicInput(TrieNode* root)
{
    char ch;
    char word[100];
    int length = 0;

    printf("Type a word: ");

    while (1)
    {
        ch = _getch();

        if (ch == ' ')
        {
            break;
        }

        if (ch == '\r')
        {
            break;
        }

        if (length < 99)
        {
            word[length] = ch;
            length++;

            word[length] = '\0';

            printf("\nCurrent word: %s\n", word);
            
            autocomplete(root, word);
        }
    }

    printf("\nYou entered: %s\n", word);
}
