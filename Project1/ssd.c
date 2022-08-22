#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #include <unistd.h>


//#include <cstdint>

#include "ssd.h"

//#define POLYNOMIAL 0xD8
//#define WIDTH  (8 * sizeof(crc))
//#define TOPBIT (1 << (WIDTH - 1))

#define PAGE_SIZE 256
#define PAGE_COUNT 64
#define BLOCK_COUNT 8

typedef struct SSDSimulator
{
    char filePath[256];
    int pageSize;
    int blockSize;
    int blockAmt;
} ssd;

typedef struct _Example
{
	int size;
	int block;
	int amt;
} Example;

//typedef struct _Example Example;

ssd* SSDInit(char* name)//Most of this is mock-up/TODO for now
{
    ssd* pSSD = malloc(sizeof(ssd));
    strcpy(pSSD->filePath, name);
    pSSD->pageSize = PAGE_SIZE;
    pSSD->blockSize = PAGE_COUNT;
    pSSD->blockAmt = BLOCK_COUNT;
    //FILE* file;
    char path[100] = "files/";
    strcat(path, pSSD->filePath);
    strcpy(pSSD->filePath, path);
    return pSSD;
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

void SSDDeinit(ssd** ppSSD)
{
    free(*ppSSD);
    *ppSSD = NULL;
}
/*
uint8_t GenerateCRC(uint8_t const message[], int nBytes)
{
    uint8_t  remainder = 0;
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
*/
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

    return NULL;
}

void SSDWipeBlock(int BlockNum)
{
    //
}

char* SSDGetPath(ssd* ssd)
{
    return ssd->filePath;
}

size_t SSDWrite(ssd* pSSD, void* buf, unsigned size)
{
	if (pSSD == NULL)
	{
		printf("NULL pointer passed\n");
		return 0;
	}
	
    if ((buf == NULL) || (size == 0))
	{
		printf("No data to write\n");
		return 0;
	}


	FILE* file;
	file = fopen(pSSD->filePath, "wb");
	if (file == NULL)
	{
		printf("Cannot open file!\n");
		return 0;
	}

	size_t result = fwrite(buf, sizeof(char), size, file);
	fclose(file);
    return result;
}

void* SSDRead(ssd* pSSD, unsigned* size)
{
    FILE* file;
	file = fopen(pSSD->filePath, "rb");
	if (file == NULL)
	{
		printf("Cannot open file!\n");
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	unsigned fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = malloc(fileSize);
	if (buffer == NULL)
	{
		printf("Cannot allocate memory!\n");
		return NULL;
	}
	memset(buffer, 0, fileSize);

	fread(buffer, fileSize, sizeof(char), file);
	fclose(file);
    
    *size = fileSize;
    return buffer;
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
