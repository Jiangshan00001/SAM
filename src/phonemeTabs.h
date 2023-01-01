#ifndef PHONEMETABS_H
#define PHONEMETABS_H


//tab40682
extern unsigned char phonemeNameTable1[];

//tab40763
extern unsigned char PhonemeNameTable2[];

//tab45056
extern unsigned char freq1data[];

//tab451356
extern unsigned char freq2data[];

//tab45216
extern unsigned char freq3data[];

extern unsigned char ampl1data[];

extern unsigned char ampl2data[];

extern unsigned char ampl3data[];


//tab45616???
extern unsigned char phonemeStressedLengthTable[];

//tab45536???
extern unsigned char phonemeLengthTable[];

extern unsigned short flags[];

//loc_9F8C
enum {
    FLAG_PLOSIVE  = 0x0001,
    FLAG_STOPCONS = 0x0002, /* stop consonant */
    FLAG_VOICED   = 0x0004,
    /* 0x08 */
    FLAG_DIPTHONG = 0x0010,
    FLAG_DIP_YX   = 0x0020, /* dipthong ending with YX */
    FLAG_CONSONANT= 0x0040,
    FLAG_VOWEL    = 0x0080,
    FLAG_PUNCT    = 0x0100,
    /* 0x200 */
    FLAG_ALVEOLAR = 0x0400,
    FLAG_NASAL    = 0x0800,
    FLAG_LIQUIC   = 0x1000,  /* liquic consonant */
    FLAG_FRICATIVE= 0x2000
};

#endif
