// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <cs50.h>

#include "dictionary.h"

unsigned int count_size = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    //Set Node Cursor to first item in linked list
    node *cursor = table[index];

    //Traverse through Linked List until NULL
    while (cursor != NULL){
        //If cursor and word are the same, return true
        if (strcasecmp(cursor -> word, word) == 0){
            return true;
        }
        //Traverse to next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Source: djb2 by dan Bernstring
    unsigned long hash = 5381;
    int c;

    while ((c = tolower(*word++))){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    //Open Dictionary File
    FILE *input = fopen(dictionary, "r");

    if (input == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    //Read Strings from one file at a time
    char buffer[LENGTH + 1];
    while (fscanf(input, "%s", buffer) != EOF){
        fread(buffer, sizeof(buffer), 1, input);
        //Create a new node for each word
        node * new_node = malloc(sizeof(node));
        if (new_node != NULL){
            //Copy buffer string from new node into word node
            strcpy(new_node->word, buffer);
        }
        //Hash word into hash table
        int index = hash(buffer);

        if (table[index] == NULL){
            table[index] = new_node;
        }else{
            //Insert Node into Hash table
            new_node->next = table[index];
            table[index] = new_node;
        }
        count_size++;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = NULL;
    node *tmp = cursor;

    for (int i = 0; i < N; i++){
        cursor = table[i];
        while (cursor!= NULL){
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
