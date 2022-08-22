#ifndef __KEYVAL_LIB_SSD__
#define __KEYVAL_LIB_SSD__

#include <stdlib.h>
#include <stdbool.h>

#include "ssd.h"
#include "list.h"

typedef struct StringObj //obsolete
{
    char key[16];
    char value[48];
    int pos;
} StringObj;


typedef struct _ArrayEntry entry;

typedef struct _KeyValueStorage//rework
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
} keyval;

//init/deinit
keyval* KeyValInit();//needs load from file
bool KeyValClear(keyval* kv);
bool KeyValDeinit(keyval** kv);//needs write to file

//interact with user (and ssd simulator)
bool WriteString(keyval* kv, char* key, char* value);
bool ClearValue(keyval* kv, char* key);
char* ReadString(keyval* kv, char* key);
bool ModifyValue(keyval* kv, char* key, char* value);

//interact with ssd simulator (create array for list interaction)
void WriteToSSD(keyval* kv);
void ReadFromSSD(keyval* kv);

#endif