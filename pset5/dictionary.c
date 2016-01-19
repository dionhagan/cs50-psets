/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

node root = {false,{NULL}};

int words = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* cur = &root;
    int i = 0;
    while (word[i] != '\0')
    {
        // get children index value for word[i]
        int val = get_val(word[i]);
        
        // if word[i] node not in children return false
        if (cur->children[val] == NULL)
        {
            return false;
        }
        // point cur to next letter
        cur = cur->children[val];
        i++;
    }
    // check if last letter has 'is_word == true'
    // if false, return false
    if (cur->is_word)
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // set current node
    // root = malloc(sizeof(node));
    node* cur = &root;
    
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("File not found");
        fclose(fp);
        return false;
    }
    
    char c = '\0';
    
    while ((c = fgetc(fp)) != EOF)
    {
        // allow only alphabetical characters and apostrophes
        if (c != '\n')
        {
            int val = get_val(c);
            
            if (cur->children[val] == NULL)
            {
                // create a new node letter and have root point to new letter
                node* letter = malloc(sizeof(node));
                if (letter == NULL)
                {
                    printf("Malloc failed");
                    return false;
                }
                // default node
                *letter = (node){false,{NULL}};
                
                // place node in current node's children array
                cur->children[val] = letter;
                
            }
            // point cur to next letter node
            cur = cur->children[val];
        }
        // we must have found a whole word
        else
        {
            // indicate this node ends a full word
            cur->is_word = true;
            cur = &root;
            // update counter
            words++;
            // printf("%i\n", words);
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/* helper function for unload */
void unloader(node* cur)
{
    if (cur == NULL)
    {
        return;
    }
    
    for (int i = 0;i < 27; i++)
    {
        if (cur->children[i] != NULL)
        {
            unloader(cur->children[i]);
        }
    }
    free(cur);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0;i < 27; i++)
    {
        if (root.children[i] != NULL)
        {
            unloader(root.children[i]);
        }
    }
    return true;
}

int get_val(char c)
{
    int ascii_val = c;
    
    // handle apostrophes - ASCII value of 39
    if (c == 39)
    {
        ascii_val -= 12;
    }
    else
    {
        // index of children array
        ascii_val = tolower(c) - 'a';
    }
    return ascii_val;
}

