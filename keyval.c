#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "keyval.h"
//#include "ssd.h"

SSD* SSDInit()
{
    SSD pssd;
    SSD* ssd = &pssd;
    MySSD* curr = MySSD_init("ssd1", 64, 64, 8);
    ssd->ssd = curr;
    ssd->currPage = 0;
    return ssd;
}

void WriteString(SSD* ssd, char* key, char* value)
{
    StringObj strop;
    StringObj* stro = &strop;
    //strcpy_s(stro->key, 16, key);
    strcpy(stro->key, key);
    strcpy(stro->value, value);
    stro->pos = 0;
    int sizeObj = sizeof(stro->key) + sizeof(stro->value);
    //char toWrite[sizeObj];
    char* toWrite;
    toWrite = malloc((sizeObj+1) * sizeof(char));
    strcpy(toWrite, *stro->key);
    //strcat_s(toWrite, 48, stro->value);
    strcat(toWrite, stro->value);
    SSDWritePage(ssd->ssd, toWrite, ssd->currPage, sizeObj/*/8*/);
    stro->pos = ssd->currPage;
    ssd->table[ssd->curri] = stro;
    ssd->currPage++;
    ssd->curri++;
}

char* ReadString(SSD* ssd, char* key)
{
    char* point;
    char* res[48];
    int i = 0;
    while (!strcmp(*ssd->table[i]->key, key))
    {
        i++;
    }
    int seek = ssd->table[i]->pos;
    int sizeObj = sizeof(ssd->table[i]->key) + sizeof(ssd->table[i]->value);
    point = (char*)ssd->table[i];
    SSDReadPage(ssd->ssd, point, seek, sizeObj/*/8*/);
    strcpy(*res, *ssd->table[i]->value);
    return *res;
}

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
