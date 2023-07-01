// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

bool placeInArray(int *pointerCount, unsigned int hash, node *newPointer, node *tablePointer[N]);
bool deleteNodes(node *ptr);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashValue = hash(word);
    int length = strlen(word);
    char lowercase[length + 1];
    for (int i = 0; i < length; i++)
    {
        lowercase[i] = tolower(word[i]);
    }
    lowercase[length] = '\0';
    // printf("hashValue: %i, word: %s, length: %i \n", hashValue, lowercase, length);
    node *ptr = table[hashValue];
    if (ptr == NULL) // if there are no nodes
    {
        return false;;
    }
    while (ptr->next != NULL)
    {
        if (strcmp(ptr->word, lowercase) == 0)
        {
            // printf("word '%s' found!\n", word);
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    if (strcmp(ptr->word, lowercase) == 0) // check for last node
    {
        // printf("word '%s' found!\n", word);
        return true;
    }
    // printf("word not found \n");
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int i = 0, sum = 0, modSum = 0;
    while (*(word + i) != '\0')
    {
        if (*(word + i) == '\'')
        {
            sum = sum - 1; // set ' as -1 since it can't exist alone
        }
        else
        {
            sum = sum + (toupper(*(word + i)) - 'A');
        }
        // printf("character: %c\n", *(word + i));
        i++;
    }
    modSum = sum % N;
    // printf("sum: %i\n", sum);
    return modSum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // ERROR SEG FAULT create a node for each node pointer and set it to point to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        // printf("Could not open dictionary");
        unload();
        return false;
    }
    char word[LENGTH + 1];
    char c;
    int index = 0;
    int pointerCount = 0;
    while (fread(&c, sizeof(char), 1, dictFile))
    {
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            word[index] = c;
            // printf("character: %c\n", c);
            index++;
        }
        else if (index > 0) // word has been found
        {
            word[index] = '\0';
            // create a new node for the word
            node *new = malloc(sizeof(node));
            strcpy(new->word, word);
            // printf("word: %s\n", new->word);

            // get the hash value
            int hashValue = hash(word); // does this have to be unsigned?
            // printf("hashValue: %i\n", hashValue);
            if (placeInArray(&pointerCount, hashValue, new, table) == false)
            {
                return false;
            }
            index = 0;
        }
    }
    // printf("dictionary loaded\n");
    fclose(dictFile);
    return true;
}

bool placeInArray(int *pointerCount, unsigned int hash, node *new, node *tablePointer[N])
{
    if (*pointerCount > N)
    {
        printf("Pointer count %i  has exceeded %i!\n", *pointerCount, N);
    }
    else if (tablePointer[hash] == NULL)
    {
        table[hash] = new;
        new->next = NULL;
        *pointerCount += 1;
        return true;
        // printf("table[%i] is pointing at new node, pointercount: %i\n", hash, *pointerCount);
    }
    else
    {
        new->next = tablePointer[hash];
        table[hash] = new;
        return true;
        // printf("table[%i] is now pointing at replaced node, pointercount: %i\n", hash, *pointerCount);
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int sum = 0;
    for (int i = 0; i < N; i++)
    {
        node *bucket = table[i];
        if (bucket == NULL)
        {
            continue;
        }
        else
        {
            while (bucket->next != NULL)
            {
                sum += 1;
                bucket = bucket->next;
            }
        }
        sum += 1; // for the last node
    }
    // printf("sum: %i\n", sum);
    return sum; // was return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        if (ptr != NULL)
        {
            if (!deleteNodes(ptr))
            {
                return false;
            }
        }
    }
    // printf("you made it\n");
    return true;
}

bool deleteNodes(node *ptr)
{
    if (ptr->next == NULL)
    {
        free(ptr);
        return true;
    }
    else
    {
        if (deleteNodes(ptr->next) == true)
        {
            free(ptr);
            return true;
        }
        return false;
    }
    return false;
}