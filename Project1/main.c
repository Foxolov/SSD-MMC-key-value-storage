#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//#include "ssd.h"
#include "keyval.h"

int main()
{

    //MySSD_init("newssd",64,64,8);
    //printf("Done in main!\n");

    //List testing
    node* head = NULL;
    append(&head, "a", "123");
    append(&head, "b", "456");
    append(&head, "c", "789");
    //printf("Length is %d\n\n", lenList(head));
    printList(head);
    changeByKey(head, "a", "987654321");
    //delKey(&head, "a");
    //printf("Length is %d\n\n", lenList(head));
    printList(head);
    //List testing end


    /*
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
    */

    return 0;
}
