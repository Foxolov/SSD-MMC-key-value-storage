typedef struct MySSD
{
    char name[80];
    int pageSize;
    int blockSize;
    int blockAmt;
} MySSD;

MySSD* MySSD_init(char*, int, int, int);

void SSDWritePage(MySSD*, char*, int, int);

char* SSDReadPage(MySSD*, char*, int, int);

void SSDWipeBlock(int);

void SSDDestructor(MySSD*);
