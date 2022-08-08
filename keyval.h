#include <stdlib.h>

#include "ssd.h"

typedef struct StringObj
{
    char* key[16];
    char* value[48];
    int pos;
} StringObj;

typedef struct SSDInterface
{
    MySSD* ssd;
    int currPage;
    StringObj* table[64 * 8];
    int curri;
    //int pageSize;
    //int blockSize;
    //int blockAmt;
    //char buf[64*64*8];
} SSD;

SSD* SSDInit();

void WriteString(SSD*, char*, char*);

char* ReadString(SSD*, char*);
