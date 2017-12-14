/*
 *
 * Mathew McHugh
 * C Program that manages a directory of notes
 * Allows for opening and reading specific notes
 * As well as the creation of new notes
 *
 */
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "linkedList.h"
#include <stdlib.h>

#define EXIT_VAL '5'
#define BUFFER_SIZE 255
#define MAX_USER_NAME_LENGTH 20
#define FILE_EXTENSION ".txt"


char promp_user();
void execute_action(char choice, char* user);
struct Node *create_list();
void print_file();
void create_Note(char *user);
void delete_Note();
char *make_filename();
void populate_Note(FILE* fp, char *filename, char* author, char *time);
void edit_Note();

int main(void)
{
    int choice;
    char user[MAX_USER_NAME_LENGTH];
    printf(" -----   Welcomes to the Note Record System   -----\n\n");
    printf("Enter your username: ");
    scanf( "%s", user);
    do{
        choice = promp_user();
        execute_action(choice, user);
    }while (choice != EXIT_VAL);
    return(0);
}

char promp_user(){
    char choice;
    printf("Options: \n     1: Create a new Note\n     2: View an existing Note\n     3: Delete an old Note\n     4: Edit an existing Note\n     5: Exit\n\n");
    printf("Enter the number of your selection: ");
    scanf(" %c", &choice);
    return choice;
}

/* carries out the action that the user requests */
void execute_action(char choice, char *user){
    struct Node *head = NULL;
    printf("\n");
    head = create_list();
    switch(choice){
        case '1':
            create_Note(user);
            break;
        case '2':                       /* conditionally complete */
            printList(head);
            print_file();
            break;
        case '3':
            printList(head);
            delete_Note();
            break;
        case '4':
            printList(head);
            edit_Note();
            break;
        case EXIT_VAL:
            break;
        default:
            printf("Invalid option: Enter a number 1-5\n");
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
    printf("-------------------------------------------------------------------------\n");
    while(fgets(line, BUFFER_SIZE, fp) != NULL)
        printf("%s", line);
    if(feof(fp))
        printf("\n-------------------------------------------------------------------------\n");
    else
        printf("\nError\n");
    fclose(fp);
}


void create_Note(char *user){
    time_t mytime;
    char *token;
    char *totalTime;
    FILE *fp;
    mytime = time(NULL);
    char *filename = (char*)malloc(sizeof(char)*MAX_NAME_LENGTH);
    printf("Type a custom Note name, or press <enter> for the default name: ");
    fgets(filename, MAX_NAME_LENGTH, stdin);
    if(!strcmp(filename, "\n")){
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
    }
    else{
        filename[strlen(filename)-1] = 0;
        strcat(filename, FILE_EXTENSION);
    }
    fp = fopen(filename, "w");
    if(fp == NULL)
        printf("Failed to create file.\n");
    else{
        populate_Note(fp, filename, user, ctime(&mytime));
        printf("File %s successfully created.\n", filename);
    }
    fclose(fp);
}

void populate_Note(FILE* fp, char *filename, char* author, char *time){
    fprintf(fp,"Title: %s\nAuthor: %s\nCreated: %s\nBody:", filename, author, time);
}

void delete_Note(){
    char filename[MAX_NAME_LENGTH];
    printf("Enter the name without extension of the Note you would like to delete: ");
    fgets(filename, MAX_NAME_LENGTH, stdin);
    filename[strlen(filename)-1] = 0;
    strcat(filename, FILE_EXTENSION);
    if(remove(filename) == 0)
        printf("File %s successfully deleted.\n", filename);
    else
        printf("Could not delete file %s.\n", filename);
}

//non functional, problem with newline in buffer
void edit_Note(){
    char filename[MAX_NAME_LENGTH];
    char command[MAX_NAME_LENGTH + 5];
    int ch;
    FILE *fp = NULL;
    while ((ch = getchar()) != '\n' && ch != EOF){}
    do{
        printf("Enter the name without extension of the Note you would like to edit or quit to exit: ");
        fgets(filename, MAX_NAME_LENGTH, stdin);
        if(!strcmp(filename, "quit\n"))
            return;
        filename[strlen(filename)-1] = 0;
        strcat(filename, FILE_EXTENSION);
        fp = fopen(filename, "r");
    }while(fp == NULL);
    strcpy(command, "gvim ");
    strcat(command, filename);
    system(command);


}

