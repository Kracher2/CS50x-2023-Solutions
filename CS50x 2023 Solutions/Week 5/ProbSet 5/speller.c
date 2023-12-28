#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents node in hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 7500;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char copy[LENGTH + 1];
    strcpy(copy, word);

    for (int i = 0, len = strlen(copy); i < len; i++)
    {
        copy[i] = toupper(copy[i]);
    }

    node *tmp = table[hash(copy)]->next;

    while (tmp != NULL)
    {
        if (strcmp(tmp->word, copy) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

    return false;
}

// Hashes word to number
unsigned int hash(const char *word)
{
    int num = 0;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        num += toupper(word[i]);
    }

    if (num == 0)
    {
        printf("Could not hash following word: %s\n", word);
        return 3;
    }

    num = (num * len) % N;
    return num;
}

int full_size = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));

        if (table[i] == NULL)
        {
            printf("Not enough memory\n");
            return false;
        }

        table[i]->next = NULL;
    }

    FILE *input = fopen(dictionary, "r");

    if (input == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    char *current = malloc((LENGTH + 1) * sizeof(char));

    if (current == NULL)
    {
        printf("Not enough memory\n");
        return false;
    }

    while (fscanf(input, "%s", current) != EOF)
    {
        node *p = malloc(sizeof(node));

        if (p == NULL)
        {
            printf("Not enough memory\n");
            free(current);
            return false;
        }

        p->next = NULL;

        for (int i = 0, len = strlen(current); i < len; i++)
        {
            current[i] = toupper(current[i]);
        }

        strcpy(p->word, current);
        p->next = table[hash(current)]->next;
        table[hash(current)]->next = p;
        full_size++;
    }

    free(current);
    fclose(input);

    return true;
}

// Returns number of words in dictionary
unsigned int size(void)
{
    return full_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i]->next;

        while (tmp != NULL)
        {
            node *toFree = tmp;
            tmp = tmp->next;
            free(toFree);
        }

        free(table[i]);
        table[i] = NULL;
    }

    return true;
}
