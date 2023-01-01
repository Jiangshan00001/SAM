#ifndef SAM_H
#define SAM_H

void SetInput(unsigned char *_input);
void SetSpeed(unsigned char _speed);
void SetPitch(unsigned char _pitch);
void SetMouth(unsigned char _mouth);
void SetThroat(unsigned char _throat);
void EnableSingmode();

int SAMMain();

char* GetBuffer();
int GetBufferLength();


extern unsigned char stress[256]; //numbers from 0 to 8
extern unsigned char phonemeLength[256]; //tab40160
extern unsigned char phonemeindex[256];

extern unsigned char phonemeIndexOutput[60]; //tab47296
extern unsigned char stressOutput[60]; //tab47365
extern unsigned char phonemeLengthOutput[60]; //tab47416

extern unsigned char speed;
extern unsigned char pitch;
extern int singmode;

extern char *buffer;
extern int bufferpos;
#endif
