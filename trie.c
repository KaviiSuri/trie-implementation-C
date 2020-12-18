#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "utils.c"

#define ALPHABET_SIZE 26
#define ALPHABET_ROOT 'a'

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    char data;
    bool word_end;
} TrieNode;

// Create A New Node
TrieNode *createTrieNode()
{
    TrieNode *node;
    node = malloc(sizeof(TrieNode));
    node->word_end = false;
    int i = 0;
    while (i < ALPHABET_SIZE)
    {
        node->children[i] = NULL;
        i++;
    }
    return node;
}
// Insert word in a given trie
// Time Complexity O(L) where L is Lenght of single word
void insert(TrieNode *root, char *word)
{
    char data = *word;
    if ((strlen(word - 1) != 0))
    {
        if (root->children[data - ALPHABET_ROOT] == NULL)
        {
            TrieNode *node = NULL;
            node = createTrieNode();
            node->data = data;
            root->children[data - ALPHABET_ROOT] = node;
        }
        word++;
        insert(root->children[data - ALPHABET_ROOT], word);
    }
    else
    {
        root->word_end = true;
    }
    return;
}

// Search a word in the Trie
// Time Complexity O(L) where L is Lenght of single word
TrieNode *search(TrieNode *root, char *word)
{
    TrieNode *temp;
    while (*word != '\0')
    {
        char data = *word;
        if (root->children[data - ALPHABET_ROOT] != NULL)
        {
            temp = root->children[data - ALPHABET_ROOT];
            word++;
            root = temp;
        }
        else
        {
            printf("No Possible words!!\n");
            return NULL;
        }
    }
}

void printPathsRecur(TrieNode *node, char prefix[], int len_till_now)
{
    if (node == NULL)
        return;
    prefix[len_till_now] = node->data;
    len_till_now++;
    if (node->word_end)
    {
        printArray(prefix, len_till_now);
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        printPathsRecur(node->children[i], prefix, len_till_now);
    }
}