typedef struct SSDSimulator ssd;

ssd* SSDInit(char* name);//Most of this is mock-up/TODO for now
void SSDClear(char* name);
void SSDDeinit(ssd** ssd);

crc GenerateCRC(uint8_t const message[], int nBytes);

void SSDWritePage(ssd*, char*, int, int);
char* SSDReadPage(ssd*, char*, int, int);
void SSDWipeBlock(int);
char* SSDGetPath(ssd* ssd);

void SSDWrite(ssd* ssd, void* buf, int len);
void SSDRead(ssd* ssd, void* buf);
