#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 26
typedef struct TrieNode TrieNode;

struct TrieNode
{

    char data;
    TrieNode *children[N];
    int is_leaf;
};

TrieNode *make_trienode(char data);
void free_trienode(TrieNode *node);
TrieNode *insert_trie(TrieNode *root, char *word);
int search_trie(TrieNode *root, char *word);
TrieNode *delete_trie(TrieNode *root, char *word);
void print_trie(TrieNode *root);
void print_search(TrieNode *root, char *word);