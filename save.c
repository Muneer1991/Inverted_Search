#include "inverted_search.h"

/* Function defintion to save the database into a file entered by the user */
void save_database( Wlist *head[])
{
    /* variable to store file name */
    char file_name[FILE_NAME_SIZE];
    
    /* Read file name from user */
    printf("Enter the filename: ");
    scanf("%s", file_name) ;

    /* Open the file if present or create a new file in write mode */
    FILE *fptr = fopen(file_name, "w");

    /* Traverse through the index */
    for (int i = 0 ; i < 27; i++)
    {
        /* condition to check if list is not empty for any index */
        if(head[i] != NULL)
        {
            fprintf(fptr,"#%d\n",i);
            /* Function call to write data into the file */
            write_databasefile(head[i],fptr);
        }   
        /* Close the pointer after each writing */
        fclose(fptr);
        /* Then open the file in append mode for next write operation */
        fptr = fopen(file_name, "a");
    }
    /* Close the file pointer at end */
    fclose(fptr);
    printf ("\nDatabase is saved in %s\n\n", file_name);
}

/* Function defintion to write database into a file */
void write_databasefile(Wlist *head, FILE* databasefile)
{
    /* Temporary pointer to traverse through the nodes */
    Wlist *temp1 = head;
    /* Status to find if there are more than 1 table node */
    int status = 0;

    /* Traverse through wlist */
    while(temp1)
    {
        /* save informations */
        fprintf(databasefile,"%s;%d;", temp1 -> word, temp1 -> file_count);

        /* Temporary variable to traverse through the table list */
        Tlist *temp = temp1 -> Tlink;

        /* Traverse through the table node to save informations in the file */
        while(temp)
        {
            if(status == 0)
            {
                fprintf(databasefile,"%s;%d;", temp -> file_name, temp -> word_count);
                
            }   
            else
                fprintf(databasefile,"%s;%d;", temp -> file_name, temp -> word_count);

            status = 1;
            temp = temp -> tlink;
        }
        status = 0;
        fprintf(databasefile,"#\n");
        temp1 = temp1 -> wlink;
    }

    
}