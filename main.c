/*
 * C Program that manages a directory of notes.
 * Allows for opening and reading specific notes.
 */
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "linkedList.h"
#include <stdlib.h>

#define EXIT_VAL '4'
#define BUFFER_SIZE 255
#define FILE_EXTENSION ".txt"

char promp_user();
void execute_action(char choice);
struct Node *create_list();
void print_file();
void create_Note();
char *make_filename();


int main(void)
{
    int choice;
    printf(" -----   Welcomes to the Note Record System   -----\n\n");
    printf("What would you like to do today? \n     1: Create a new Note\n     2: View an existing Note\n     3: Delete an old Note\n     4: Exit\n\n");
    choice = promp_user();
    while (choice != EXIT_VAL){
        execute_action(choice);
        choice = promp_user();
    }
    return(0);
}

char promp_user(){
    char choice;
    printf("Enter the number of your selection: ");
    scanf(" %c", &choice);
    return choice;
}

/* carries out the action that the user requests */
void execute_action(char choice){
    struct Node *head = NULL;
    char filename[MAX_NAME_LENGTH];
    fgets(filename, MAX_NAME_LENGTH, stdin);
    switch(choice){
        case '1':
            create_Note();
            break;
        case '2':                       /* conditionally complete */
            head = create_list();
            printList(head);
            print_file();
            break;
        case '3':
            //delete_Note();
            break;
        default:
            printf("Invalid option: Enter a number 1-4\n");
            break;

    }

}

/* creates a list of all .txt files in the directory */
struct Node *create_list(){
    DIR *d;
    struct dirent *dir;
    struct Node* head = NULL;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name, FILE_EXTENSION)){
                append(&head, dir->d_name);
            }
        }
        closedir(d);
    }
    return head;
}

/* prints out the contents of a file */
void print_file(){
    char filename[MAX_NAME_LENGTH];
    char line[BUFFER_SIZE];
    FILE *fp;
    printf("Type the full name without extension of the Note you would like to view: ");
    scanf("%s", filename);
    strcat(filename, FILE_EXTENSION);
    fp = fopen(filename, "r");
    while(fp == NULL){
        printf("Enter a valid filename: ");
        scanf("%s", filename);
        strcat(filename, FILE_EXTENSION);
        fp = fopen(filename, "r");
    }
    while(fgets(line, BUFFER_SIZE, fp) != NULL)
        printf("%s", line);
    if(feof(fp))
        printf("\n");
    else
        printf("\nError\n");
    fclose(fp);
}

/*void create_Note(){
    const char *filename;
    FILE *fp;
    filename = make_filename();
    strcat(filename, FILE_EXTENSION);
    fp = fopen(filename, "w");
    fclose(fp);
}*/

void create_Note(){
    time_t mytime;
    int i;
    char *token;
    char *totalTime;
    FILE *fp;
    mytime = time(NULL);
    char *filename = (char*)malloc(sizeof(char)*30);
    totalTime = ctime(&mytime);
    strtok(totalTime, " ");
    token = strtok(NULL, " ");
    strcpy(filename, token);
    strcat(filename, "_");
    token = strtok(NULL, " ");
    strcat(filename , token);
    strcat(filename, "_");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");
    strncat(filename, token, 4);
    strcat(filename, FILE_EXTENSION);
    fp = fopen(filename, "w");
    if(fp == NULL)
        printf("Failed to create file.\n");
    else
        printf("File %s successfully created.\n", filename);
    fclose(fp);
}

