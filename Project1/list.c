#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

/*
struct _ListNode
{
    char key[STRING_LENGTH];
    char value[STRING_LENGTH];
    struct ListNode* next;
};
*/

void printList(node* head)
{
    while (head != NULL) {
        printf("Key: %s\nValue: %s\n\n", head->key, head->value);
        head = head->next;
    }
}
int lenList(node* head)
{
    int len = 0;
    node* current = head;
    while (current != NULL)
    {
        len++;
        current = current->next;
    }
    return len;
}

void push(node** head, char* key, char* value)
{
    node* newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->key, key);
    strcpy(newnode->value, value);
    newnode->next = (*head);
    (*head) = newnode;
}
void append(node** head, char* key, char* value)
{
    node* newnode = (node*)malloc(sizeof(node));
    node* last = *head;
    strcpy(newnode->key, key);
    strcpy(newnode->value, value);
    newnode->next = NULL;

    if (*head == NULL)
    {
        *head = newnode;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newnode;
    return;
}

void pop(node** head)
{
    node* temp = *head;
    *head = (*head)->next;
    free(temp);
}
void delLast(node** head)
{
    node* last = *head;
    node* prev = NULL;
    while (last->next != NULL)
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    free(last);
}
void delKey(node** head, char* key)
{
    node* temp = *head, * prev = NULL;
    if (temp != NULL && !strcmp(temp->key, key)) {
        *head = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->key, key)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        return;
    }
    prev->next = temp->next;
    free(temp);
}

node* getByPos(node* head, int pos)
{
    return NULL;//TODO: is it needed? we only probably will need getbykey, pos is relative to push/append
}
node* getByKey(node* head, char* key)
{
    node* temp = head;
    while (temp != NULL && strcmp(temp->key, key))
    {
        temp = temp->next;
    }
    return temp;
}
node* getNext(node* head)
{
    if (head->next != NULL)
    {
        return head->next;
    }
    else
    {
        return NULL;
    }
}
bool checkKey(node* head, char* key)
{
    node* temp = head;
    while (temp != NULL)
    {
        if (!strcmp(temp->key, key))
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void changeByPos(node* head, int pos, char* value)
{
    // TODO: is it needed? we only probably will need getbykey, pos is relative to push/append
    // return NULL;
}
void changeByKey(node* head, char* key, char* value)
{
    node* temp = getByKey(head, key);
    strcpy(temp->value, value);
}

void freeList(node** head)
{
    if ((*head) != NULL)
    {
        if ((*head)->next != NULL)
        {
            freeList(&(*head)->next);
        }
        free(*head);
        *head = NULL;
    }
    return;
}