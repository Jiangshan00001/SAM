#include<stdio.h>
#include "phonemeTabs.h"


int debug = 0;


void PrintPhonemes(unsigned char *phonemeindex, unsigned char *phonemeLength, unsigned char *stress)
{
	int i = 0;
	printf("===========================================\n");

	printf("Internal Phoneme presentation:\n\n");
    printf("no idx    phoneme  length  stress\n");
	printf("------------------------------\n");

	while((phonemeindex[i] != 255) && (i < 255))
	{
		if (phonemeindex[i] < 81)
		{
            printf("%3i  %3i      %c%c      %3i       %i\n",
                   i,
			phonemeindex[i],
            phonemeNameTable1[phonemeindex[i]],
            PhonemeNameTable2[phonemeindex[i]],
			phonemeLength[i],
			stress[i]
			);
		} else
		{
			printf("%3i %3i      ??      %3i       %i\n",i, phonemeindex[i], phonemeLength[i], stress[i]);
		}
		i++;
	}
	printf("===========================================\n");
	printf("\n");
}

void PrintOutput(
	unsigned char *flag, 
	unsigned char *f1, 
	unsigned char *f2, 
	unsigned char *f3,
	unsigned char *a1, 
	unsigned char *a2, 
	unsigned char *a3,
	unsigned char *p)
{
	int i = 0;
	printf("===========================================\n");
	printf("Final data for speech output:\n\n");
    printf("no flags ampl1 freq1 ampl2 freq2 ampl3 freq3 pitch\n");
	printf("------------------------------------------------\n");
	while(i < 255)
	{
		printf("%5i %5i %5i %5i %5i %5i %5i %5i %5i\n",i, flag[i], a1[i], f1[i], a2[i], f2[i], a3[i], f3[i], p[i]);
        if((flag[i]==a1[i])&&
                (a1[i]==f1[i])&&(f1[i]==a2[i])&&
                (a2[i]==f2[i])&&(f2[i]==a3[i])&&(a3[i]==f3[i])&&(f3[i]==0))
            break;
		i++;
	}
	printf("===========================================\n");

}

extern unsigned char GetRuleByte(unsigned short mem62, unsigned char Y);

void PrintRule(unsigned short offset)
{
	unsigned char i = 1;
	unsigned char A = 0;
	printf("Applying rule: ");
	do
	{
		A = GetRuleByte(offset, i);
		if ((A&127) == '=') printf(" -> "); else printf("%c", A&127);
		i++;
	} while ((A&128)==0);
	printf("\n");
}





void PrintUsage()
{
    printf("usage: sam [options] Word1 Word2 ....\n");
    printf("options\n");
    printf("	-phonetic 		enters phonetic mode. (see below)\n");
    printf("	-pinyin		enter chinese pinyin mode.\n");
    printf("	-pitch number		set pitch value (default=64)\n");
    printf("	-speed number		set speed value (default=72)\n");
    printf("	-throat number		set throat value (default=128)\n");
    printf("	-mouth number		set mouth value (default=128)\n");
    printf("	-wav filename		output to wav instead of libsdl\n");
    printf("	-sing			special treatment of pitch\n");
    printf("	-debug			print additional debug messages\n");
    printf("\n");


    printf("     VOWELS                            VOICED CONSONANTS	\n");
    printf("IY           f(ee)t                    R        red		\n");
    printf("IH           p(i)n                     L        allow		\n");
    printf("EH           beg                       W        away		\n");
    printf("AE           Sam                       W        whale		\n");
    printf("AA           pot                       Y        you		\n");
    printf("AH           b(u)dget                  M        Sam		\n");
    printf("AO           t(al)k                    N        man		\n");
    printf("OH           cone                      NX       so(ng)		\n");
    printf("UH           book                      B        bad		\n");
    printf("UX           l(oo)t                    D        dog		\n");
    printf("ER           bird                      G        again		\n");
    printf("AX           gall(o)n                  J        judge		\n");
    printf("IX           dig(i)t                   Z        zoo		\n");
    printf("				       ZH       plea(s)ure	\n");
    printf("   DIPHTHONGS                          V        seven		\n");
    printf("EY           m(a)de                    DH       (th)en		\n");
    printf("AY           h(igh)						\n");
    printf("OY           boy						\n");
    printf("AW           h(ow)                     UNVOICED CONSONANTS	\n");
    printf("OW           slow                      S         Sam		\n");
    printf("UW           crew                      Sh        fish		\n");
    printf("                                       F         fish		\n");
    printf("                                       TH        thin		\n");
    printf(" SPECIAL PHONEMES                      P         poke		\n");
    printf("UL           sett(le) (=AXL)           T         talk		\n");
    printf("UM           astron(omy) (=AXM)        K         cake		\n");
    printf("UN           functi(on) (=AXN)         CH        speech		\n");
    printf("Q            kitt-en (glottal stop)    /H        a(h)ead	\n");
}
