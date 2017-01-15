/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

/**
 * Creates node structure.
 */
typedef struct node
{
    bool is_word;
    struct node* children [27];
} 
node;

// Declares global variable root which is the pointer to the root node.
node* root = NULL;
unsigned int n = 0;
int ascii = 97;
int ap = 39;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* currentNode = root;
    char c = word [0];
    for (int i = 0; word[i] != '\0'; i++)
    {
        c = word[i];
        if (isalpha(c))
        {
            c = tolower(c);
            if (currentNode->children[(int)c - ascii] == NULL)
                return false;
            currentNode = currentNode->children[(int)c - ascii];
        }
        else
        {
            if (currentNode->children[26] == NULL)
                return false;
            currentNode = currentNode->children[26];
        }
    }
    return currentNode->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = (node *)malloc(sizeof (node));
    for (int i = 0; i < 27; i++)
        root->children[i] = NULL;
    node* currentNode = root;
    FILE* list = fopen (dictionary, "r");
    for (int c = fgetc(list); c != EOF; c = fgetc(list))
    {
        if (isalpha(c))
        {
            if (currentNode->children[(int)c - ascii] == NULL)
            {
                currentNode->children[(int)c - ascii] = (node *)malloc (sizeof (node));
                currentNode->children[(int)c - ascii]->is_word = false;
                for (int i = 0; i < 27; i++)
                    currentNode->children[(int)c - ascii]->children[i] = NULL;
            }
            currentNode = currentNode->children[(int)c - ascii];
        }
        else if (c == '\'')
        {
            if (currentNode->children[26] == NULL)
            {
                currentNode->children[26] = (node *)malloc (sizeof (node));
                currentNode->children[26]->is_word = false;
                for (int i = 0; i < 27; i++)
                    currentNode->children[26]->children[i] = NULL;
            }
            currentNode = currentNode->children[26];
        }
        else 
        {
            currentNode->is_word = true;
            n++;
            currentNode = root;
        }
    }
    
    if (ferror(list))
    {
        fclose (list);
        return false;
    }
    else 
    {
        fclose (list);
        return true;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return n;
}

bool freeSpace (node* currentNode)
{
    if (currentNode == NULL)
    {
        free (currentNode);
        return true;
    }
    for (int i = 0; i < 27; i++)
    {
        freeSpace (currentNode->children[i]);
    }
    free(currentNode);
    return true;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return (freeSpace (root));
}