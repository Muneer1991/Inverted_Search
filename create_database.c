#include "inverted_search.h"

/* extern variable to store the filename */
char *f_name;

/* extern variable to keep track of database file count */
int db_count = 0;

/* Function definition to create database */
void create_database(Flist *f_head, Wlist *head[])
{
    /* Variable to store the file count */
    int f_count = 0;

    /* Temporary pointer to traverse through the file list */
    Flist *temp = f_head;

    /* Get the file count from file list */
    while(temp)
    {
        f_count++;
        temp = temp -> flink;
        
    }
    /* if total file count is equal to the database file count then it means the database is already updated */
    if(f_count == db_count)
    {
        printf("\nDatabase is already updated\n\n");
        return;
    }
    
    /* Loop until the file list is traverse till end */
    while(f_head)
    {
        /* Function call to read words from file and create a corresponding database */
        read_datafile(f_head, head, f_head -> file_name);      
        f_head = f_head -> flink;
    }
    printf("\nDatabase created succesfully\n\n");

    /* Store the file count in database file count */
    db_count = f_count;
    return;
}

/* Function definition to read words from the file and create a corresponding database */
void read_datafile(Flist *file, Wlist *head[], char *filename)
{
    
    /* variable to update the status of a duplicate word to be updated in database */
    int file_status = 1;

    /* store the filename in a variable */
    f_name = filename;

    /* File pointer to open the file in read only mode */
    FILE *fptr = fopen(filename, "r");

    /* Buffer to store the words from the file */
    char word[WORD_SIZE];

    /* Read words from file and store one by one in buffer and store in database */
    while(fscanf(fptr, "%s", word) != EOF)
    {
        /* 0 to 25 index for alphabets and 26 for non alphabets */
        int index = tolower(word[0]) % 97;

        if(!(index >= 0 && index <= 25))
            index = 26;

        /* Traverse through the list for particular index */
        if(head[index] != NULL)
        {
            /* Temporary pointer to traverse through the list */
            Wlist *temp = head[index];

            /* Check for same words by traversing */
            while(temp)
            {
                /* if same words found update the list accordingly for word count/file count */
                if(!strcmp(temp -> word, word))
                {
                    /* Function call to update the list counts */
                    if(update_word_count(&temp, filename) == FAILURE)
                    {
                        printf("\nWord could not be updated in the database\n\n");
                        fclose(fptr);
                        return;
                    }
                    /* status for same word found in database */
                    file_status = 0;
                }
                /* update temp to traverse */
                temp = temp -> wlink;         
            }
        }
        /* If word not present insert the nodes at last */
        if(file_status == 1)
        {
            /* Function call to insert nodes at last */
            if(insert_at_last(&head[index], word) == FAILURE)
            {
                printf("\nWords could not be added to the database\n\n");
                fclose(fptr);
                return;
            }
        }
        /* Change status at loop end */
        file_status = 1;
    }

    /* Close the file pointer after the file operations */
    fclose(fptr);
}

/* Function definition to update the word count/file count */
int update_word_count(Wlist **head, char *file_name)
{
    /* temporary pointer to traverse through the list */
    Tlist *temp = (*head) -> Tlink;

    /* loop to check if the file name is matching then izcrement the word count and return */
    while(1)
    {
        if(!strcmp(temp -> file_name, file_name))
        {
            (temp -> word_count)++;
            return SUCCESS;
        }
        if(temp -> tlink == NULL)
        {
            break;
        }
        temp = temp -> tlink;
    }

    /* if the filename is not matching then increment the file count and add a table node */
    Tlist *new = calloc(sizeof(Tlist), 1);

    if(!new)
        return FAILURE;
    
    new -> word_count = 1;
    strcpy(new -> file_name, file_name);
    new -> tlink = NULL;

    ((*head) -> file_count)++;
    temp -> tlink = new;
    
    return SUCCESS;
}