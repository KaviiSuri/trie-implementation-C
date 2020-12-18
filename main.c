#include "trie.h"

int main()
{
    // Driver program for the Trie Data Structure Operations
    TrieNode *root = make_trienode('\0');
    int ch;
    do
    {
        printf("\n\n--------Menu-----------\n");
        printf(" 1.Insert_trie\n 2.Search\n 3.print_trie\n 4.Delete\n 5.Exit\n");
        printf("-------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
        {
            root = insert_trie(root, "hello");
            break;
        }

        case 2:
            print_search(root, "hello");
            break;
        case 3:
            print_trie(root);
            break;
        case 4:
            root = delete_trie(root, "hello");
            break;
        case 5:
            free_trienode(root);
            exit(0);
            break;
        default:
            printf("\nInvalid choice:\n");
            break;
        }
    } while (ch != 5);
    return 0;
}