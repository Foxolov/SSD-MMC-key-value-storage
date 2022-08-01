typedef struct MySSD
{
    char name[50];
    int pageSize;
    int blockSize;
    int blockAmt;
} MySSD;

MySSD MySSD_init(char*, int, int, int);

void MySSDinit(struct MySSD);
