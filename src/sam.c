#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "debug.h"
#include "sam.h"
#include "render.h"
#include "phonemeTabs.h"
#include "RenderTabs.h"
enum {
    pR    = 23,
    pD    = 57,
    pT    = 69,
    BREAK = 254,
    END   = 255
};


unsigned short flags[]={
    0x8000 , 0xC100 , 0xC100 , 0xC100 , 0xC100 , 0x00A4 , 0x00A4 , 0x00A4 ,
    0x00A4 , 0x00A4 , 0x00A4 , 0x0084 , 0x0084 , 0x00A4 , 0x00A4 , 0x0084 ,
    0x0084 , 0x0084 , 0x0084 , 0x0084 , 0x0084 , 0x0084 , 0x0044 , 0x1044 ,
    0x1044 , 0x1044 , 0x1044 , 0x084C , 0x0C4C , 0x084C , 0x0448 , 0x404C ,

    0x2440 , 0x2040 , 0x2040 , 0x2440 , 0x0040 , 0x0040 , 0x2444 , 0x2044 ,
    0x2044 , 0x2444 , 0x2048 , 0x2040 , 0x004C , 0x2044 , 0x0000 , 0x0000 ,
    0x00B4 , 0x00B4 , 0x00B4 , 0x0094 , 0x0094 , 0x0094 , 0x004E , 0x004E ,

    0x004E , 0x044E , 0x044E , 0x044E , 0x004E , 0x004E , 0x004E , 0x004E ,
    0x004E , 0x004E , 0x004B , 0x004B , 0x004B , 0x044B , 0x044B , 0x044B ,
    0x004B , 0x004B , 0x004B , 0x004B , 0x004B , 0x004B , 0x0080 , 0x00C1 ,
    0x00C1
};



/*

Ind  | phoneme |  flags   |
-----|---------|----------|
0    |   *     | 00000000 |
1    |  .*     | 00000000 |
2    |  ?*     | 00000000 |
3    |  ,*     | 00000000 |
4    |  -*     | 00000000 |

VOWELS
5    |  IY     | 10100100 |
6    |  IH     | 10100100 |
7    |  EH     | 10100100 |
8    |  AE     | 10100100 |
9    |  AA     | 10100100 |
10   |  AH     | 10100100 |
11   |  AO     | 10000100 |
17   |  OH     | 10000100 |
12   |  UH     | 10000100 |
16   |  UX     | 10000100 |
15   |  ER     | 10000100 |
13   |  AX     | 10100100 |
14   |  IX     | 10100100 |

DIPTHONGS
48   |  EY     | 10110100 |
49   |  AY     | 10110100 |
50   |  OY     | 10110100 |
51   |  AW     | 10010100 |
52   |  OW     | 10010100 |
53   |  UW     | 10010100 |


21   |  YX     | 10000100 |
20   |  WX     | 10000100 |
18   |  RX     | 10000100 |
19   |  LX     | 10000100 |
37   |  /X     | 01000000 |
30   |  DX     | 01001000 |


22   |  WH     | 01000100 |


VOICED CONSONANTS
23   |  R*     | 01000100 |
24   |  L*     | 01000100 |
25   |  W*     | 01000100 |
26   |  Y*     | 01000100 |
27   |  M*     | 01001100 |
28   |  N*     | 01001100 |
29   |  NX     | 01001100 |
54   |  B*     | 01001110 |
57   |  D*     | 01001110 |
60   |  G*     | 01001110 |
44   |  J*     | 01001100 |
38   |  Z*     | 01000100 |
39   |  ZH     | 01000100 |
40   |  V*     | 01000100 |
41   |  DH     | 01000100 |

unvoiced CONSONANTS
32   |  S*     | 01000000 |
33   |  SH     | 01000000 |
34   |  F*     | 01000000 |
35   |  TH     | 01000000 |
66   |  P*     | 01001011 |
69   |  T*     | 01001011 |
72   |  K*     | 01001011 |
42   |  CH     | 01001000 |
36   |  /H     | 01000000 |

43   |  **     | 01000000 |
45   |  **     | 01000100 |
46   |  **     | 00000000 |
47   |  **     | 00000000 |


55   |  **     | 01001110 |
56   |  **     | 01001110 |
58   |  **     | 01001110 |
59   |  **     | 01001110 |
61   |  **     | 01001110 |
62   |  **     | 01001110 |
63   |  GX     | 01001110 |
64   |  **     | 01001110 |
65   |  **     | 01001110 |
67   |  **     | 01001011 |
68   |  **     | 01001011 |
70   |  **     | 01001011 |
71   |  **     | 01001011 |
73   |  **     | 01001011 |
74   |  **     | 01001011 |
75   |  KX     | 01001011 |
76   |  **     | 01001011 |
77   |  **     | 01001011 |


SPECIAL
78   |  UL     | 10000000 |
79   |  UM     | 11000001 |
80   |  UN     | 11000001 |
31   |  Q*     | 01001100 |

*/
/// @addtogroup KeyVars
/// @{
///



