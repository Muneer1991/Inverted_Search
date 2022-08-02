#include "inverted_search.h"

/* Function defintion ti display the database */
void display_database( Wlist *head[])
{
    /* status variable to check if the database is empty */
    int status = 0;

    /* for loop to traverse through each indexes */
    for(int i = 0; i < 27; i++)
    {
        /* Check if list is empty */
        if(head[i])
        {
            /* execute at first entry to print information and update empty status */
            if(!status)
            {
                printf("\n%-10s%-9s%-11s%-9s%-12s%-11s\n","[index]","[word]","filecount","file/s", "File_name", "word_count");
                status = 1;
            }
            /* Function call to print the database contents */
            print_word_count(head[i]);
        }
    }
    printf("\n");
    /* Condition to check if database is empty */
    if(status == 0)
        printf("\nThe database is empty\n\n");
}

/* Function defintion to print the database contents */
void print_word_count(Wlist *head)
{
    /* Temporary pointer to traverse through the list */
    Wlist *temp1 = head;
    /* Status variable to know if there is more than 1 table node */
    int status = 0;

    /* Find index value */
    int index = tolower(temp1 -> word[0]) % 97;

    if(!(index >= 0 && index <= 25))
            index = 26;

    /* Traverse through wlist */
    while(temp1)
    {
        /* Print informations */
        printf("%-10d%-9s%-11d%-9s", index, temp1 -> word, temp1 -> file_count,"file/s");

        /* Temporary variable to traverse through the table list */
        Tlist *temp = temp1 -> Tlink;

        /* Traverse through the table node to print informations in the database */
        while(temp)
        {
            if(status == 0)
            {
                printf("%-12s%-11d", temp -> file_name, temp -> word_count);
                
            }   
            else
                printf("\n%45s%7d", temp -> file_name, temp -> word_count);

            status = 1;
            temp = temp -> tlink;
        }
        status = 0;
        printf("\n");
        temp1 = temp1 -> wlink;
    }

    
}