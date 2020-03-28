// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

// Represents a trie
node *root;

// count number of words in dict
int num_words_in_dict = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = calloc(1, sizeof(node));
    if (root == NULL)
    {
        return false;
    }

    //int copy of root
    node *trav = root;

    for (int i = 0; i < N; i++)
    {
        trav->children[i] = NULL;
    }

    trav->is_word = false;

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // ascii word number
    int ascii_word = 0;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        int word_len = strlen(word);

        for (int i = 0; i < word_len + 1; i++)
        {
            if (isalpha(word[i]))
            {
                ascii_word = tolower((unsigned char) word[i]) - 'a';
            }
            else
            {
                ascii_word = 26;
            }

            if (trav->children[ascii_word] == NULL)
            {
                node *new_node = calloc(1, sizeof(node));

                trav->children[ascii_word] = new_node;

                trav = trav->children[ascii_word];

                if (i == word_len)
                {
                    trav->is_word = true;
                    trav = root;
                    num_words_in_dict++;
                }
            }

            else
            {
                trav = trav->children[ascii_word];
            }
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return num_words_in_dict;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //int copy of root
    node *trav = root;

    char word_lower[LENGTH + 1];

    strcpy(word_lower, word);

    int word_len = strlen(word_lower);

    int ascii_word = 0;

    for (int i = 0; i < word_len + 1; i++)
    {
        if (isalpha(word[i]))
        {
            ascii_word = tolower((unsigned char) word[i]) - 'a';
        }
        else
        {
            ascii_word = 26;
        }

        if (trav->children[ascii_word] == NULL)
        {
            return false;
        }

        else
        {
            trav = trav->children[ascii_word];
        }

        if (i == word_len)
        {
            if (trav->is_word == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

// recursion function
bool unload_recursion(node *n);

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //unload from bottom to top
    //travel to lowest node possible
    //free all pointers in children
    //backtrack upwards, freeing all elements in each children array until you hit root node

    node *trav = root;

    if (trav == NULL)
    {
        return false;
    }

    else
    {
        return unload_recursion(trav);
    }
}

bool unload_recursion(node *n)
{
    for (int i = 0; i < N; i++)
    {
        if (n->children[i] != NULL)
        {
            unload_recursion(n->children[i]);
        }

        if (i == 26)
        {
            free(n);
            break;
        }
    }

    return true;
}