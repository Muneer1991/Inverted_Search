#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Macro definitions */
#define SUCCESS 0
#define FAILURE -1
#define FILE_EMPTY -2
#define FILE_NOT_AVAILABLE -3
#define REPEATATION -4
#define FILE_NAME_SIZE 10
#define WORD_SIZE 20

/* structure for file list */
typedef struct file_node
{
    char file_name[FILE_NAME_SIZE];
    struct file_node *flink;
}Flist;

/* structure for link table */
typedef struct link_table_node
{
    unsigned int word_count;
    char file_name[FILE_NAME_SIZE];
    struct link_table_node *tlink;
}Tlist;

/* structure for word list */
typedef struct word_node
{
    unsigned int file_count;
    char word[WORD_SIZE];
    Tlist *Tlink;
    struct word_node *wlink;
}Wlist;



/* Function prototype to check if the file is empty, available or non empty */
int isFileEmpty(char *filename);
/* Function prototype to validate the files passed through CLA */
void file_validation_n_file_list(Flist **f_head, char *argv[]);
/* Function prototype to create the valid file list */
int to_create_list_of_files(Flist **f_head, char *name);
/* Function prototype ti display the database */
void display_database( Wlist *head[]);
/* Function prototype to print the database contents */
void print_word_count(Wlist *head);
/* Function prototype to create database */
void create_database(Flist *f_head, Wlist *head[]);
/* Function prototype to read words from the file and create a corresponding database */
void read_datafile(Flist *file, Wlist *head[], char *filename);
/* Function prototype to update the word count/file count */
int update_word_count(Wlist **head, char *file_name);
/* Function prototype to create table node */
int update_link_table(Wlist **head);
/* Function prototype to insert a node at end of the list */
int insert_at_last(Wlist **head, char *data);
/* Function prototype to search a word from the database */
int search(Wlist *head[], char *word);
/* Function prototype to save the database into a file entered by the user */
void save_database( Wlist *head[]);
/* Function prototype to write database into a file */
void write_databasefile(Wlist *head, FILE *databasefile);
/* Function prototype for updating database */
int update_database( Wlist *head[], Flist **f_head);

#endif