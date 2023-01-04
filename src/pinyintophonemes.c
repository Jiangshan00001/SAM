#include "string.h"
#include "pinyintophonemes.h"

static char inputtemp[256];   // secure copy of input tab36096

typedef char * CHAR_P;
typedef struct PINYIN_S_TAG{
CHAR_P pinyin;
CHAR_P phoneme;
}PINYIN_S;

//https://mp.weixin.qq.com/s?__biz=MzAxNjkxOTk2OA==&mid=2247570887&idx=3&sn=008882f45590368e99b022118a396561&chksm=9beee908ac99601efb48a689e8fb313536ff3ce7305622278ee32f1b81b080a583fb05e6cdcf&scene=27
//http://www.retrobits.net/atari/sam.shtml#ch5.7
///https://sites.google.com/site/h2obsession/CBM/C128/SAM-128/phonemes
PINYIN_S g_pinyin_table[]={

    /*3字母 韵母*/
    {"ANG", "AH2NX"}, //long = LAO4NX AH-bug
    {"ENG", "EHN"},
    {"ING", "NXGUL"},//IYN single = SIH4NXGUL
    {"ONG", "WAH"},//WUN WAH-one NX-wrong

    /*2字母 韵母*/
    {"AI", "EH"},//air = EH4R
    {"EI", "IX"},//
    {"UI", "WEY"},//WE-way WIY-weak
    {"AO", "AO"}, //AO AW
    {"OU", "AA"},
    {"IU", "IHUX"},
    {"IE", "IHEH"},
    {"VE", "IYUW"},
    {"ER", "ER"},
    {"AN", "AE"},//AX and = AE4ND
    {"EN", "NX"},
    {"IN", "IH"},
    {"UN", "UX"},
    {"VN", "UX"},

    /*2字母 声母*/
    {"ZH", "Z"}, //???
    {"CH", "CH"},
    {"SH", "SH"},

    /*单字母 声母*/
    //23个: bpmfdtnlgkhjqxzhchshrzcsyw
    {"B", "B"},
    {"P", "P"},
    {"M", "M"},
    {"F", "F"},
    {"D", "D"},
    {"T", "T"},
    {"N", "N"},
    {"L", "L"},
    {"G", "G"},
    {"K", "K"},
    {"H", "/H"},
    {"J", "JIH"},//jiffy = JIH4FIY ????
    {"Q", "Q"},
    {"X", "SEY"}, //??? TH??


    {"R", "R"},
    {"Z", "Z"},//Z--zoo DH-->then ZIH-zip  ZIY-zero
    {"C", "S"},
    {"S", "S"},
    {"Y", "IY"},
    {"W", "UH"},
    /*单字母 韵母*/
    ///韵母表24个. aoeiuü aieiui aoouiu ieüeer aneninun ang engingong
    {"A", "AH"},
    {"O", "AA"},
    {"E", "ER"},
    {"I", "IY"},//three = THRIY4
    {"U", "V"},
    {"V", "IYV"},



};
int g_pinyin_table_len = sizeof(g_pinyin_table)/sizeof(g_pinyin_table[0]);

int PinyinToPhonemes(char *inpu)
{
    //printf("PinyinToPhonemes start\n");
    int X=0;
    //unsigned char A;
    inputtemp[0] = ' ';
    int input_len = strlen((char*)inpu);
    strcpy((char*)inputtemp, inpu);
    inputtemp[255] = 27;
    memset(inpu,0, 256);

    for(X=0;X<input_len;++X)
    {
        //printf("search X=%d\n", X);
        int match_len=0;
        for(int i=0;i<g_pinyin_table_len;++i)
        {
            int str_len = strlen(g_pinyin_table[i].pinyin);
            if(strncmp(g_pinyin_table[i].pinyin, inputtemp+X, str_len)==0)
            {
                //此处匹配。直接翻译
                match_len = str_len;
                strcat(inpu, g_pinyin_table[i].phoneme);
                break;
            }
        }
        if(match_len==0)
        {
            //printf("match nothing X=%d\n", X);
            //no match. just stress???
            if((inputtemp[X]>='1')&&(inputtemp[X]<='8'))
            {
                char tmp[4]={0,0,0,0};
                /// 1--一声 ->5
                /// 2--二声 7
                /// 3--三声 3
                /// 4--四声 1
                /// 5--轻声 8
                ///
//                if(inputtemp[X]=='1')tmp[0]='5';
//                else if(inputtemp[X]=='2')tmp[0]='7';
//                else if(inputtemp[X]=='3')tmp[0]='3';
//                else if(inputtemp[X]=='4')tmp[0]='1';
//                else if(inputtemp[X]=='5')tmp[0]='8';
                tmp[0]=inputtemp[X];

                strcat(inpu,tmp );
                match_len=1;
            }
            else
            {
                //skip this char?
                match_len=1;
                strcat(inpu, " ");
            }
        }

        //因为默认X每次加1，如果一次匹配多余1个字符，则此处要加上
        if(match_len>1)X+= match_len-1;
    }

    input_len=strlen(inpu);
    inpu[input_len]=155u;//end of line marker
    inpu[input_len+1]=0;//end of str marker

    return 1;
}
