#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "keyval.h"
//#include "ssd.h"

struct _ArrayEntry
{
    char key[STRING_LENGTH];
    char value[STRING_LENGTH];
};


keyval* KeyValInit()
{
    keyval* kv = malloc(sizeof(keyval));
    kv->ssd = SSDInit("ssd1");
    kv->head = NULL;
    ReadFromSSD(kv);
    return kv;//создаются объекты, выделяется память, читаем из файла, восстановл всего, что на диске
}
bool KeyValClear(keyval* kv)
{
    SSDClear(SSDGetPath(kv->ssd));
    freeList(&(kv->head));
    return true;
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
    if (checkKey(kv->head, key))
    {
        return false;
    }
    append(&(kv->head), key, value);
    return true;
}
bool ClearValue(keyval* kv, char* key)
{
    if (!checkKey(kv->head, key))
    {
        return false;
    }
    delKey(&(kv->head), key);
    return true;
}
char* ReadString(keyval* kv, char* key)
{
    if (!checkKey(kv->head, key))
    {
        return NULL;
    }
    return getByKey(kv->head, key)->value;
}
bool ModifyValue(keyval* kv, char* key, char* value)
{
    if (!checkKey(kv->head, key))
    {
        return false;
    }
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
    SSDWrite(kv->ssd, arr, sizeof(entry) * listSize);
    free(arr);
}

void ReadFromSSD(keyval* kv)
{
    unsigned size = 0;
    entry* arr = (entry*)SSDRead(kv->ssd, &size);// = (entry*)malloc(PAGE_SIZE * PAGE_COUNT * BLOCK_COUNT);

    if (arr == NULL || size == 0)
        return;

    for (size_t i = 0; i < size / sizeof(entry); i++)
    {
        append(&(kv->head), (arr + i)->key, (arr + i)->value);
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
