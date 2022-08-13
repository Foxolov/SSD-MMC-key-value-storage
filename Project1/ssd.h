typedef struct SSDSimulator
{
    char name[80];
    int pageSize;
    int blockSize;
    int blockAmt;
} ssd;

ssd* MySSD_init(char*, int, int, int);

void SSDWritePage(ssd*, char*, int, int);

char* SSDReadPage(ssd*, char*, int, int);

void SSDWipeBlock(int);

void SSDDestructor(ssd*);
