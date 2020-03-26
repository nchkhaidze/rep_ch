// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 214639;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char p[LENGTH + 1];
    strcpy(p, word);
    unsigned int hash_code = hash(p);

    if (table[hash_code] == NULL)
    {
        return false;
    }
    else
    {
        node* tmp = table[hash_code];
        while (tmp != NULL)
        {
            if (strcasecmp(tmp->word, p) == 0)
            {
                return true;
            }
            tmp = tmp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Bob Jenkins' one-at-a-time hash function
    char p[LENGTH + 1];
    strcpy(p, word);
    unsigned int len = word_len(p);
    unsigned int h = 0;
    int i;

    for (i = 0; i < len; i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return (h % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    unsigned int hash_code;
    int collisions = 0;
    while (fscanf(dict, "%s", word) != EOF)
    {
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        hash_code = hash(word);
        if (table[hash_code] == NULL)
        {
            table[hash_code] = n;
        }
        else
        {
            n->next = table[hash_code];
            table[hash_code] = n;
            collisions++;
        }
    }
    printf("Collisions: %i\n", collisions);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}

unsigned int word_len(const char* word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    return i;

}
