/* linked list implementation*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/* A linked list node */
struct Node
{
  char filename[MAX_NAME_LENGTH];
  struct Node *next;
};

/* Given a reference (pointer to pointer) to the head of a list and
   an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, char *filename)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    /* 2. put in the data  */
    strncpy(new_node->filename, filename, MAX_NAME_LENGTH+1);
    /* 3. Make next of new node as head */
    new_node->next = (*head_ref);

    /* 4. move the head to point to the new node */
    (*head_ref)    = new_node;
}

/* Given a node prev_node, insert a new node after the given
   prev_node */
void insertAt(struct Node** head_ref, int index, char *filename)
{
    /*1. check if the given prev_node is NULL */
    if (*head_ref == NULL)
      return;
    if (index != 1)
        insertAt(&((*head_ref)->next), --index, filename);

    /* 2. allocate new node */
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node));

    /* 3. put in the data  */
    strncpy(new_node->filename, filename, MAX_NAME_LENGTH);

    /* 4. Make next of new node as next of prev_node */
    new_node->next = (*head_ref)->next;

    /* 5. move the next of prev_node as new_node */
    (*head_ref)->next = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, char* filename)
{
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    struct Node *last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    strncpy(new_node->filename, filename, MAX_NAME_LENGTH);
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

/* This function prints contents of linked list starting from head */
void printList(struct Node *node)
{
    FILE *fp;
    int i;
    char line[BUFFER_SIZE];
    struct Node *unformatted = NULL;
    if(node == NULL)
        return;
    printf("-------------------------------------------------------------------------\n\n");
    printf("Formatted Files:\n");
    while (node != NULL)
    {
        if(validate_file(node->filename)){
            fp = fopen(node->filename, "r");
            printf("%s ------> ", node->filename);
            for(i = 0; i < HEADER_LINES; i++){
                fgets(line, BUFFER_SIZE, fp);
                line[strlen(line)-1] = 0;
                printf("%s    ", line);
            }
            printf("\n");
            fclose(fp);
            node = node->next;
        }
        else{
            append(&unformatted, node->filename);
            node = node->next;
        }
    }
    printf("\nUnformatted Files:\n");
    if(unformatted == NULL){
        printf("\n-------------------------------------------------------------------------\n");
        return;
    }
    while(unformatted != NULL){
        printf("%s\n", unformatted->filename);
        unformatted = unformatted->next;
    }
    printf("\n-------------------------------------------------------------------------\n");
}

void removeAt(struct Node** head_ref, int index){
    if (*head_ref == NULL)
        return;
    if(index == 0){
        *head_ref = (*head_ref)->next;
        return;
    }
    if(index != 1)
        removeAt(&((*head_ref)->next), --index);
    else if((*head_ref)->next == NULL)
        return;
    else{
        (*head_ref)->next = (*head_ref)->next->next;
    }
}

struct Node *list_search(struct Node *head, char* filename){
    while(head != NULL){
        if (strcmp(head->filename, filename))
            return head;
        head = head->next;
    }
    return NULL;
}

void clean_list(struct Node *head){
    if (head != NULL)
        clean_list(head->next);
    free(head);
}
