#include "inverted_search.h"

/* extern variable to access the file name */
extern char *f_name;

/* Function definition to insert a node at end of the list */
int insert_at_last(Wlist **head, char *data)
{
    /* create a node */
    Wlist *new = calloc(sizeof(Wlist), 1);

    /* Check for memory allocation */
    if(!new)
        return FAILURE;

    /* Update node members */
    new -> file_count = 1;
    strcpy(new -> word, data);
    new -> Tlink = NULL;
    new -> wlink = NULL;

    /* Function call to create table node */
    if(update_link_table(&new) == FAILURE)
        return FAILURE;

    /* Check if the list is empty and add the node */
    if(*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    /* if the list is not empty traverse through the list and add the node */
    Wlist *temp = *head;

    while(temp -> wlink != NULL)
    {
        temp = temp -> wlink;        
    }

    temp -> wlink = new;
    return SUCCESS;
}

/* Function definition to create table node */
int update_link_table(Wlist **head)
{
    /* Create node */
    Tlist *new = calloc(sizeof(Tlist), 1);

    /* Check for memory allocation */
    if(!new)
        return FAILURE;

    /* Update node members */
    new -> word_count = 1;
    strcpy(new -> file_name, f_name);
    new -> tlink = NULL;

    /* attach the node to corresponding wlist */
    (*head) -> Tlink = new;
    
    return SUCCESS;
    
}