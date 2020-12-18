#include "trie.h"

TrieNode *make_trienode(char data)
{
    TrieNode *node = (TrieNode *)calloc(1, sizeof(TrieNode));
    for (int i = 0; i < N; i++)
        node->children[i] = NULL;
    node->is_leaf = 0;
    node->data = data;
    return node;
}

void free_trienode(TrieNode *node)
{

    for (int i = 0; i < N; i++)
    {
        if (node->children[i] != NULL)
        {
            free_trienode(node->children[i]);
        }
        else
        {
            continue;
        }
    }
    free(node);
}

TrieNode *insert_trie(TrieNode *root, char *word)
{

    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {

        int idx = (int)word[i] - 'a';
        if (temp->children[idx] == NULL)
        {
            temp->children[idx] = make_trienode(word[i]);
        }
        else
        {
            // Do nothing. The node already exists
        }
        temp = temp->children[idx];
    }
    temp->is_leaf = 1;
    return root;
}

int search_trie(TrieNode *root, char *word)
{
    TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position] == NULL)
            return 0;
        temp = temp->children[position];
    }
    if (temp != NULL && temp->is_leaf == 1)
        return 1;
    return 0;
}

int check_divergence(TrieNode *root, char *word)
{
    TrieNode *temp = root;
    int len = strlen(word);
    if (len == 0)
        return 0;
    int last_index = 0;
    for (int i = 0; i < len; i++)
    {
        int position = word[i] - 'a';
        if (temp->children[position])
        {
            for (int j = 0; j < N; j++)
            {
                if (j != position && temp->children[j])
                {
                    last_index = i + 1;
                    break;
                }
            }
            temp = temp->children[position];
        }
    }
    return last_index;
}

char *find_longest_prefix(TrieNode *root, char *word)
{
    if (!word || word[0] == '\0')
        return NULL;
    int len = strlen(word);
    char *longest_prefix = (char *)calloc(len + 1, sizeof(char));
    for (int i = 0; word[i] != '\0'; i++)
        longest_prefix[i] = word[i];
    longest_prefix[len] = '\0';
    int branch_idx = check_divergence(root, longest_prefix) - 1;
    if (branch_idx >= 0)
    {
        longest_prefix[branch_idx] = '\0';
        longest_prefix = (char *)realloc(longest_prefix, (branch_idx + 1) * sizeof(char));
    }

    return longest_prefix;
}

int is_leaf_node(TrieNode *root, char *word)
{
    TrieNode *temp = root;
    for (int i = 0; word[i]; i++)
    {
        int position = (int)word[i] - 'a';
        if (temp->children[position])
        {
            temp = temp->children[position];
        }
    }
    return temp->is_leaf;
}

TrieNode *delete_trie(TrieNode *root, char *word)
{
    if (!root)
        return NULL;
    if (!word || word[0] == '\0')
        return root;
    if (!is_leaf_node(root, word))
    {
        return root;
    }
    TrieNode *temp = root;
    char *longest_prefix = find_longest_prefix(root, word);
    if (longest_prefix[0] == '\0')
    {
        free(longest_prefix);
        return root;
    }
    int i;
    for (i = 0; longest_prefix[i] != '\0'; i++)
    {
        int position = (int)longest_prefix[i] - 'a';
        if (temp->children[position] != NULL)
        {

            temp = temp->children[position];
        }
        else
        {

            free(longest_prefix);
            return root;
        }
    }

    int len = strlen(word);
    for (; i < len; i++)
    {
        int position = (int)word[i] - 'a';
        if (temp->children[position])
        {
            TrieNode *rm_node = temp->children[position];
            temp->children[position] = NULL;
            free_trienode(rm_node);
        }
    }
    free(longest_prefix);
    return root;
}

void print_trie(TrieNode *root)
{
    if (!root)
        return;
    TrieNode *temp = root;
    printf("%c -> ", temp->data);
    for (int i = 0; i < N; i++)
    {
        print_trie(temp->children[i]);
    }
}

void print_search(TrieNode *root, char *word)
{
    printf("Searching for %s: ", word);
    if (search_trie(root, word) == 0)
        printf("Not Found\n");
    else
        printf("Found!\n");
}