///
/// \brief input user input string
/// length is 256 fixed.
/// input english text and then translated to phoneme names string.
/// if you want to change the length.
/// \ref input and \ref inputtemp is to be changed.
unsigned char input[256];

/// \brief standard sam sound speed
///
unsigned char speed = 72;
///
/// \brief pitch
///
unsigned char pitch = 64;
///
/// \brief mouth
///
unsigned char mouth = 128;
///
/// \brief throat
///
unsigned char throat = 128;
///
/// \brief singmode
///
int singmode = 0;

///
/// \brief stress
/// \ref phonemeindex \ref phonemeLength \ref stress  is the phoneme
/// list
unsigned char stress[256]; //numbers from 0 to 8
///
/// \brief phonemeLength
/// \ref phonemeindex \ref phonemeLength \ref stress  is the phoneme
/// list
unsigned char phonemeLength[256]; //tab40160
///
/// \brief phonemeindex
/// \ref phonemeindex \ref phonemeLength \ref stress  is the phoneme
/// list
unsigned char phonemeindex[256];

///
/// \brief phonemeIndexOutput
/// copy of \ref phonemeindex
unsigned char phonemeIndexOutput[60]; //tab47296
///
/// \brief stressOutput
/// copy of \ref stress
unsigned char stressOutput[60]; //tab47365
///
/// \brief phonemeLengthOutput
/// copy of \ref phonemeLength
unsigned char phonemeLengthOutput[60]; //tab47416



///
/// @}
///

void SetInput(unsigned char *_input)
{
    int i;
    size_t  l;
	l = strlen((char*)_input);
	if (l > 254) l = 254;
    for(i=0; i<(int)l; i++)
		input[i] = _input[i];
	input[l] = 0;
}

void SetSpeed(unsigned char _speed) {speed = _speed;};
void SetPitch(unsigned char _pitch) {pitch = _pitch;};
void SetMouth(unsigned char _mouth) {mouth = _mouth;};
void SetThroat(unsigned char _throat) {throat = _throat;};
void EnableSingmode() {singmode = 1;};
char* GetBuffer(){return buffer;};
int GetBufferLength(){return bufferpos;};

void Init();
int PhonemeStr2PhonemeIdx();
void PhonemeidxChangeAccordRuleA();
int SAMMain(int is_english);
void CopyStress();
void SetPhonemeLength();
void AdjustLengthsAccordRuleb();
void CopyStopConsFrame();
void Insert(unsigned char position, unsigned char mem60, unsigned char mem59, unsigned char mem58);
void InsertBreath();
void RenderAll();
void SetMouthThroat(unsigned char mouth, unsigned char throat);

void Init() {
	int i;
	SetMouthThroat( mouth, throat);

	bufferpos = 0;
	// TODO, check for free the memory, 10 seconds of output should be more than enough
	buffer = malloc(22050*10); 

	for(i=0; i<256; i++) {
		stress[i] = 0;
		phonemeLength[i] = 0;
	}

	for(i=0; i<60; i++) {
		phonemeIndexOutput[i] = 0;
		stressOutput[i] = 0;
		phonemeLengthOutput[i] = 0;
	}
	phonemeindex[255] = END; //to prevent buffer overflow // ML : changed from 32 to 255 to stop freezing with long inputs
}

