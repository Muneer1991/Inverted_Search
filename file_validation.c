#include "inverted_search.h"

/* Function definition to validate the files passed through CLA */
void file_validation_n_file_list(Flist **f_head, char *argv[])
{
    /* Variable declaration */
    int empty, repeat, i = 1;

    /* While loop to take each files from the CLA array */
    while(argv[i])
    {
        /* Function call to check if the file is empty */
        if((empty = isFileEmpty(argv[i])) == FILE_EMPTY)
        {
            printf("\nThe file: %s is empty\n", argv[i]);
            printf("Hence not adding this file\n\n");
            i++;
            continue;
        }
        /* Check if the file is available in local directory */
        else if(empty == FILE_NOT_AVAILABLE)
        {
            printf("\nNo file %s available in the file list\n", argv[i]);
            printf("Hence not adding this file\n\n");
            i++;
            continue;
        }
        /* condition for non empty files */
        else
        {
            /* Function call to create the file SLL */
            if((repeat = to_create_list_of_files(f_head, argv[i])) == FAILURE)
            {
                printf("\nFile list creation unsuccessfull for %s\n\n", argv[i]);
            }
            /* Condition to check if the file is repeated */
            else if(repeat == REPEATATION)
            {
                printf("\nDuplicate file name found\n");
                printf("File list creation unsuccessfull for %s\n\n", argv[i]);
            }
            /* Condition if the insertion of file is successfull */
            else
            {
                printf("Successful: Inserting file name: %s into file linked list\n\n",argv[i]);
            }
            
            i++;
        } 
    }
}

/* Function definition to check if the file is empty, available or non empty */
int isFileEmpty(char *filename)
{
    /* File pointer to open the file in read only mode */
    FILE *fptr = fopen(filename, "r");

    /* Condition to check if file is not available */
    if(!fptr)
        return FILE_NOT_AVAILABLE;

    /* point to end of the file */
    fseek(fptr, 0, SEEK_END);

    /* Condition to get the size of the file */
    if(!ftell(fptr))
    {
        fclose(fptr);
        return FILE_EMPTY;
    }
    else 
    {
        fclose(fptr);
        return SUCCESS;
    }       
}

/* Function definition to create the valid file list */
int to_create_list_of_files(Flist **f_head, char *name)
{
    /* Create a node for the file */
    Flist *new = calloc(sizeof(Flist),1);

    /* Validate the memory allocation */
    if(new == NULL)
        return FAILURE;

    /* Update node fields */
    strcpy(new -> file_name,name);
    new -> flink = NULL;

    /* Check if the list is empty */
    /* if yes update the head pointer and return */
    if(!*f_head)
    {
        *f_head = new;
        return SUCCESS;
    }

    /* if list is non empty traverse and update the list */
    Flist *temp = *f_head;
    while(1)
    {
        /* Condition for checking if the file is already present */
        if(strcmp(name, temp -> file_name) == 0)
            return REPEATATION;

        if(temp -> flink == NULL)
        {
            break;
        }
        temp = temp -> flink;
    }
    temp -> flink = new;
    return SUCCESS;
}