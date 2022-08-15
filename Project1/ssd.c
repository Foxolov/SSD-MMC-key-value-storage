#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ssd.h"

ssd* MySSD_init(char* name, int pageSize, int blockSize, int blockAmt)
{
    ssd pssd;
    ssd* ssd = &pssd;
    strcpy(ssd->name, name);
    ssd->pageSize = pageSize;
    ssd->blockSize = blockSize;
    ssd->blockAmt = blockAmt;
    FILE* file;
    char path[100] = "files/";
    strcat(path, ssd->name);
    //strcat(path, ".txt");
    strcpy(ssd->name, path);
    file = fopen(ssd->name, "wb");
    if (file == NULL)
    {
        printf("Cannot open file!\n");
        exit(1);
    }
    int totalSize = ssd->pageSize * ssd->blockSize * ssd->blockAmt;
    //char fill[totalSize];
    char* fill;
    fill = malloc(totalSize * sizeof(char));
    memset(fill, '0', totalSize);
    fprintf(file, "%s", fill);
    fclose(file);
    free(fill);
    printf("I'm done!\n");
    return ssd;
}

void SSDWritePage(ssd* ssd, char* buf, int pageNum, int size)
{
    FILE* file;
    file = fopen(ssd->name, "ab");
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
    file = fopen(ssd->name, "rb");
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

}

void SSDDestructor(ssd* ssd)
{
    free(ssd);
}

/* ������� �������������� ������ - ����������� ������
 *
 * ��� ����� - "��������" ������
 *
 * ������� ���������� ����-����-���������� ��������� ��������
 *
 * ������� "��������� ������� �������" -
 * ���������_�������=rand();
 * �������_�������=rand();
 * ��������� ������ �������/������� ������� ����� ������� �������
 */