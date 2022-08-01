#include <stdio.h>

#include "ssd.h"
#include "keyval.h"

int main()
{

    MySSD_init("newssd",64,64,8);
    printf("Done in main!\n");
    return 0;
}
