#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"
#include "dictionary.h"
#include "prefix_autocomplete.h"
#include "dynamic_input.h"
#include "nlp.h"

#define DICTIONARY_FILE "dictionary.txt"
#define NLP_MODEL_FILE "nlp_model.txt"

static void readWord(char* word, int size)
{
    if (fgets(word, size, stdin) == NULL)
    {
        word[0] = '\0';
        return;
    }

    word[strcspn(word, "\n")] = '\0';

    for (int i = 0; word[i] != '\0'; i++)
    {
        word[i] = (char)tolower((unsigned char)word[i]);
    }
}

static void showMenu(void)
{
    printf("\n====================================\n");
    printf(" INTELLIGENT DICTIONARY\n");
    printf("====================================\n");
    printf("1. Exact word search\n");
    printf("2. Auto-complete\n");
    printf("3. Dynamic typing suggestions\n");
    printf("4. NLP context-aware suggestions\n");
    printf("5. Add word\n");
    printf("6. Delete word\n");
    printf("7. Exit\n");
    printf("====================================\n");
    printf("Enter your choice: ");
}

int main(void)
{
    TrieNode* root = createNode();

    if (root == NULL)
    {
        printf("Error: Could not create Trie.\n");
        return 1;
    }

    loadDictionary(root, DICTIONARY_FILE);
    loadNlpModel(NLP_MODEL_FILE);

    while (1)
    {
        int choice;
        char word[100];

        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            while (getchar() != '\n')
            {
            }
            continue;
        }

        getchar();

        switch (choice)
        {
            case 1:
                printf("Enter word: ");
                readWord(word, sizeof(word));

                if (Search(root, word))
                {
                    printf("\"%s\" found. Frequency: %d\n",
                           word, getFrequency(root, word));
                }
                else
                {
                    printf("\"%s\" not found.\n", word);
                }
                break;

            case 2:
                printf("Enter prefix: ");
                readWord(word, sizeof(word));
                autocomplete(root, word);
                break;

            case 3:
                dynamicInput(root);
                break;

            case 4:
            {
                char context[MAX_WORD_LENGTH];
                char prefix[MAX_WORD_LENGTH];
                Suggestion suggestions[MAX_SUGGESTIONS];

                printf("Enter previous/context word: ");
                readWord(context, sizeof(context));

                printf("Enter prefix for the next word: ");
                readWord(prefix, sizeof(prefix));

                int suggestionCount = collectSuggestions(
                    root,
                    prefix,
                    suggestions,
                    MAX_SUGGESTIONS
                );

                if (suggestionCount == 0)
                {
                    printf("No words found for prefix \"%s\".\n", prefix);
                }
                else
                {
                    rankContextSuggestions(
                        suggestions,
                        suggestionCount,
                        context
                    );

                    displayContextSuggestions(
                        suggestions,
                        suggestionCount,
                        context
                    );
                }
                break;
            }

            case 5:
                printf("Enter new word: ");
                readWord(word, sizeof(word));
                addWordToDictionary(root, DICTIONARY_FILE, word);
                break;

            case 6:
                printf("Enter word to delete: ");
                readWord(word, sizeof(word));
                deleteWordFromDictionary(root, DICTIONARY_FILE, word);
                break;

            case 7:
                freeTrie(root);
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
