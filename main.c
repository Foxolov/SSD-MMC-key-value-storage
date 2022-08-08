#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//#include "ssd.h"
#include "keyval.h"

int main()
{

    //MySSD_init("newssd",64,64,8);
    //printf("Done in main!\n");

    SSD* ssd = SSDInit();
    char* out[64];
    char key[] = "abc";
    char value[] = "i am string";
    WriteString(ssd, key, value);
    strcpy(*out, ReadString(ssd, key));
    printf("%s\n", *out);
    printf("Done in main!\n");

    return 0;
}
