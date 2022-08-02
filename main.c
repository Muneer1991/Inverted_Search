/**************Documentation**************
Name          : Muneer Mohammad Ali
Date          : 24/06/2022
Description   : Inverted Search
Sample Input  : ./out.exe f1.txt f2.txt 
                Choose options to create database
Sample Output : Choose option to display database or save database to a file
******************************************/
#include "inverted_search.h"

int main(int argc, char *argv[]) 
{
    /* Variable declaration */
    char word[WORD_SIZE];
    int choice;

    /* Head pointers initialization */
    Flist *f_head = NULL;
    Wlist *head[27] = {NULL};

    /* check if CLA is passed */
    if(argc == 1)
    {
        printf("\nEnter valid number of arguments\n");
        printf("./out.exe f1.txt f2.txt ...\n\n");    
        return 1;
    }

    /* Function call to validate the files passed through CLA */
    file_validation_n_file_list(&f_head, argv);

    /* Check if list is empty, then no files list is created, then return */
    if(f_head == NULL)
    {
        printf("\nNo files are added into the list\n");
        printf("Hence process is terminating\n\n");
        return 2;
    }

    /* loop for doing operations on the database */
    while(1)
    {
        /* Print options */
        printf("1.Create Database\n2.Display Database\n3.Search\n4.Update Database\n5.Save Database\n6.Exit\nEnter your choice : ");    

        /* Read choice from user */
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                /* Function call to create the database */
                create_database(f_head, head);
                break;
            case 2:
                /* Function call to display database contents */
                display_database(head);
                break;
            case 3:
                /* Search a word from database */
                printf("Enter the word to be searched: ");
                scanf("%s", word);
                if(search(head, word) == FAILURE)
                    printf("\nSearch word is not available\n\n");
                break;
            case 4:
                /* Function call to update the database with new file */
                if(update_database(head, &f_head) == FAILURE)
                {
                    printf("\nNo files are added into the list\n");
                    printf("Hence process is terminating\n\n");
                }
                break;
            case 5:
                /* Function call to save the database into a file entered by the user */
                save_database(head);
                break;
            case 6:
                /* EXIT */
                return 0;
            default:
                /* Incorrect options */
                printf("\nEnter proper option\n\n");
        }
    }
  
    return 0;
}