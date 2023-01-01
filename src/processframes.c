#include "render.h"
#include "RenderTabs.h"
#include "render.h"
#include "sam.h"


extern void Output(int index, unsigned char A);

///
/// \brief GenerateWaveFromFreqPhase
/// \param phase1
/// \param phase2
/// \param phase3
/// \param Y
///
/// wave=sin(f1)*amp(f1) + sin(f2)*amp(f2)+rect(f3)*amp(f3) + constant_value
///
static void GenerateWaveFromFreqPhase(unsigned char phase1, unsigned char phase2, unsigned char phase3, unsigned char frame_index)
{
    unsigned int tmp;

    tmp   = multtable[sinus[phase1]     | amplitude1[frame_index]];
    tmp  += multtable[sinus[phase2]     | amplitude2[frame_index]];
    tmp  += tmp > 255 ? 1 : 0; // if addition above overflows, we for some reason add one;
    tmp  += multtable[rectangle[phase3] | amplitude3[frame_index]];
    tmp  += 0x88;
    tmp >>= 4; // Scale down to 0..15 range of C64 audio.
            
    Output(0, tmp & 0xf);
}

// PROCESS THE FRAMES
//
// In traditional vocal synthesis, the glottal pulse drives filters, which
// are attenuated to the frequencies of the formants.
//
// SAM generates these formants directly with sin and rectangular waves.
// To simulate them being driven by the glottal pulse, the waveforms are
// reset at the beginning of each glottal pulse.
//
void ProcessFrames2Buffer(unsigned char frame_len)
{
    unsigned char speedcounter = 72;
	unsigned char phase1 = 0;
    unsigned char phase2 = 0;
	unsigned char phase3 = 0;
    unsigned char const_offset = 0; //!! was not initialized
    
    unsigned char frame_index = 0;

    unsigned char glottal_pulse = pitches[0];
    unsigned char voiced_const_voice_time = glottal_pulse - (glottal_pulse >> 2); // mem44 * 0.75

    while(frame_len) {
        unsigned char flags = sampledConsonantFlag[frame_index];
		
		// unvoiced sampled phoneme?
        if(flags & 0xf8) {
            RenderConsonantSample(&const_offset, flags,frame_index);
			// skip ahead two in the phoneme buffer
            frame_index += 2;
            frame_len -= 2;
            speedcounter = speed;
		} else {
            GenerateWaveFromFreqPhase(phase1, phase2, phase3, frame_index);

			speedcounter--;
			if (speedcounter == 0) { 
                frame_index++; //go to next amplitude
                // decrement the frame count
                frame_len--;
                if(frame_len == 0) return;
                speedcounter = speed;
            }
         
            --glottal_pulse;
		
            if(glottal_pulse != 0) {
                // not finished with a glottal pulse

                --voiced_const_voice_time;
                // within the first 75% of the glottal pulse?
                // is the count non-zero and the sampled flag is zero?
                if((voiced_const_voice_time != 0) || (flags == 0))
                {
                    ///here is vowel or voiced const voice time.
                    // reset the phase of the formants to match the pulse
                    phase1 += frequency1[frame_index];
                    phase2 += frequency2[frame_index];
                    phase3 += frequency3[frame_index];
                    continue;
                }
                
                // voiced sampled phonemes interleave the sample with the
                // glottal pulse. The sample flag is non-zero, so render
                // the sample for the phoneme.
                RenderConsonantSample(&const_offset, flags,frame_index);
            }
        }

        glottal_pulse = pitches[frame_index];
        voiced_const_voice_time = glottal_pulse - (glottal_pulse>>2); // mem44 * 0.75

        // reset the formant wave generators to keep them in 
        // sync with the glottal pulse
        phase1 = 0;
        phase2 = 0;
        phase3 = 0;
	}
}
