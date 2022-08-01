#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ssd.h"

MySSD MySSD_init(char*, int, int, int);

void MySSDinit(struct MySSD);

MySSD MySSD_init(char* name, int pageSize, int blockSize, int blockAmt)
{
    MySSD ssd;
    strcpy(ssd.name, name);
    ssd.pageSize = pageSize;
    ssd.blockSize = blockSize;
    ssd.blockAmt = blockAmt;
    FILE* file;
    char path[100] = "files/";
    strcat(path, ssd.name);
    strcat(path, ".txt");
    file = fopen(path, "w");
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        exit(1);
    }
    //fputs("SSD name :\n", file);
    //fputs("64,64,8\n", file);
    fprintf(file, "SSD name: %s\n", ssd.name);
    fprintf(file, "%d, %d, %d;\n", ssd.pageSize, ssd.blockSize, ssd.blockAmt);
    fclose(file);
    printf("I'm done!\n");
    return ssd;
}

void MySSDinit(struct MySSD ssd)
{
    FILE* file;
    char path[100] = "/files/";
    strcat(path, ssd.name);
    strcat(path, ".txt");
    file = fopen(path, "w");
    //fputs("SSD name :\n", file);
    fprintf(file, "SSD name: %s\n", ssd.name);
    fprintf(file, "%d, %d, %d;\n", ssd.pageSize, ssd.blockSize, ssd.blockAmt);
    fclose(file);
    return;
}

/* функция балансирования записи - циклическая запись; при перезаписи
 * блока - выбор блока с наименьшим износом
 *
 * вид файла - "разметка" границ страниц и блоков с указанием износа
 * страниц
 *
 * функция "произошел перебой питания" -
 * произошел_перебой=rand();
 * позиция_перебоя=rand();
 * выставить символ перебоя/удалить символы после позиции перебоя
 */