///
/// \brief SAMMain
/// \return
/// main process
int SAMMain(int is_english) {
	unsigned char X = 0; //!! is this intended like this?
	Init();
    /* FIXME: At odds with assignment in Init() */
	phonemeindex[255] = 32; //to prevent buffer overflow

    if (!PhonemeStr2PhonemeIdx()) return 0;
	if (debug) PrintPhonemes(phonemeindex, phonemeLength, stress);
    if(is_english)PhonemeidxChangeAccordRuleA();
	CopyStress();
	SetPhonemeLength();
    if(is_english)AdjustLengthsAccordRuleb();

    if(is_english)CopyStopConsFrame();

    do {
        if (phonemeindex[X] > 80)
        {
			phonemeindex[X] = END;
			break; // error: delete all behind it
		}
	} while (++X != 0);

    InsertBreath();

	if (debug) PrintPhonemes(phonemeindex, phonemeLength, stress);

    RenderAll();
	return 1;
}

///
/// \brief RenderAll
/// input: \ref phonemeindex \ref phonemeLength \ref stress
/// output: \ref buffer
/// 1. copy from  \ref phonemeindex \ref phonemeLength \ref stress
/// to \ref phonemeIndexOutput  \ref phonemeLengthOutput \ref stressOutput
/// and call RenderOnce
///
void RenderAll() {
	unsigned char srcpos  = 0; // Position in source
	unsigned char destpos = 0; // Position in output

	while(1) {
		unsigned char A = phonemeindex[srcpos];
        phonemeIndexOutput[destpos] = A;
        switch(A)
        {
        case END:
            RenderOnce();
			return;
		case BREAK:
			phonemeIndexOutput[destpos] = END;
            RenderOnce();
			destpos = 0;
            break;
        case 0:
            break;
        default:
            phonemeLengthOutput[destpos] = phonemeLength[srcpos];
            stressOutput[destpos]        = stress[srcpos];
            ++destpos;
            break;
        }
		++srcpos;
	}
}


void InsertBreath() {
	unsigned char mem54 = 255;
	unsigned char len = 0;
	unsigned char index; //variable Y

	unsigned char pos = 0;

	while((index = phonemeindex[pos]) != END) {
		len += phonemeLength[pos];
		if (len < 232) {
			if (index == BREAK) {
            } else if (!(flags[index] & FLAG_PUNCT)) {
                if (index == 0) mem54 = pos;
            } else {
                len = 0;
                Insert(++pos, BREAK, 0, 0);
            }
		} else {
            pos = mem54;
            phonemeindex[pos]  = 31;   // 'Q*' glottal stop
            phonemeLength[pos] = 4;
            stress[pos] = 0;

            len = 0;
            Insert(++pos, BREAK, 0, 0);
        }
        ++pos;
	}
}


// Iterates through the phoneme buffer, copying the stress value from
// the following phoneme under the following circumstance:
       
//     1. The current phoneme is voiced, excluding plosives and fricatives
//     2. The following phoneme is voiced, excluding plosives and fricatives, and
//     3. The following phoneme is stressed
//
//  In those cases, the stress value+1 from the following phoneme is copied.
//
// For example, the word LOITER is represented as LOY5TER, with as stress
// of 5 on the dipthong OY. This routine will copy the stress value of 6 (5+1)
// to the L that precedes it.



void CopyStress() {
    // loop thought all the phonemes to be output
	unsigned char pos=0; //mem66
    unsigned char Y;
	while((Y = phonemeindex[pos]) != END) {
		// if CONSONANT_FLAG set, skip - only vowels get stress
		if (flags[Y] & 64) {
            Y = phonemeindex[pos+1];

            // if the following phoneme is the end, or a vowel, skip
            if (Y != END && (flags[Y] & 128) != 0) {
                // get the stress value at the next position
                Y = stress[pos+1];
                if (Y && !(Y&128)) {
                    // if next phoneme is stressed, and a VOWEL OR ER
                    // copy stress from next phoneme to this one
                    stress[pos] = Y+1;
                }
            }
        }

		++pos;
	}
}

void Insert(unsigned char position/*var57*/, unsigned char phidx, unsigned char phlen, unsigned char phstress)
{
	int i;
	for(i=253; i >= position; i--) // ML : always keep last safe-guarding 255	
	{
		phonemeindex[i+1]  = phonemeindex[i];
		phonemeLength[i+1] = phonemeLength[i];
		stress[i+1]        = stress[i];
	}

    phonemeindex[position]  = phidx;
    phonemeLength[position] = phlen;
    stress[position]        = phstress;
}


