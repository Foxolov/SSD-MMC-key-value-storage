typedef struct SSDSimulator ssd;

ssd* MySSD_init(char*, int, int, int);//Most of this is mock-up/TODO for now

void SSDWritePage(ssd*, char*, int, int);
char* SSDReadPage(ssd*, char*, int, int);
void SSDWipeBlock(int);
void SSDDeinit(ssd** ssd);

void SSDWrite(void* buf, int len);
void SSDRead(void* buf);
