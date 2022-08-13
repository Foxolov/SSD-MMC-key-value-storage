#include <stdlib.h>

#include "ssd.h"//create and add list lib

typedef struct StringObj
{
    char key[16];
    char value[48];
    int pos;
} StringObj;

typedef struct KeyVal
{
    ssd* ssd;
    int currPage;
    StringObj* table[64 * 8];//here be list
    int curri;
    //int pageSize;
    //int blockSize;
    //int blockAmt;
    //char buf[64*64*8];
} keyval;

keyval* SSDInit();

void SSDDeinit(keyval*);

void WriteString(keyval*, char*, char*);

char ReadString(keyval*, char*);