signed int full_match(unsigned char sign1, unsigned char sign2) {
    unsigned char Y = 0;
    do {
        // GET FIRST CHARACTER AT POSITION Y IN signInputTable
        // --> should change name to PhonemeNameTable1
        unsigned char A = phonemeNameTable1[Y];
        
        if (A == sign1) {
            A = PhonemeNameTable2[Y];
            // NOT A SPECIAL AND MATCHES SECOND CHARACTER?
            if ((A != '*') && (A == sign2)) return Y;
        }
    } while (++Y != 81);
    return -1;
}

signed int wild_match(unsigned char sign1) {
    signed int Y = 0;
    do {
        if (PhonemeNameTable2[Y] == '*') {
            if (phonemeNameTable1[Y] == sign1) return Y;
		}
	} while (++Y != 81);
    return -1;
}



/// The input[] buffer contains a string of phonemes and stress markers along
/// the lines of:
///
///     DHAX KAET IHZ AH5GLIY. <0x9B>
///
/// The byte 0x9B marks the end of the buffer. Some phonemes are 2 bytes
/// long, such as "DH" and "AX". Others are 1 byte long, such as "T" and "Z".
/// There are also stress markers, such as "5" and ".".
///
/// The first character of the phonemes are stored in the table \ref phonemeNameTable1.
/// The second character of the phonemes are stored in the table \ref phonemeNameTable2.
/// The stress characters are arranged in low to high stress order in stressInputTable[].
///
/// The following process is used to parse the input[] buffer:
///
/// Repeat until the <0x9B> character is reached:
///
///        First, a search is made for a 2 character match for phonemes that do not
///        end with the '*' (wildcard) character. On a match, the index of the phoneme
///        is added to phonemeIndex[] and the buffer position is advanced 2 bytes.
///
///        If this fails, a search is made for a 1 character match against all
///        phoneme names ending with a '*' (wildcard). If this succeeds, the
///        phoneme is added to phonemeIndex[] and the buffer position is advanced
///        1 byte.
///
///        If this fails, search for a 1 character match in the stressInputTable[].
///        If this succeeds, the stress value is placed in the last stress[] table
///        at the same index of the last added phoneme, and the buffer position is
///        advanced by 1 byte.
///
///        If this fails, return a 0.
///
/// On success:
///
///    1. \ref phonemeIndex will contain the index of all the phonemes.
///    2. The last index in \ref phonemeIndex will be 255.
///    3. \ref stress will contain the stress value for each phoneme
/// \ref input holds the string of phonemes, each two bytes wide
/// \ref phonemeNameTable1 holds the first character of each phoneme
/// \ref phonemeNameTable2 holds te second character of each phoneme
/// \ref phonemeIndex holds the indexes of the phonemes after parsing input[]
///
/// The parser scans through the \ref input, finding the names of the phonemes
/// by searching phonemeNameTable1[] and phonemeNameTable2[]. On a match, it
/// copies the index of the phoneme into the phonemeIndexTable[].
///
/// The character <0x9B> marks the end of text in input[]. When it is reached,
/// the index 255 is placed at the end of the phonemeIndexTable[], and the
/// function returns with a 1 indicating success.
int PhonemeStr2PhonemeIdx()
{
	unsigned char sign1;
	unsigned char position = 0;
	unsigned char srcpos   = 0;

	memset(stress, 0, 256); // Clear the stress table.

	while((sign1 = input[srcpos]) != 155) { // 155 (\233) is end of line marker
		signed int match;
		unsigned char sign2 = input[++srcpos];
        if ((match = full_match(sign1, sign2)) != -1) {
            // Matched both characters (no wildcards)
            phonemeindex[position++] = (unsigned char)match;
            ++srcpos; // Skip the second character of the input as we've matched it
        } else if ((match = wild_match(sign1)) != -1) {
            // Matched just the first character (with second character matching '*'
            phonemeindex[position++] = (unsigned char)match;
        } else {
            // Should be a stress character. Search through the
            // stress table backwards.
            match = 8; // End of stress table. FIXME: Don't hardcode.
            while( (sign1 != stressInputTable[match]) && (match>0) ) --match;
            
            if (match == 0) return 0; // failure

            stress[position-1] = (unsigned char)match; // Set stress for prior phoneme
        }
	} //while

    phonemeindex[position] = END;
    return 1;
}


//change phonemelength depedendent on stress
void SetPhonemeLength() {
	int position = 0;
	while(phonemeindex[position] != 255) {
		unsigned char A = stress[position];
		if ((A == 0) || ((A&128) != 0)) {
			phonemeLength[position] = phonemeLengthTable[phonemeindex[position]];
		} else {
			phonemeLength[position] = phonemeStressedLengthTable[phonemeindex[position]];
		}
		position++;
	}
}

