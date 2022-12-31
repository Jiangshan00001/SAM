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


//tab45056
extern unsigned char freq1data[];

//tab451356
extern unsigned char freq2data[];

//tab45216
extern unsigned char freq3data[];

extern unsigned char ampl1data[];

extern unsigned char ampl2data[];

extern unsigned char ampl3data[];



//tab42240
extern unsigned char sinus[];

//tab42496
extern unsigned char rectangle[];


//tab42752
extern unsigned char multtable[];

//random data ?
extern unsigned char sampleTable[0x500];


#endif
