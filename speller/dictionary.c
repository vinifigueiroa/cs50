// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// TODO: Choose number of buckets in hash table
const unsigned int N = 1430;

// Hash table
node *table[N];

// size_counter
int size_counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];
    return navigator(word, cursor);

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int result = 1;
    for (int i = 0; i < (int) strlen(word); i++)
    {
        result *= tolower(word[i]);
    }

    return result % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *to_load = fopen(dictionary, "r");
    if (to_load == NULL)
    {
        printf("Failed to load dictionary file");
        return false;
    }

    char new_word[LENGTH];
    int bucket;

    while (fscanf(to_load, "%s", new_word) != EOF)
    {

        bucket = hash(new_word);
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Failed to add words to memory");
            return false;
        }

        size_counter += 1;
        strcpy(new_node->word, new_word);

        if (table[bucket] == NULL)
        {
            table[bucket] = new_node;
            new_node->next = NULL;
        }
        else
        {
            node *previous_pointer = table[bucket];
            table[bucket] = new_node;
            new_node->next = previous_pointer;
        }
    }
    fclose(to_load);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freeloader(table[i]);
        }
    }

    return true;
}

// Goes through the linked list in the specific bucket. returns true if word is found
bool navigator(const char *word, node *cursor)
{
    if (cursor == NULL)
    {
        return false;
    }
    else if (strcasecmp(word, cursor->word) == 0)
    {
        return true;
    }
    else
    {
        cursor = cursor->next;
        return navigator(word, cursor);
    }
}

bool freeloader(node *node)
{
    if (node->next == NULL)
    {
        free(node);
        return true;
    }
    else
    {
        return freeloader(node->next);
    }
}