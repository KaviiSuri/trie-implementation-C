#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 26

struct Trie
{
    int isLeaf;
    struct Trie *character[CHAR_SIZE];
};

// Function that returns a new Trie node
struct Trie *getNewTrieNode()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++)
        node->character[i] = NULL;

    return node;
}

// function to insert a string in Trie
void insert(struct Trie *head, char *str)
{
    struct Trie *curr = head;
    while (*str)
    {
        if (curr->character[*str - 'a'] == NULL)
            curr->character[*str - 'a'] = getNewTrieNode();
        curr = curr->character[*str - 'a'];
        str++;
    }
    curr->isLeaf = 1;
}

// function to search a string in Trie. It returns 1
// if the string is found in the Trie, else it returns 0
int search(struct Trie *head, char *str)
{
    if (head == NULL)
        return 0;

    struct Trie *curr = head;
    while (*str)
    {
        curr = curr->character[*str - 'a'];

        if (curr == NULL)
            return 0;

        str++;
    }

    return curr->isLeaf;
}

// returns 1 if given node has any children
int haveChildren(struct Trie *curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
        if (curr->character[i])
            return 1;

    return 0;
}

// function to delete a string in Trie
int deletion(struct Trie **curr, char *str)
{
    if (*curr == NULL)
        return 0;

    if (*str)
    {
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!haveChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    if (*str == '\0' && (*curr)->isLeaf)
    {
        if (!haveChildren(*curr))
        {
            free(*curr);
            (*curr) = NULL;
            return 1;
        }

        else
        {
            (*curr)->isLeaf = 0;
            return 0;
        }
    }

    return 0;
}

int main()
{
    struct Trie *head = getNewTrieNode();

    insert(head, "hello");
    printf("%d ", search(head, "hello")); // print 1

    insert(head, "helloworld");
    printf("%d ", search(head, "helloworld")); // print 1

    printf("%d ", search(head, "helll")); // print 0 (Not present)

    insert(head, "hell");
    printf("%d ", search(head, "hell")); // print 1

    insert(head, "h");
    printf("%d \n", search(head, "h")); // print 1 + newline

    deletion(&head, "hello");
    printf("%d ", search(head, "hello"));      // print 0 (hello deleted)
    printf("%d ", search(head, "helloworld")); // print 1
    printf("%d \n", search(head, "hell"));     // print 1 + newline

    deletion(&head, "h");
    printf("%d ", search(head, "h"));           // print 0 (h deleted)
    printf("%d ", search(head, "hell"));        // print 1
    printf("%d\n", search(head, "helloworld")); // print 1 + newline

    deletion(&head, "helloworld");
    printf("%d ", search(head, "helloworld")); // print 0
    printf("%d ", search(head, "hell"));       // print 1

    deletion(&head, "hell");
    printf("%d\n", search(head, "hell")); // print 0 + newline

    if (head == NULL)
        printf("Trie empty!!\n"); // Trie is empty now

    printf("%d ", search(head, "hell")); // print 0

    return 0;
}
