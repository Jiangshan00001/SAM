#ifndef SAMTABS_H
#define SAMTABS_H

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

//tab40672
extern unsigned char stressInputTable[];

//tab40682
extern unsigned char signInputTable1[];

//tab40763
extern unsigned char signInputTable2[];

extern unsigned short flags[];


//tab45616???
extern unsigned char phonemeStressedLengthTable[];

//tab45536???
extern unsigned char phonemeLengthTable[];


#endif
