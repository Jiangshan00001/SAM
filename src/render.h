#ifndef RENDER_H
#define RENDER_H

void RenderOnce();
void SetMouthThroat(unsigned char mouth, unsigned char throat);

void ProcessFrames2Buffer(unsigned char frame_len);
void RenderConsonantSample(unsigned char *mem66, unsigned char consonantFlag, unsigned char mem49);
unsigned char CreateFrameTransitions();

#define PHONEME_PERIOD (1)
#define PHONEME_QUESTION (2)

#define RISING_INFLECTION (1)
#define FALLING_INFLECTION (255)


extern unsigned char pitches[256]; // tab43008

extern unsigned char frequency1[256];
extern unsigned char frequency2[256];
extern unsigned char frequency3[256];

extern unsigned char amplitude1[256];
extern unsigned char amplitude2[256];
extern unsigned char amplitude3[256];

extern unsigned char sampledConsonantFlag[256]; // tab44800


#endif