void CopyStopConsFrame() {
	unsigned char pos=0;

	while(phonemeindex[pos] != END) {
		unsigned char index = phonemeindex[pos];

        if ((flags[index] & FLAG_STOPCONS))
        {
            if ((flags[index] & FLAG_PLOSIVE))
            {
                unsigned char A;
                unsigned char X = pos;
                while(!phonemeindex[++X]); /* Skip pause */
                A = phonemeindex[X];
                if (A != END) {
                    if ((flags[A] & 8) || (A == 36) || (A == 37))
                    {++pos; continue;} // '/H' '/X'
                }
                
            }
            Insert(pos+1, index+1, phonemeLengthTable[index+1], stress[pos]);
            Insert(pos+2, index+2, phonemeLengthTable[index+2], stress[pos]);
            pos += 2;
        }
        ++pos;
	}
}


void ChangeRule(unsigned char position, unsigned char mem60, const char * descr)
{
    if (debug) printf("RULE: %s\n",descr);
    phonemeindex[position] = 13; //rule;
    Insert(position+1, mem60, 0, stress[position]);
}

void drule(const char * str) {
    if (debug) printf("RULE: %s\n",str);
}

void drule_pre(const char *descr, unsigned char X) {
    drule(descr);
    if (debug) {
        printf("PRE\n");
        printf("phoneme %d (%c%c) length %d\n", X, phonemeNameTable1[phonemeindex[X]], PhonemeNameTable2[phonemeindex[X]], phonemeLength[X]);
    }
}

void drule_post(unsigned char X) {
    if (debug) {
        printf("POST\n");
        printf("phoneme %d (%c%c) length %d\n", X, phonemeNameTable1[phonemeindex[X]], PhonemeNameTable2[phonemeindex[X]], phonemeLength[X]);
    }
}


// Rewrites the phonemes using the following rules:
//
//       <DIPTHONG ENDING WITH WX> -> <DIPTHONG ENDING WITH WX> WX
//       <DIPTHONG NOT ENDING WITH WX> -> <DIPTHONG NOT ENDING WITH WX> YX
//       UL -> AX L
//       UM -> AX M
//       <STRESSED VOWEL> <SILENCE> <STRESSED VOWEL> -> <STRESSED VOWEL> <SILENCE> Q <VOWEL>
//       T R -> CH R
//       D R -> J R
//       <VOWEL> R -> <VOWEL> RX
//       <VOWEL> L -> <VOWEL> LX
//       G S -> G Z
//       K <VOWEL OR DIPTHONG NOT ENDING WITH IY> -> KX <VOWEL OR DIPTHONG NOT ENDING WITH IY>
//       G <VOWEL OR DIPTHONG NOT ENDING WITH IY> -> GX <VOWEL OR DIPTHONG NOT ENDING WITH IY>
//       S P -> S B
//       S T -> S D
//       S K -> S G
//       S KX -> S GX
//       <ALVEOLAR> UW -> <ALVEOLAR> UX
//       CH -> CH CH' (CH requires two phonemes to represent it)
//       J -> J J' (J requires two phonemes to represent it)
//       <UNSTRESSED VOWEL> T <PAUSE> -> <UNSTRESSED VOWEL> DX <PAUSE>
//       <UNSTRESSED VOWEL> D <PAUSE>  -> <UNSTRESSED VOWEL> DX <PAUSE>


void rule_alveolar_uw(unsigned char X) {
    // ALVEOLAR flag set?
    if (flags[phonemeindex[X-1]] & FLAG_ALVEOLAR) {
        drule("<ALVEOLAR> UW -> <ALVEOLAR> UX");
        phonemeindex[X] = 16;
    }
}

void rule_ch(unsigned char X) {
    drule("CH -> CH CH+1");
    Insert(X+1, 43, 0, stress[X]);
}

void rule_j(unsigned char X) {
    drule("J -> J J+1");
    Insert(X+1, 45, 0, stress[X]);
}

