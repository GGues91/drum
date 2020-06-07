/*
    standard C code to read and write a RIFF WAVE file
    [NO] 100% compatibility
    
    wave_t wave;
    if (!wave_read(&wave,"song.wav"))
      exit(1);

    wave_mixer_t mixer;
    mixer.wave.spec.rate = 44100;
    mixer.wave.spec.channels = 1;
    mixer.wave.spec.depth = 16;
    ...
    wave_domix(mixer,&wave);
    ...

    if (!wave_write(&(mixer.wave),"domix.wav"))
      exit(1);

   sin function
    hz is hertz up and down of wave is per second
       additive synthesis
    subtractive synthesis
*/

#include "wave.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int wave_read(wave_t *wave, char *name)
{
  memset(wave,0,sizeof(wave_t));
  // BEGIN OPEN/READ FILE INTO MEMORY BUFFER
  FILE *fs;
  fs = fopen(name,"rb");
  if (!fs)
    return 0;
  fseek(fs,0,SEEK_END);
  long b;
  b = ftell(fs);
  uint8_t *buffer;
  buffer = malloc(b);
  if (!buffer)
    return 0;
  fseek(fs,0,SEEK_SET);
  if (fread(buffer,b,1,fs) != 1)
    return 0;
  fclose(fs);
  // END OPEN/READ FILE INTO MEMORY BUFFER
  //read wav into wav_t
  /*
      RIFF (little endian) https://en.wikipedia.org/wiki/Resource_Interchange_File_Format#Explanation
        chunk ;; 4B_ASCII 4B_UNSIGNED XB_DATA [1B_PAD if XB_DATA's not even]
              ;; 4B_ASCII —→ an ASCII text of 4 bytes —→ RIFF,LIST,"AVI ",WAVE,"fmt ",data,INFO
              ;; 4B_UNSIGNED —→ literally 4 bytes —→ the length of this chunks data
              ;; XB_DATA —→ arbitrary number of bytes (the amount is given by 4B_UNSIGNED) —→ this chunk's data
              ;; 1B_PAD —→ just 1 byte —→ if the size of XB_DATA is odd then this pad will exist
        http://www-mmsp.ece.mcgill.ca/documents/audioformats/wave/wave.html
        wave  ;; RIFF 4+N WAVEfmt  

  */
  // p will be used to go through the file
  uint8_t *p;
  p = buffer;
  // BEGIN MASTER RIFF CHUNK
  if (strncmp(p,"RIFF",4))
    return 0;
  p += 4;
  uint32_t chunk_size;
  chunk_size = 4 /*WAVE*/ + *((uint32_t*)p); //TODO: support big endian machines
  p += 4;
  if (strncmp(p,"WAVE",4))
    return 0;
  p += 4;
  // END OF MASTER RIFF CHUNK
  /*
      from here, it's just a bunch of subchunks following the format above
  */
  // BEGIN SUBCHUNKS
  while((uint32_t)(p - buffer) != b && //first test if we're at the end of the file
        (*p >= 'A' && *p <= 'Z'        //second, if we're not, then we should encounter a CHUNK-ID
                   ||                  //... if not, then we terminate
         *p >= 'a' && *p <= 'z'))
  //while ((uint32_t)(p - buffer) != b) //turns out atleast *one* random file had an extra 4096 bytes without any chunk-id <<--- so this conditional would loop forever
  {
    if (!strncmp(p,"fmt ",4))
      {
        p += 4;
        chunk_size = *((uint32_t*)p);
        //printf("%lu\n",chunk_size);
        p += 4;
        //wFormatTag
        #define WWAVE_FORMAT_PCM        0x0001
        #define WWAVE_FORMAT_IEEE_FLOAT 0x0003
        #define WWAVE_FORMAT_ALAW       0x0006
        #define WWAVE_FORMAT_MULAW      0x0007
        #define WWAVE_FORMAT_EXTENSIBLE 0xFFFE
        /*
        #undef WWAVE_FORMAT_PCM        
        #undef WWAVE_FORMAT_IEEE_FLOAT 
        #undef WWAVE_FORMAT_ALAW       
        #undef WWAVE_FORMAT_MULAW      
        #undef WWAVE_FORMAT_EXTENSIBLE 
        */
        p += 2;
        //nChannels
        wave->spec.channels = *((int16_t*)p);
        p += 2;
        //nSamplesPerSec
        wave->spec.rate = *((int32_t*)p);
        p += 4;
        //nAvgBytesPerSec //bitrate? = (sample rate * bit depth * channels) / 8
        p += 4;
        //nBlockAlign
        p += 2;
        //wBitsPerSample
        wave->spec.depth = *((int16_t*)p); //should be rounded up to the next multiple of 8bits?
        p += 2;
        //these fields may or may not be...
        //this condition can be: if chunk_size == 18 || chunk_size == 40
        //if "fmt " is specified last in the file, then this condition will access 1 byte not allocated
        if (!(*p >= 'A' && *p <= 'Z' ||
            *p >= 'a' && *p <= 'z'))
          {
            //cbSize
            if (0 == *((int16_t*)p))
              continue;
            fprintf(stderr,
                    "%s:%d: error reading wav file: unsupported additional fields in \"fmt \" / you need to implement them\n", 
                    __FILE__,__LINE__);
            exit(1);
            p += 2;
            //wValidBitsPerSample
            p += 2;
            //dwChannelMask
            p += 4;
            //SubFormat
            p += 16;
          }
      }
    else
    if (!strncmp(p,"data",4)) //this chunk denotes the samples
      {
        p += 4;
        chunk_size = *((uint32_t*)p);
        wave->samples = malloc(chunk_size);
        p += 4;
        memcpy(wave->samples,p,chunk_size);
        p += chunk_size; //+ 4096; there's an additional that many bytes ?!
        wave->length = chunk_size; //count of bytes in wave.samples
        //printf("%s\n",p);
      }
    else //non-accounted for chunks, just ignore them
      {
        //printf("found something else\n");
        p += 4;
        chunk_size = *((uint32_t*)p);
        p += 4;
        p += chunk_size;
      }
    //p will point to a chunk beginning, so adding chunk_size to it should direct us either 
    //to a new chunk-id or none at all (in which case the file has been read)
    //although, one thing i am concerned about is that this might actually make us address a memory address
    //out of the allocated memory... "WAVE xxxxxx\0HERE IS LAST PLACE P POINTS" //... time will tell
    //if segmentation fault happens, then here is likely the reason (although it's just 1 byte)
    //and we actually don't write to it, so i'm not sure why any error should occur (but what happens if
    //that address points to a character??? then we will continue into deep space. hmm
    //solved this in upper loop conditional, see the comment above
    //p += chunk_size;
  }
  // END OF SUBCHUNKS
  //printf ("%d,%d\n",b,((int32_t)(p - buffer)));
  free(buffer);
  return 1;
}

