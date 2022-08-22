#ifndef __LIST_FOR_KEYVAL_SSD__
#define __LIST_FOR_KEYVAL_SSD__

#include <stdlib.h>
#include <stdbool.h>

#define STRING_LENGTH 64

typedef struct ListNode
{
    char key[STRING_LENGTH];
    char value[STRING_LENGTH];
    struct ListNode* next;
} node;

//All this must be static to prevent external access?----------------------------------------------
//misc functions
void printList(node* head);
int lenList(node* head);

//adders
void push(node** head, char* key, char* value);
void append(node** head, char* key, char* value);

//deleters
void pop(node** head);
void delLast(node** head);
void delKey(node** head, char* key);

//getters
node* getByPos(node* head, int pos);
node* getByKey(node* head, char* key);
node* getNext(node* head);
bool checkKey(node* head, char* key);

//modifiers
void changeByPos(node* head, int pos, char* value);
void changeByKey(node* head, char* key, char* value);

//free memory
void freeList(node** head);
//All this must be static to prevent external access?----------------------------------------------

#endif