void rule_g(unsigned char pos) {
    // G <VOWEL OR DIPTHONG NOT ENDING WITH IY> -> GX <VOWEL OR DIPTHONG NOT ENDING WITH IY>
    // Example: GO

    unsigned char index = phonemeindex[pos+1];
            
    // If dipthong ending with YX, move continue processing next phoneme
    if ((index != 255) && ((flags[index] & FLAG_DIP_YX) == 0)) {
        // replace G with GX and continue processing next phoneme
        drule("G <VOWEL OR DIPTHONG NOT ENDING WITH IY> -> GX <VOWEL OR DIPTHONG NOT ENDING WITH IY>");
        phonemeindex[pos] = 63; // 'GX'
    }
}


void change(unsigned char pos, unsigned char val, const char * rule) {
    drule(rule);
    phonemeindex[pos] = val;
}


void rule_dipthong(unsigned char p, unsigned short pf, unsigned char pos) {
    // <DIPTHONG ENDING WITH WX> -> <DIPTHONG ENDING WITH WX> WX
    // <DIPTHONG NOT ENDING WITH WX> -> <DIPTHONG NOT ENDING WITH WX> YX
    // Example: OIL, COW

    // If ends with IY, use YX, else use WX
    unsigned char A = (pf & FLAG_DIP_YX) ? 21 : 20; // 'WX' = 20 'YX' = 21
                
    // Insert at WX or YX following, copying the stress
    if (A==20) drule("insert WX following dipthong NOT ending in IY sound");
    else if (A==21) drule("insert YX following dipthong ending in IY sound");
    Insert(pos+1, A, 0, stress[pos]);
                
    if (p == 53) rule_alveolar_uw(pos); // Example: NEW, DEW, SUE, ZOO, THOO, TOO
    else if (p == 42) rule_ch(pos);     // Example: CHEW
    else if (p == 44) rule_j(pos);      // Example: JAY
}

void PhonemeidxChangeAccordRuleA() {
	unsigned char pos = 0; //mem66;
    unsigned char p;

	if (debug) printf("Parser2\n");

	while((p = phonemeindex[pos]) != END) {
		unsigned short pf;
		unsigned char prior;

        if (debug) printf("%d: %c%c\n", pos, phonemeNameTable1[p], PhonemeNameTable2[p]);

		if (p == 0) { // Is phoneme pause?
			++pos;
			continue;
		}

        pf = flags[p];
        prior = phonemeindex[pos-1];

        if ((pf & FLAG_DIPTHONG)) rule_dipthong(p, pf, pos);
        else if (p == 78) ChangeRule(pos, 24, "UL -> AX L"); // Example: MEDDLE
        else if (p == 79) ChangeRule(pos, 27, "UM -> AX M"); // Example: ASTRONOMY
        else if (p == 80) ChangeRule(pos, 28, "UN -> AX N"); // Example: FUNCTION
        else if ((pf & FLAG_VOWEL) && stress[pos]) {
            // RULE:
            //       <STRESSED VOWEL> <SILENCE> <STRESSED VOWEL> -> <STRESSED VOWEL> <SILENCE> Q <VOWEL>
            // EXAMPLE: AWAY EIGHT
            if (!phonemeindex[pos+1]) { // If following phoneme is a pause, get next
                p = phonemeindex[pos+2];
                if (p!=END && (flags[p] & FLAG_VOWEL) && stress[pos+2]) {
                    drule("Insert glottal stop between two stressed vowels with space between them");
                    Insert(pos+2, 31, 0, 0); // 31 = 'Q'
                }
            }
        } else if (p == pR) { // RULES FOR PHONEMES BEFORE R
            if (prior == pT) change(pos-1,42, "T R -> CH R"); // Example: TRACK
            else if (prior == pD) change(pos-1,44, "D R -> J R"); // Example: DRY
            else if (flags[prior] & FLAG_VOWEL) change(pos, 18, "<VOWEL> R -> <VOWEL> RX"); // Example: ART
        } else if (p == 24 && (flags[prior] & FLAG_VOWEL)) change(pos, 19, "<VOWEL> L -> <VOWEL> LX"); // Example: ALL
        else if (prior == 60 && p == 32) { // 'G' 'S'
            // Can't get to fire -
            //       1. The G -> GX rule intervenes
            //       2. Reciter already replaces GS -> GZ
            change(pos, 38, "G S -> G Z");
        } else if (p == 60) rule_g(pos);
		else {
            if (p == 72) {  // 'K'
                // K <VOWEL OR DIPTHONG NOT ENDING WITH IY> -> KX <VOWEL OR DIPTHONG NOT ENDING WITH IY>
                // Example: COW
                unsigned char Y = phonemeindex[pos+1];
                // If at end, replace current phoneme with KX
                if ((flags[Y] & FLAG_DIP_YX)==0 || Y==END) { // VOWELS AND DIPTHONGS ENDING WITH IY SOUND flag set?
                    change(pos, 75, "K <VOWEL OR DIPTHONG NOT ENDING WITH IY> -> KX <VOWEL OR DIPTHONG NOT ENDING WITH IY>");
                    p  = 75;
                    pf = flags[p];
                }
            }

            // Replace with softer version?
            if ((flags[p] & FLAG_PLOSIVE) && (prior == 32)) { // 'S'
                // RULE:
                //      S P -> S B
                //      S T -> S D
                //      S K -> S G
                //      S KX -> S GX
                // Examples: SPY, STY, SKY, SCOWL
                
                if (debug) printf("RULE: S* %c%c -> S* %c%c\n", phonemeNameTable1[p], PhonemeNameTable2[p],phonemeNameTable1[p-12], PhonemeNameTable2[p-12]);
                phonemeindex[pos] = p-12;
            } else if (!(pf & FLAG_PLOSIVE)) {
                p = phonemeindex[pos];
                if (p == 53) rule_alveolar_uw(pos);   // Example: NEW, DEW, SUE, ZOO, THOO, TOO
                else if (p == 42) rule_ch(pos); // Example: CHEW
                else if (p == 44) rule_j(pos);  // Example: JAY
            }
            
            if (p == 69 || p == 57) { // 'T', 'D'
                // RULE: Soften T following vowel
                // NOTE: This rule fails for cases such as "ODD"
                //       <UNSTRESSED VOWEL> T <PAUSE> -> <UNSTRESSED VOWEL> DX <PAUSE>
                //       <UNSTRESSED VOWEL> D <PAUSE>  -> <UNSTRESSED VOWEL> DX <PAUSE>
                // Example: PARTY, TARDY
                if (flags[phonemeindex[pos-1]] & FLAG_VOWEL) {
                    p = phonemeindex[pos+1];
                    if (!p) p = phonemeindex[pos+2];
                    if ((flags[p] & FLAG_VOWEL) && !stress[pos+1]) change(pos,30, "Soften T or D following vowel or ER and preceding a pause -> DX");
                }
            }
        }
        pos++;
	} // while
}

