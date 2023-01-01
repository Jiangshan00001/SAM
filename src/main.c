#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "reciter.h"
#include "sam.h"
#include "debug.h"
#include "WriteWav.h"

#ifdef USESDL
#include <SDL.h>
#include <SDL_audio.h>
#endif

static int my_min(int l, int r) { return l < r ? l : r; }

// Approximations of some Windows functions to ease portability
#if defined __GNU_LIBRARY__ || defined __GLIBC__
static void strcat_s(char * dest, int size, char * str) {
    unsigned int dlen = strlen(dest);
    if (dlen >= size-1) return;
    strncat(dest+dlen, str, size - dlen - 1);
}
void fopen_s(FILE ** f, const char * filename, const char * mode) {
    *f = fopen(filename,mode);
}
#endif


void PrintUsage()
{
	printf("usage: sam [options] Word1 Word2 ....\n");
	printf("options\n");
	printf("	-phonetic 		enters phonetic mode. (see below)\n");
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

#ifdef USESDL

int pos = 0;
void MixAudio(void *unused, Uint8 *stream, int len)
{
	int bufferpos = GetBufferLength();
	char *buffer = GetBuffer();
	int i;
	if (pos >= bufferpos) return;
	if ((bufferpos-pos) < len) len = (bufferpos-pos);
	for(i=0; i<len; i++)
	{
		stream[i] = buffer[pos];
		pos++;
	}
}


void OutputSound()
{
	int bufferpos = GetBufferLength();
	bufferpos /= 50;
	SDL_AudioSpec fmt;

	fmt.freq = 22050;
	fmt.format = AUDIO_U8;
	fmt.channels = 1;
	fmt.samples = 2048;
	fmt.callback = MixAudio;
	fmt.userdata = NULL;

	/* Open the audio device and start playing sound! */
	if ( SDL_OpenAudio(&fmt, NULL) < 0 ) 
	{
		printf("Unable to open audio: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_PauseAudio(0);
	//SDL_Delay((bufferpos)/7);
	
	while (pos < bufferpos)
	{
		SDL_Delay(100);
	}
	
	SDL_CloseAudio();
}

#else

void OutputSound() {}

#endif	


/// @addtogroup KeyFuncs
/// @{
/// \ref TextToPhonemes -> [ \ref input ] @n
/// \ref PhonemeStr2PhonemeIdx -> [ \ref phonemeindex,  \ref phonemeLength, \ref stress  ] @n
/// \ref RenderAll -> [ \ref phonemeIndexOutput,  \ref phonemeLengthOutput, \ref stressOutput ] @n
/// \ref CreateFrames -> [ \ref frequency1, \ref frequency2, \ref frequency3 \ref amplitude1 \ref amplitude2, \ref amplitude3 \ref pitches \ref sampledConsonantFlag ] @n
/// \ref ProcessFrames2Buffer -> [ \ref buffer, \ref bufferpos ] @n
///
/// @}
///





/// @mainpage sam tech analysis
/// @ref main
///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
///
/// main: @n
/// 1 copy input to var @ref input. @n
/// 2 use @ref TextToPhonemes to do text to phoneme if input is text. @n
/// 3 call @ref SAMMain to do other things. @n
/// @n
/// @n
/// @ref KeyFuncs
/// @ref phonemeTables
/// @ref RenderTabs
/// @ref  KeyVars
///
/// ref: @n
/// https://sites.google.com/site/h2obsession/CBM/C128/SAM-128  @n
/// https://simulationcorner.net/index.php?page=sam  @n
///
int main(int argc, char **argv)
{
	int i;
	int phonetic = 0;

	char* wavfilename = NULL;
    unsigned char inpu[256];

    memset(inpu, 0, 256);

	if (argc <= 1)
	{
		PrintUsage();
		return 1;
	}

	i = 1;
	while(i < argc)
	{
		if (argv[i][0] != '-')
		{
            strcat_s((char*)inpu, 256, argv[i]);
            strcat_s((char*)inpu, 256, " ");
		} else
		{
			if (strcmp(&argv[i][1], "wav")==0)
			{
				wavfilename = argv[i+1];
				i++;
			} else
			if (strcmp(&argv[i][1], "sing")==0)
			{
				EnableSingmode();
			} else
			if (strcmp(&argv[i][1], "phonetic")==0)
			{
				phonetic = 1;
			} else
			if (strcmp(&argv[i][1], "debug")==0)
			{
				debug = 1;
			} else
			if (strcmp(&argv[i][1], "pitch")==0)
			{
                SetPitch((unsigned char)my_min(atoi(argv[i+1]),255));
				i++;
			} else
			if (strcmp(&argv[i][1], "speed")==0)
			{
                SetSpeed((unsigned char)my_min(atoi(argv[i+1]),255));
				i++;
			} else
			if (strcmp(&argv[i][1], "mouth")==0)
			{
                SetMouth((unsigned char)my_min(atoi(argv[i+1]),255));
				i++;
			} else
			if (strcmp(&argv[i][1], "throat")==0)
			{
                SetThroat((unsigned char)my_min(atoi(argv[i+1]),255));
				i++;
			} else
			{
				PrintUsage();
				return 1;
			}
		}
		
		i++;
	} //while

    for(i=0; inpu[i] != 0; i++){
        inpu[i] = (unsigned char)toupper((int)inpu[i]);
    }

	if (debug)
	{
        if (phonetic) printf("phonetic input: %s\n", inpu);
        else printf("text input: %s\n", inpu);
	}
	
	if (!phonetic)
	{
        strcat_s((char*)inpu, 256, "[");
        if (!TextToPhonemes(inpu)) return 1;
		if (debug)
            printf("phonetic input: %s\n", inpu);
    } else strcat_s((char*)inpu, 256, "\x9b");

#ifdef USESDL
	if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) 
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
#endif

    SetInput(inpu);
	if (!SAMMain())
	{
		PrintUsage();
		return 1;
	}

	if (wavfilename != NULL) 
		WriteWav(wavfilename, GetBuffer(), GetBufferLength()/50);
	else
		OutputSound();

	return 0;
}
