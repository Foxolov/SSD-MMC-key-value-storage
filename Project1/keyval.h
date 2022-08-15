#include <stdlib.h>
#include <stdbool.h>

#include "ssd.h"//create and add list lib NO!, list will be here

typedef struct StringObj //obsolete
{
    char key[16];
    char value[48];
    int pos;
} StringObj;

typedef struct _ListNode node;
typedef struct _ArrayEntry entry;
typedef struct _KeyValueStorage keyval;


//All this must be static to prevent external access?----------------------------------------------
//misc functions
void printList(node* head);
int lenList(node* head);

//adders
void push(node** head, char* key, char* value);
void append(node** head, char* key, char* value);

//deleters
void pop(node** head);
void delLast(node** head);
void delKey(node** head, char* key);

//getters
node* getByPos(node* head, int pos);
node* getByKey(node* head, char* key);
node* getNext(node* head);

//modifiers
void changeByPos(node* head, int pos, char* value);
void changeByKey(node* head, char* key, char* value);

//free memory
void freeList(node** head);
//All this must be static to prevent external access?----------------------------------------------


//init/deinit
keyval* KeyValInit();//needs load from file
bool KeyValDeinit(keyval** kv);//needs write to file

//interact with user (and ssd simulator)
bool WriteString(keyval* kv, char* key, char* value);
bool ClearValue(keyval* kv, char* key);
char* ReadString(keyval* kv, char* key);
bool ModifyValue(keyval* kv, char* key, char* value);

//interact with ssd simulator (create array for list interaction)
void WriteToSSD(keyval* kv);
void ReadFromSSD(keyval* kv);
