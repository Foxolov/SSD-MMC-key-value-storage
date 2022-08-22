#ifndef __SSD_OBJECT__
#define __SSD_OBJECT__
#include <stdbool.h>

//typedef  crc;
typedef struct SSDSimulator ssd;

ssd* SSDInit(char* name);//Most of this is mock-up/TODO for now
void SSDClear(char* name);
void SSDDeinit(ssd** ppSSD);

//uint8_t GenerateCRC(uint8_t const message[], int nBytes);

void SSDWritePage(ssd*, char*, int, int);
char* SSDReadPage(ssd*, char*, int, int);
void SSDWipeBlock(int);
char* SSDGetPath(ssd* ssd);

size_t SSDWrite(ssd* pSSD, void* buf, unsigned size);
void* SSDRead(ssd* pSSD, unsigned* size);

#endif