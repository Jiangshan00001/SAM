SAM
===

Software Automatic Mouth - Tiny Speech Synthesizer 


What is SAM?
============

Sam is a very small Text-To-Speech (TTS) program written in C, that runs on most popular platforms.
It is an adaption to C of the speech software SAM (Software Automatic Mouth) for the Commodore C64 published 
in the year 1982 by Don't Ask Software (now SoftVoice, Inc.). It includes a Text-To-Phoneme converter called reciter and a Phoneme-To-Speech routine for the 
final output. It is so small that it will work also on embedded computers. On my computer it takes
less than 39KB (much smaller on embedded devices as the executable-overhead is not necessary) of disk space and is a fully stand alone program. 
For immediate output it uses the SDL-library, otherwise it can save .wav files. 

An online version and executables for Windows can be found on the web site: http://simulationcorner.net/index.php?page=sam



changes:
=======
1. change some code name for readablity.
2. add doxygen doc.
3. add chinese pinyin support.


how to say chinese:
=======

./sam.exe -pinyin ni1hao4a2 -debug -wav nihao.wav

will speak 你好啊


.sam.exe wo4hui4shuo4han4yu4a4  -pinyin -debug -wav tt.wav

will speak 我会说汉语啊



Compile
=======

Simply type "make" in your command prompt.
In order to compile without SDL remove the SDL statements from the CFLAGS and LFLAGS variables in the file "Makefile".

It should compile on every UNIX-like operating system. For Windows you need Cygwin or MinGW( + libsdl).




Docs:
=====

https://jiangshan00001.github.io/SAM/html/index.html
https://jiangshan00001.github.io/SAM/html/modules.html


License
=======

The software is a reverse-engineered version of a commercial software published more than 30 years ago.
The current copyright holder is SoftVoice, Inc. (www.text2speech.com)

As long this is the case I cannot put my code under any specific open source software license
Use it at your own risk.

this is only for study purpose.


this is from :
https://github.com/vidarh/SAM
https://github.com/s-macke/SAM


Contact
=======

If you have questions don' t hesitate to ask me.
If you discovered some new knowledge about the code please mail me.

710806594@qq.com