int wave_write(wave_t *wave, char *name)
{
  FILE *fs;
  fs = fopen(name, "wb");
  if (!fs)
    return 0;
  #define allocSIZE 4/*RIFF*/ + 4/*CHUNK*/ + 4/*WAVE*/ \
    + 24 /*fmt */ /*chunk is 18*/ \
    + 8 /*data*/ /*chunk is 4 + 4 X (sizeof(chunk) counted in X)*/ \
    + wave->length
  char *buffer = malloc(allocSIZE);
  char *p = buffer;
  memcpy(p,"RIFF",4);
  p += 4;
  *(uint32_t*)p = allocSIZE;
  p += 4;
  memcpy(p,"WAVE",4);
  p += 4;
  memcpy(p,"fmt ",4);
  p += 4;
  *(uint32_t*)p = 16;
  p += 4;
  *(uint16_t*)p = WWAVE_FORMAT_PCM;
  p += 2;
  *(uint16_t*)p = wave->spec.channels;
  p += 2;
  *(uint32_t*)p = wave->spec.rate;
  p += 4;
  *(uint32_t*)p = (wave->spec.rate * wave->spec.depth * wave->spec.channels) / 8;
  p += 4;
  *(uint16_t*)p = wave->spec.depth * wave->spec.channels; //????
  p += 2;
  *(uint16_t*)p = wave->spec.depth;
  p += 2;
  memcpy(p,"data",4);
  p += 4;
  *(uint32_t*)p = 4 + wave->length;
  p += 4;
  memcpy(p,wave->samples,wave->length);
  /*buffer is just assigned for return value*/ *(uint32_t*)buffer = fwrite(buffer,1,allocSIZE,fs);
  fclose(fs);
  return *(uint32_t*)buffer == allocSIZE;
  #undef allocSIZE
}

//###
//###  here goes operations on samples like mixing and effects
//###

/*
    http://stackoverflow.com/questions/31417953/c-how-to-mix-two-wav-files-without-using-any-multimedia-libraries

    mixer ;; mix a wave_t to a wave_mixer_t's wave_t
    ----------------------------------------------
    continous array of initially empty samples that grows as needed
    an offset to denote where a mix should occur

    change in offset is only applied when mixing src
    so, adding empty samples to the end of a wave must be done
    manually, or by pointing src to the empty samples
    mixing src after progressing mixer->offset will in-effect create a gap
    of empty samples between the previous mixer->offset and the progressed one

    mixer->offset is advanced automatically to the end of src in dest

    WAVE is interleaved

    [NO] channel conversion
    [NO] sample rate conversion
    [NO] depth conversion
*/
int wave_domix(wave_mixer_t *dest, wave_t *src)
{
  /* dest->wave.length is total */
  if(dest->offset + src->length > dest->wave.length)
  {
    /* calculate new length */
    uint32_t len = dest->offset + src->length;
    /* write exceeds allocated space */
    if(len >= dest->allocated)
    {
      /* allocate chunk twice len for less frequent allocation to mixer */
      dest->allocated = len * 2;
      /*
	
       */
      /* in-effect zero set any lapse in offset beyond the end of samples */
      int8_t *samples = calloc(dest->allocated,1);
      /* copy previously written samples */
      if(dest->wave.samples)
      {
        memcpy(samples,dest->wave.samples,/* previous length */dest->wave.length);
        free(dest->wave.samples);
      }
      dest->wave.samples = samples;
    }
    /*
        the error was that I had put this statement in the above block
        it should not be there because it is not certain whether len exceeds
        the allocated space, but it is certain that dest->offset + src->length
        is higher than dest->wave.length, which if this routine is called repetitively
        without changing dest->wave.length (as was the error) ... argh fuck I can't explain
        why it causes certain waves to be omitted from the resulting successive mix.
        actually, dest->wave.length did rarely get advanced because only when sufficient
        offset was built up would it surpass dest->wave.length, as argh... nvm
        TODO: explain to my brain
    */
    dest->wave.length = len;
  }
  double attenuation = 1.0;
  double sum;
  uint32_t n;
  for(n = 0; n < src->length; n += 2)
  {
    sum = *(int16_t*)(dest->wave.samples + dest->offset) + *(int16_t*)(src->samples + n);
    sum *= attenuation;
    if (sum > 32767) 
      sum = 32767;
    else
    if (sum < -32767)
      sum = -32767;
    *(int16_t*)(dest->wave.samples + dest->offset) = sum;
    dest->offset += 2;
  }
  return 1;
}
