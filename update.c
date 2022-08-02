#include "inverted_search.h"

/* extern variable to keep track of database file count */
extern int db_count;

/* Function definition for updating database */
int update_database( Wlist *head[], Flist **f_head)
{
    /* Variable declaration */
    char fname[FILE_NAME_SIZE];
    int empty, repeat;

    /* Read the file name to be updated from the user */
    printf("Enter the file name: ");
    scanf("%s", fname);
    /* Function call to check if the file is empty */
    if((empty = isFileEmpty(fname)) == FILE_EMPTY)
    {
        printf("\nThe file: %s is empty\n", fname);
        printf("Hence not adding this file\n\n");
        return FAILURE;;
    }
    /* Check if the file is available in local directory */
    else if(empty == FILE_NOT_AVAILABLE)
    {
        printf("\nNo files available in the file list\n");
        printf("Hence not adding %s file\n\n", fname);
        return FAILURE;;
    }
    /* condition for non empty files */
    else
    {
        /* Function call to create the file SLL */
        if((repeat = to_create_list_of_files(f_head, fname)) == FAILURE)
        {
            printf("\nFile list creation unsuccessfull for %s\n\n", fname);
            return FAILURE;
        }
        /* Condition to check if the file is repeated */
        else if(repeat == REPEATATION)
        {
            printf("\nDuplicate file name found\n");
            printf("File list creation unsuccessfull for %s\n\n", fname);
            return FAILURE;
        }
        /* Condition if the insertion of file is successfull */
        else
        {
            printf("\nSuccessful: Inserting file name: %s into file linked list\n\n",fname);
        }
    }

    /* if list empty return failure */
    if(f_head == NULL)
    {
        return FAILURE;
    }

    /* Function call to create the database */
    read_datafile(*f_head, head, fname);
    printf("\nUpdated database succesfully\n\n");
    /* extern variable to keep track of database file count */
    db_count++;
    return SUCCESS;
}