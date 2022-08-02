#include "inverted_search.h"

/* Function definition to search a word from the database */
int search(Wlist *head[], char *word)
{
    /* Find the index */
    int index = tolower(word[0]) % 97;

    if(!(index >= 0 && index <= 25))
        index = 26;

    /* Check if the list is empty */
    if(head[index] == NULL)
    {
        return FAILURE;
    }

    /* Traverse through the list */
    while(head[index])
    {
        /* if word is found print relevant informations */
        if(!strcmp(head[index] -> word, word))        
        {
            printf("\nword %s is present in %d file(s):", head[index] -> word, head[index] -> file_count);

            Tlist *temp = head[index] -> Tlink;

            /* Traverse through table nodes to print relevant informations */
            while(temp)
            {
                printf(" %s , %d times", temp -> file_name, temp -> word_count);
                temp = temp -> tlink;        
            }
            printf("\n\n");
            return SUCCESS;
        }
        head[index] = head[index] -> wlink;
    }
    return FAILURE;
}