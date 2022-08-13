#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//#include "ssd.h"
#include "keyval.h"

int main()
{

    //MySSD_init("newssd",64,64,8);
    //printf("Done in main!\n");

    keyval* kv = SSDInit();
    char out[64];
    char key[] = "abc";
    puts(key);
    char value[] = "i am string";
    WriteString(kv, key, value);
    strcpy(out, ReadString(kv, key));
    printf("%s\n", out);
    SSDDeinit(kv);
    printf("Done in main!\n");

    return 0;
}
