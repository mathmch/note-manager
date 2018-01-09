#ifndef LINKEDLIST_H
#define LINKEDLIST_H


struct Node
{
    struct Node *next;
    char filename[];
};

/* Given a reference (pointer to pointer) to the head of a list and
   an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, char *filename);

/* Given a node prev_node, insert a new node after the given
   prev_node */
void insertAt(struct Node** head_ref, int index, char *filename);

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node** head_ref, char *filename);

// This function prints contents of linked list starting from head
void printList(struct Node *node);

void removeAt(struct Node** head_ref, int index);

struct Node *list_search(struct Node *head, char *filename);

void clean_list(struct Node *head);
#endif
