#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdint>

#include "ssd.h"

#define POLYNOMIAL 0xD8
#define WIDTH  (8 * sizeof(crc))
#define TOPBIT (1 << (WIDTH - 1))

#define PAGE_SIZE 256
#define PAGE_COUNT 64
#define BLOCK_COUNT 8

typedef uint8_t crc;

typedef struct SSDSimulator
{
    char filePath[256];
    int pageSize;
    int blockSize;
    int blockAmt;
} ssd;

ssd* SSDInit(char* name)//Most of this is mock-up/TODO for now
{
    ssd* ssd = malloc(sizeof(ssd));
    strcpy(ssd->filePath, name);
    ssd->pageSize = PAGE_SIZE;
    ssd->blockSize = PAGE_COUNT;
    ssd->blockAmt = BLOCK_COUNT;
    //FILE* file;
    char path[100] = "files/";
    strcat(path, ssd->filePath);
    strcpy(ssd->filePath, path);
    return ssd;
}
void SSDClear(char* name)//needs to take ssd, but error here
{
    FILE* file;
    file = fopen(name, "wb");
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        exit(1);
    }
    int totalSize = PAGE_SIZE * PAGE_COUNT * BLOCK_COUNT;
    //char fill[totalSize];
    char* fill;
    fill = malloc(totalSize * sizeof(char));
    memset(fill, '0', totalSize);
    fprintf(file, "%s", fill);
    fclose(file);
    free(fill);
}
void SSDDeinit(ssd** ssd)
{
    free(*ssd);
    *ssd = NULL;
}

crc GenerateCRC(uint8_t const message[], int nBytes)
{
    crc  remainder = 0;
    for (int byte = 0; byte < nBytes; ++byte)
    {
        remainder ^= (message[byte] << (WIDTH - 8));
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            if (remainder & TOPBIT)
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    return (remainder);
}

void SSDWritePage(ssd* ssd, char* buf, int pageNum, int size)
{
    FILE* file;
    file = fopen(ssd->filePath, "ab");
    fseek(file, pageNum * ssd->pageSize, SEEK_SET);
    for (int i = 0; i < size; i++)
    {
        putc(*buf++, file);
        fflush(file);
    }
    fclose(file);
}

char* SSDReadPage(ssd* ssd, char* buf, int pageNum, int size)
{
    FILE* file;
    file = fopen(ssd->filePath, "rb");
    fseek(file, pageNum * ssd->pageSize, SEEK_SET);
    for (int i = 0; i < size; i++)
    {
        *buf = i;
        buf++;
    }
    fclose(file);
}

void SSDWipeBlock(int BlockNum)
{
    //
}

char* SSDGetPath(ssd* ssd)
{
    return ssd->filePath;
}

void SSDWrite(ssd* ssd, void* buf, int len)
{
    FILE* file;
    file = fopen(ssd->filePath, "wb");
    write(file, buf, len);
    fclose(file);
}

void SSDRead(ssd* ssd, void *buf)
{
    FILE* file;
    file = fopen(ssd->filePath, "rb");
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        exit(1);
    }
    int len = PAGE_SIZE * PAGE_COUNT * BLOCK_COUNT;
    buf = malloc(len + 1);
    memset(buf, '0', len + 1);//
    read(file, buf, len);//error here
    printf("We're done writing!");
    fclose(file);
    //
}

/* функция балансирования записи - циклическая запись
 *
 * вид файла - "разметка" нулями
 *
 * таблица размещения файл-ключ-занимаемые физически страницы
 *
 * функция "произошел перебой питания" -
 * произошел_перебой=rand();
 * позиция_перебоя=rand();
 * выставить символ перебоя/удалить символы после позиции перебоя
 */
