// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Choose number of buckets in hash table
const unsigned int N = 500;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Declare a buff to fread
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            if (strcasecmp(word, tmp->word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //sdbm hash function (as seen in http://www.cse.yorku.ca/~oz/hash.html)
    unsigned long hash = 0;
    int c;
    while ((c = *word++))
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        printf("Dictionary could not be opened.\n");
        return false;
    }

    //Scan dictionary
    char buff[LENGTH + 1];
    while (fscanf(file, "%s", buff) != EOF)
    {
        //Allocate memory to a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }

        //Copy word to node e point to NULL
        strcpy(n->word, buff);

        //Use hash function to search best bucket
        int i = hash(n->word);

        //Link word in hash table
        n->next = table[i];
        table[i] = n;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Declare int to count words
    int count = 0;

    //Return zero if load return false
    if (&load == false)
    {
        return 0;
    }

    //Return after count in a loop on hash table and linked lists
    for (int i = 0; i < N; i++)
    {
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // declare a point
    node *point = NULL;

    //Loop over hash table
    for (int i = 0; i < N; i++)
    {
        point = table[i];
        while (point != NULL)
        {
            node *tmp = point;
            point = point->next;
            free(tmp);
        }
    }
    return true;
}