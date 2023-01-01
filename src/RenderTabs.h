#ifndef RENDERTABS_H
#define RENDERTABS_H

extern unsigned char tab48426[5];

extern unsigned char tab47492[];


extern unsigned char amplitudeRescale[];

// Used to decide which phoneme's blend lengths. The candidate with the lower score is selected.
// tab45856
extern unsigned char blendRank[] ;


// Number of frames at the end of a phoneme devoted to interpolating to next phoneme's final value
//tab45696
extern unsigned char outBlendLength[];


// Number of frames at beginning of a phoneme devoted to interpolating to phoneme's final value
// tab45776
extern unsigned char inBlendLength[];


extern unsigned char sampledConsonantFlags[] ;


//tab40672
extern unsigned char stressInputTable[];

//tab42240
extern unsigned char sinus[];

//tab42496
extern unsigned char rectangle[];


//tab42752
extern unsigned char multtable[];

//random data ?
extern unsigned char sampleTable[0x500];


#endif
