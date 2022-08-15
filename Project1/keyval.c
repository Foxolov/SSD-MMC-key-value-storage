#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "keyval.h"
//#include "ssd.h"

#define STRING_LENGTH 64
#define PAGE_SIZE 256
#define PAGE_COUNT 64
#define BLOCK_COUNT 8

struct _ListNode
{
    char key[STRING_LENGTH];
    char value[STRING_LENGTH];
    struct ListNode* next;
};
struct _ArrayEntry
{
    char key[STRING_LENGTH];
    char value[STRING_LENGTH];
};
struct _KeyValueStorage//rework
{
    ssd* ssd;
    //int currPage;
    node* head;
    //StringObj* table[64 * 8];//here be list
    //int curri;
    //int pageSize;
    //int blockSize;
    //int blockAmt;
    //char buf[64*64*8];
};

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

void changeByPos(node* head, int pos, char* value)
{
    return NULL;//TODO: is it needed? we only probably will need getbykey, pos is relative to push/append
}
void changeByKey(node* head, char* key, char* value)
{
    node* temp = getByKey(head, key);
    strcpy(temp->value, value);
}

void freeList(node** head)
{
    if ((*head)->next != NULL)
    {
        freeList(&(*head)->next);
    }
    free(*head);
    *head = NULL;
}


keyval* KeyValInit()
{
    keyval* kv = malloc(sizeof(keyval));
    kv->ssd = MySSD_init("ssd1", PAGE_SIZE, PAGE_COUNT, BLOCK_COUNT);
    kv->head = NULL;
    ReadFromSSD(kv);
    return kv;//создаются объекты, выделяется память, читаем из файла, восстановл всего, что на диске
}
bool KeyValDeinit(keyval** kv)
{
    WriteToSSD(*kv);
    SSDDeinit(&((*kv)->ssd));
    freeList(&((*kv)->head));
    free(*kv);//сохранение на диске, удаление
    *kv = NULL;
    return true;
}

bool WriteString(keyval* kv, char* key, char* value)
{
    append(&(kv->head), key, value);
    return true;
}
bool ClearValue(keyval* kv, char* key)
{
    delKey(&(kv->head), key);
    return true;
}
char* ReadString(keyval* kv, char* key)
{
    return getByKey(kv->head, key)->value;
}
bool ModifyValue(keyval* kv, char* key, char* value)
{
    changeByKey(kv->head, key, value);
    return true;
}

//interact with ssd simulator (create array for list interaction)
void WriteToSSD(keyval* kv)
{
    int listSize = lenList(kv->head);
    entry *arr = (entry*)malloc(sizeof(entry)*listSize);
    node* listWalk = kv->head;
    for (int i = 0; i < listSize; i++)
    {
        strcpy(arr[i].key, listWalk->key);
        strcpy(arr[i].value, listWalk->value);
        listWalk = listWalk->next;
    }
    SSDWrite(arr, listSize);
    free(arr);
}
void ReadFromSSD(keyval* kv)
{
    entry* arr = (entry*)malloc(PAGE_SIZE * PAGE_COUNT * BLOCK_COUNT);
    SSDRead(arr);
    int i = 0;
    while (strcmp(arr[i].key, ""))
    {
        append(&(kv->head), arr[i].key, arr[i].value);
        i++;
    }
    free(arr);
}

//OBSOLETE
/*
bool WriteString(keyval* kv, char* key, char* value)
{
    StringObj strop;
    StringObj* stro = &strop;//malloc
    //strcpy_s(stro->key, 16, key);
    strcpy(stro->key, key);
    puts(stro->key);
    strcpy(stro->value, value);
    stro->pos = 0;
    //int sizeObj = sizeof(stro->key) + sizeof(stro->value);
    //char toWrite[sizeObj];
    char* toWrite = malloc(sizeof(StringObj)+1);
    memset(toWrite, 0, sizeof(StringObj) + 1);
    strcpy(toWrite, stro->key);//read the manual
    //strcpy(toWrite, &(stro.key));//as a variant
    //strcat_s(toWrite, 48, stro->value);
    strcat(toWrite, stro->value);
    SSDWritePage(kv->ssd, toWrite, kv->currPage, sizeof(StringObj) + 1);//try to write bin, not chars?
    free(toWrite);
    toWrite = NULL;
    //DO NOT cpy/cat, just give the pointer to malloced stro, let lower level do the write
    stro->pos = kv->currPage;
    kv->table[kv->curri] = stro;
    kv->currPage++;
    kv->curri++;
}

bool ReadString(keyval* kv, char* key, char* value)
{
    char point;
    char res[48];
    int i = 0;
    while (!strcmp(kv->table[i]->key, key))
    {
        i++;
    }
    int seek = kv->table[i]->pos;
    int sizeObj = sizeof(kv->table[i]->key) + sizeof(kv->table[i]->value);
    point = (char*)kv->table[i];
    SSDReadPage(kv->ssd, point, seek, sizeObj);
    strcpy(res, kv->table[i]->value);
    return res;
}
*/

/* выбор ключа - пользовательский
 *
 * хранить исходный crc для проверки целостности файла рядом с "данными"
 *
 * https://ru.wikipedia.org/wiki/%D0%A6%D0%B8%D0%BA%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B8%D0%B7%D0%B1%D1%8B%D1%82%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4
 *
 * https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 *
 * https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%A6%D0%B8%D0%BA%D0%BB%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%B9_%D0%B8%D0%B7%D0%B1%D1%8B%D1%82%D0%BE%D1%87%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4
 */
