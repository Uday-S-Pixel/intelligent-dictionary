#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "trie.h"
#include "prefix_autocomplete.h"

void dynamicInput(TrieNode* root)
{
    char ch;
    char word[100] = "";
    int length = 0;

    printf("Type a word (Enter/Space to finish, Backspace to edit, Esc to cancel): ");

    while (1)
    {
        ch = _getch();

        if (ch == 27)
        {
            printf("\nInput cancelled.\n");
            return;
        }

        if (ch == '\r' || ch == ' ')
        {
            break;
        }

        if (ch == '\b')
        {
            if (length > 0)
            {
                length--;
                word[length] = '\0';
                printf("\rCurrent word: %-99s", word);

                if (length > 0)
                {
                    autocomplete(root, word);
                }
                else
                {
                    printf("\n");
                }
            }

            continue;
        }

        if (isalpha((unsigned char)ch) && length < 99)
        {
            ch = (char)tolower((unsigned char)ch);
            word[length] = ch;
            length++;
            word[length] = '\0';

            printf("\rCurrent word: %-99s\n", word);
            autocomplete(root, word);
        }
    }

    printf("\nYou entered: %s\n", word);
}