// Applies various rules that adjust the lengths of phonemes
//
//         Lengthen <FRICATIVE> or <VOICED> between <VOWEL> and <PUNCTUATION> by 1.5
//         <VOWEL> <RX | LX> <CONSONANT> - decrease <VOWEL> length by 1
//         <VOWEL> <UNVOICED PLOSIVE> - decrease vowel by 1/8th
//         <VOWEL> <UNVOICED CONSONANT> - increase vowel by 1/2 + 1
//         <NASAL> <STOP CONSONANT> - set nasal = 5, consonant = 6
//         <VOICED STOP CONSONANT> {optional silence} <STOP CONSONANT> - shorten both to 1/2 + 1
//         <LIQUID CONSONANT> <DIPTHONG> - decrease by 2
//
void AdjustLengthsAccordRuleb() {
    // LENGTHEN VOWELS PRECEDING PUNCTUATION
    //
    // Search for punctuation. If found, back up to the first vowel, then
    // process all phonemes between there and up to (but not including) the punctuation.
    // If any phoneme is found that is a either a fricative or voiced, the duration is
    // increased by (length * 1.5) + 1

    // loop index
	{
	unsigned char X = 0;
	unsigned char index;

	while((index = phonemeindex[X]) != END) {
		unsigned char loopIndex;

		// not punctuation?
		if((flags[index] & FLAG_PUNCT) == 0) {
			++X;
			continue;
		}

		loopIndex = X;

        while (--X && !(flags[phonemeindex[X]] & FLAG_VOWEL)); // back up while not a vowel
        if (X == 0) break;

		do {
            // test for vowel
			index = phonemeindex[X];

			// test for fricative/unvoiced or not voiced
			if(!(flags[index] & FLAG_FRICATIVE) || (flags[index] & FLAG_VOICED)) {     //nochmal 黚erpr黤en
				unsigned char A = phonemeLength[X];
				// change phoneme length to (length * 1.5) + 1
                drule_pre("Lengthen <FRICATIVE> or <VOICED> between <VOWEL> and <PUNCTUATION> by 1.5",X);
				phonemeLength[X] = (A >> 1) + A + 1;
                drule_post(X);
			}
		} while (++X != loopIndex);
		X++;
	}  // while
	}

    // Similar to the above routine, but shorten vowels under some circumstances

    // Loop through all phonemes
	unsigned char loopIndex=0;
	unsigned char index;

	while((index = phonemeindex[loopIndex]) != END) {
		unsigned char X = loopIndex;

		if (flags[index] & FLAG_VOWEL) {
			index = phonemeindex[loopIndex+1];
			if (!(flags[index] & FLAG_CONSONANT)) {
				if ((index == 18) || (index == 19)) { // 'RX', 'LX'
					index = phonemeindex[loopIndex+2];
					if ((flags[index] & FLAG_CONSONANT)) {
                        drule_pre("<VOWEL> <RX | LX> <CONSONANT> - decrease length of vowel by 1\n", loopIndex);
    					phonemeLength[loopIndex]--;
                        drule_post(loopIndex);
                    }
				}
			} else { // Got here if not <VOWEL>
                unsigned short flag = (index == END) ? 65 : flags[index]; // 65 if end marker

                if (!(flag & FLAG_VOICED)) { // Unvoiced
                    // *, .*, ?*, ,*, -*, DX, S*, SH, F*, TH, /H, /X, CH, P*, T*, K*, KX
                    if((flag & FLAG_PLOSIVE)) { // unvoiced plosive
                        // RULE: <VOWEL> <UNVOICED PLOSIVE>
                        // <VOWEL> <P*, T*, K*, KX>
                        drule_pre("<VOWEL> <UNVOICED PLOSIVE> - decrease vowel by 1/8th",loopIndex);
                        phonemeLength[loopIndex] -= (phonemeLength[loopIndex] >> 3);
                        drule_post(loopIndex);
                    }
                } else {
                    unsigned char A;
                    drule_pre("<VOWEL> <VOICED CONSONANT> - increase vowel by 1/2 + 1\n",X-1);
                    // decrease length
                    A = phonemeLength[loopIndex];
                    phonemeLength[loopIndex] = (A >> 2) + A + 1;     // 5/4*A + 1
                    drule_post(loopIndex);
                }
            }
		} else if((flags[index] & FLAG_NASAL) != 0) { // nasal?
            // RULE: <NASAL> <STOP CONSONANT>
            //       Set punctuation length to 6
            //       Set stop consonant length to 5
            index = phonemeindex[++X];
            if (index != END && (flags[index] & FLAG_STOPCONS)) {
                drule("<NASAL> <STOP CONSONANT> - set nasal = 5, consonant = 6");
                phonemeLength[X]   = 6; // set stop consonant length to 6
                phonemeLength[X-1] = 5; // set nasal length to 5
            }
        } else if((flags[index] & FLAG_STOPCONS)) { // (voiced) stop consonant?
            // RULE: <VOICED STOP CONSONANT> {optional silence} <STOP CONSONANT>
            //       Shorten both to (length/2 + 1)

            // move past silence
            while ((index = phonemeindex[++X]) == 0);

            if (index != END && (flags[index] & FLAG_STOPCONS)) {
                // FIXME, this looks wrong?
                // RULE: <UNVOICED STOP CONSONANT> {optional silence} <STOP CONSONANT>
                drule("<UNVOICED STOP CONSONANT> {optional silence} <STOP CONSONANT> - shorten both to 1/2 + 1");
                phonemeLength[X]         = (phonemeLength[X] >> 1) + 1;
                phonemeLength[loopIndex] = (phonemeLength[loopIndex] >> 1) + 1;
                X = loopIndex;
            }
        } else if ((flags[index] & FLAG_LIQUIC)) { // liquic consonant?
            // RULE: <VOICED NON-VOWEL> <DIPTHONG>
            //       Decrease <DIPTHONG> by 2
            index = phonemeindex[X-1]; // prior phoneme;

            // FIXME: The debug code here breaks the rule.
            // prior phoneme a stop consonant>
            if((flags[index] & FLAG_STOPCONS) != 0) 
                drule_pre("<LIQUID CONSONANT> <DIPTHONG> - decrease by 2",X);
            
            phonemeLength[X] -= 2; // 20ms
            drule_post(X);
         }

        ++loopIndex;
    }
}
